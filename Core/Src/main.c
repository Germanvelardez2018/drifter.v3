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
#define INIT_MSG              "Init  drifter \r\n"
#define CHECK_MSG             "Check"
#define CHECK_MSG_LEN         (strlen(CHECK_MSG))
#define CHECK_TOPIC           "CHECK"
#define BUFFER_SIZE           220
#define MQTT_SEND_CHECK()      sim7000g_mqtt_publish("CHECK", get_state_device(), strlen(get_state_device()))
#define MQTT_SEND_DATA(msg)     sim7000g_mqtt_publish("DATA", msg, strlen(msg))



PRIVATE uint8_t buffer[BUFFER_SIZE] = {"CONTENIDO INICIAL\r\n"};
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
  clock_master_set(CLOCK_8MHZ);
  MX_GPIO_Init();
  // Debug
  debug_init();
  // Memoria externa
  mem_s_init();
  // sensor
  mpu6050_init();

  pwrm_init();
  // FSM
  fsm_init();
  // Mensaje inicial

  debug_print(INIT_MSG);


  //Solo para pruebas de configuracion
 // counter = 8;
 // cmax = 10;
 // cmax_interval = 3;
  //mem_s_set_counter(&counter);
  //mem_s_set_max_amount_data(&cmax);
  //mem_s_set_cmax_interval(&cmax_interval);
  //Cargo parametros desde Flash externa
 
  debug_print(get_state_device());


}


PRIVATE void check_routine(){

  // Encender el modulo
  sim_init();
  // Conectarse a servidor
  wait_for_sim();
  sim_4g_connect();
  sim_mqtt_connect();
  // Enviar mensaje de check
  MQTT_SEND_CHECK();
  sim_deinit();

}



PRIVATE void upload_routine(){

  sim_init();
  wait_for_sim();
  sim_4g_connect();
  sim_mqtt_connect();
  // transmito los datos
   if (cmax < counter)
  {
    counter = cmax;
    mem_s_set_counter(&counter);
  }
  sprintf(buffer_upload, "Extraer :%d datos\n", counter);
  debug_print(buffer_upload);
  MQTT_SEND_CHECK();
  debug_print("extrayendo:");


  uint8_t data[200];
if( counter > cmax ) counter = cmax;
   

    for(uint32_t index= 0; index < counter; index ++){
    
    mem_read_data(data,index);
    debug_print("mqtt send \r \n");
    debug_print(data);
    MQTT_SEND_DATA(data);
    delay(500);
    }
   debug_print("Finalizo deployd \r\n");
  sim_deinit();

}

PRIVATE void save_data_routine(){
  sim_init();
  sim_gps_on();
  mem_s_get_counter(&counter);
  uint8_t sensor[70];
  uint8_t gps[100];
  mpu6050_get_measure(sensor,70);
  
  wait_for_gps();
  // Obtengo gps
  sim_gps_get_info(gps,100);
  sprintf(buffer, SENSOR_FORMAT, gps, sensor);
  debug_print(buffer);
  mem_write_data(buffer, counter);
  counter = counter + 1;
  mem_s_set_counter(&counter);
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