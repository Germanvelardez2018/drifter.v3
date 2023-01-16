/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "debug.h"
#include "gpio.h"
#include "clock_master.h"
#include "time.h"
#include "sim.h"
#include "mpu6050.h"
#include "memory.h"
#include "fsm.h"
#include "rtc.h"
#include "pwrm.h"


extern UART_HandleTypeDef huart1;
#define UPLOAD_CHECK                    "CMD:Forzar upload\r\n"
#define CMD_CHECK                       "CMD Nuevo intervalo:%d \r\n"
#define SENSOR_FORMAT                   "( %s,: %s)"
#define INIT_MSG                        "Init  drifter \r\n"
#define CHECK_MSG_LEN                   (strlen(CHECK_MSG))
#define CHECK_TOPIC                     "DEVICE"
#define BUFFER_SIZE                     150

#define MQTT_SEND_CHECK()               sim7000g_mqtt_publish(CHECK_TOPIC, get_state_device(), strlen(get_state_device()))

//#define MQTT_SEND_CHECK()               sim7000g_mqtt_publish("STATE", get_state_device(), strlen(get_state_device()))
#define MQTT_SEND_DATA(msg)             sim7000g_mqtt_publish("GPS", msg, strlen(msg))


PRIVATE uint8_t buffer_upload[200];


#define ID_FORMAT                         ("(Device)Contador:%d / MAX:%d , Intervalo:%d m \r\n ")
#define ID_FORMAT_DEBUG                   ("(Device)Counter:%d, Cmax:%d, Cinterval:%d, Cimax:%d \r\n")
#define STATE_DEVICE_LEN            (100)
PRIVATE uint8_t state_device[STATE_DEVICE_LEN];
PRIVATE uint8_t counter = 0;          //  Contador de muestras almacenadas
PRIVATE uint8_t cmax = 0;             // Maximo valor del contador de muestras almacenadas
PRIVATE uint8_t counter_interval = 0;
PRIVATE uint8_t cmax_interval = 0;   // Contador maximo de intervalos

PRIVATE uint8_t* get_state_device(){
  //Actualizo las variables counter,cmax y cmax_interval
  
  mem_s_get_counter(&counter);
  mem_s_get_max_amount_data(&cmax);
  mem_s_get_cmax_interval(&cmax_interval);
  sprintf(state_device,ID_FORMAT,
                          counter,
                          cmax,
                          cmax_interval*5);
  return state_device;

}





PRIVATE void app_init(){
  // Inicio todos los servicios necesarios
  // Core
  HAL_Init();
  clock_master_set(CLOCK_4MHZ);
  MX_GPIO_Init();
  // Debug
  debug_init();
  debug_print(INIT_MSG);
  // Memoria externa
  mem_s_init();
  // sensor
  mpu6050_init();

  pwrm_init();
  // FSM
  fsm_init();
  // Mensaje inicial
//  cmax_interval = 2;
  debug_print(get_state_device());

 

}

#define delay_time          (800)
#define delay_tiny          (500)
PRIVATE void check_routine(){

  // Encender el modulo
  sim_init();
  delay(delay_time);
  // Conectarse a servidor
  sim_4g_connect();
  delay(delay_time);
  sim_mqtt_connect();
  // Enviar mensaje de check
  delay(delay_time);
  sim7000g_set_irt();
  delay(delay_time);
  MQTT_SEND_CHECK();
  delay(delay_time);
  uint8_t p_cmd_buffer[30] = {"sin datos "};
  uint8_t timeout = 0; 
  uint8_t opt = 0;
  uint8_t out = 0;
  // Sub mqtt topic
  debug_print(" sub a topic CMD \r\n");
  delay(delay_time);
  gpio_irq_on();
  delay(delay_tiny);
  sim7000g_mqtt_subscription("CMD");
# if(1)
  while(opt ==0 && out == 0 ){
    get_copy_cmd_buffer(p_cmd_buffer);
    opt =  sim7000g_get_parse(p_cmd_buffer);
    if(timeout == 20)break;
    timeout++;
    delay(delay_tiny);
  }

  uint8_t min =0;
  if(opt > 0){
    switch (opt)
    {
      // intervalo 15m
    case 1:
        min = 15;
        sprintf(p_cmd_buffer,CMD_CHECK,min);
        
        cmax_interval = 3; 
        mem_s_set_cmax_interval(&cmax_interval);
    break;
    // intervalo 30m
    case 2:
        min = 30;
        sprintf(p_cmd_buffer,CMD_CHECK,min);
        cmax_interval = 6; 
        mem_s_set_cmax_interval(&cmax_interval);
    break;
    // intervalo 60m
    case 3:
        min = 60;
        sprintf(p_cmd_buffer,CMD_CHECK,min);
        cmax_interval = 12; 
        mem_s_set_cmax_interval(&cmax_interval);
    break;
    // max data 10
    case 4:
          sprintf(p_cmd_buffer,"CMD:data 10\r\n");
            cmax = 10;
          mem_s_set_max_amount_data(&cmax);
    break;
    //max data 20
    case 5:
          sprintf(p_cmd_buffer,"CMD:20 data\r\n");
          cmax = 20;
          mem_s_set_max_amount_data(&cmax);
    break;
    //Forzar extraccion
    case 6:
        debug_print(UPLOAD_CHECK);
        fsm_set_state(FSM_UPLOAD);
        counter_interval = 0; // evita que mande save data en vez de upload
    default:
      break;
    
    
    }
    debug_print(p_cmd_buffer);
    sim7000g_mqtt_publish("DEVICE",p_cmd_buffer,strlen(p_cmd_buffer));
    delay(delay_time);
    MQTT_SEND_CHECK();

  }
  #endif
 
  // Unsub mqtt topic
  sim7000g_mqtt_unsubscription("CMD");
  gpio_irq_off();
  debug_print("finalizo la sub a topic CMD \r\n");
  sim_deinit();

}



PRIVATE void upload_routine(){

  sim_init();
  sim_4g_connect();
  delay(delay_tiny);
  sim_mqtt_connect();
  // transmito los datos
   if (cmax < counter)
  {
    counter = cmax;
    mem_s_set_counter(&counter);
  }
  sprintf(buffer_upload, "Extraer :%d datos\n", counter);
  debug_print(buffer_upload);
  delay(delay_time);
  MQTT_SEND_DATA(buffer_upload);
  debug_print("extrayendo:");
  uint8_t data[200];
  if( counter > cmax ) counter = cmax;

  while(counter != 0){
    mem_read_data(data,counter);
    debug_print("mqtt send \r \n");
    debug_print(data);
    MQTT_SEND_DATA(data);
    delay(delay_time);
    counter = counter - 1;
    mem_s_set_counter(&counter);
  }
    //El ultimo elemento a enviar
  mem_read_data(data,0);
  debug_print("mqtt send \r \n");
  debug_print(data);
  MQTT_SEND_DATA(data);
  delay(delay_tiny);
  debug_print("Finalizo deployd \r\n");
  MQTT_SEND_DATA("Fin de transmicion");
  sim_deinit();     
}


PRIVATE void save_data_routine(){
  sim_init();
  sim_gps_on();
  mem_s_get_counter(&counter);
  uint8_t buffer[BUFFER_SIZE] = {"CONTENIDO INICIAL\r\n"};
  uint8_t sensor[50];
  uint8_t gps[100];
  mpu6050_get_measure(sensor);
  wait_for_gps();
  // Obtengo gps
  sim_gps_get_info(gps,100);
  sprintf(buffer, SENSOR_FORMAT, gps, sensor);
  debug_print(buffer);
  mem_write_data(buffer, counter);
  sim_gps_off();
  sim_deinit();
}




/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{ 
  app_init();
  //test sub  
  //fsm_set_state(FSM_UPLOAD);
  if(counter > cmax)fsm_set_state(FSM_UPLOAD);
  while (1)
  {

    switch (fsm_get_state())
    {
      case FSM_CHECK_ONLY:
        debug_print("FSM:CHECK\r\n ");
        check_routine();
        counter_interval =counter_interval+ 1;
        if(counter_interval == cmax_interval)fsm_set_state(FSM_SAVE_DATA);
      break;

      case FSM_SAVE_DATA:
        debug_print("FSM:SAVE DATA \r\n ");
        save_data_routine();
        counter =counter + 1;
        mem_s_set_counter(&counter);
        if( counter == cmax){
          fsm_set_state(FSM_UPLOAD);
        }else{
          fsm_set_state(FSM_CHECK_ONLY);
          counter_interval = 0;
        } 
      break;

      case FSM_UPLOAD:
        debug_print("FSM: UPLOAD \r\n");
        upload_routine();
        counter = 0;
        mem_s_set_counter(&counter);
        fsm_set_state(FSM_CHECK_ONLY);
      break;

      default:
        debug_print("FSM: UNDEFINED \r\n");
      break;
    }
  
  sleep_interval();
  

  }


}


/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}