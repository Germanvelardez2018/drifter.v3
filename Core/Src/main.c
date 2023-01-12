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


#define SENSOR_FORMAT "( %s,: %s)"
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




uint8_t irq = 0;




PRIVATE void app_init(){
  // Inicio todos los servicios necesarios
  // Core
  HAL_Init();
  clock_master_set(CLOCK_8MHZ);
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

 


  //Solo para pruebas de configuracion
 // counter = 8;
 // cmax = 10;
  cmax_interval = 2;
  //mem_s_set_counter(&counter);
  //mem_s_set_max_amount_data(&cmax);
  mem_s_set_cmax_interval(&cmax_interval);
  //Cargo parametros desde Flash externa
 
  debug_print(get_state_device());

  gpio_irq_on();

}


PRIVATE void check_routine(){

  // Encender el modulo
  sim_init();
  // Conectarse a servidor
  sim_4g_connect();
  delay(1000);
  sim_mqtt_connect();
  // Enviar mensaje de check
  delay(2000);
  MQTT_SEND_CHECK();
  delay(500);
  // Sub mqtt topic
  debug_print(" sub a topic CMD \r\n");

  sim7000g_mqtt_subscription("CMD");
  delay(10000);
  // Unsub mqtt topic
  sim7000g_mqtt_unsubscription("CMD");
  debug_print("finalizo la sub a topic CMD \r\n");
  sim_deinit();

}



PRIVATE void upload_routine(){

  sim_init();
  sim_4g_connect();
  delay(800);
  sim_mqtt_connect();
  // transmito los datos
   if (cmax < counter)
  {
    counter = cmax;
    mem_s_set_counter(&counter);
  }
  sprintf(buffer_upload, "Extraer :%d datos\n", counter);
  debug_print(buffer_upload);
  delay(1000);
  MQTT_SEND_DATA(buffer_upload);
  debug_print("extrayendo:");
  uint8_t data[200];
  if( counter > cmax ) counter = cmax;

  while(counter != 0){
    mem_read_data(data,counter);
    debug_print("mqtt send \r \n");
    debug_print(data);
    MQTT_SEND_DATA(data);
    delay(750);
    counter = counter - 1;
    mem_s_set_counter(&counter);

  }
    //El ultimo elemento a enviar
  mem_read_data(data,0);
  debug_print("mqtt send \r \n");
  debug_print(data);
  MQTT_SEND_DATA(data);
  delay(700);
  debug_print("Finalizo deployd \r\n");
  MQTT_SEND_DATA("Fin de transmicion");
  sim_deinit();     
  delay(700);
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
  debug_print("Init de program \r\n");
  sim_init();

  while(1);
  
  #if(0)
  sim_init();
  delay(1000);
  sim_echo_off();
  delay(1000);
  sim_version();
  delay(1000);
  

  sim_4g_connect();
  delay(1000);

  sim_mqtt_connect();
  delay(2000);
  sim7000g_mqtt_publish("GPS","INICIANDO TEST",14);
  delay(2000);
  sim7000g_mqtt_subscription("CMD");
  delay(2000);
  sim7000g_set_irt();
  delay(2000);
// Sub mqtt topic
  debug_print("into the while0");
while(1){
  debug_print(".");
  debug_print(sim_get_cmd());
  delay(2000);
}
#endif





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