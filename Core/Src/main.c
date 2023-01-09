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



#define SENSOR_FORMAT "gps: %s\n sensor: %s"
#define INIT_MSG              "Init  drifter \r\n"
#define CHECK_MSG             "Check"
#define CHECK_MSG_LEN         (strlen(CHECK_MSG))
#define CHECK_TOPIC           "CHECK"
#define BUFFER_SIZE 250

#define BLINK_DEBUG                         (1)


PRIVATE uint8_t counter = 0;          //  Contador de muestras almacenadas
PRIVATE uint8_t cmax = 0;             // Maximo valor del contador de muestras almacenadas
PRIVATE uint8_t counter_interval = 0;
PRIVATE uint8_t cmax_interval = 0;   // Contador maximo de intervalos
uint8_t buffer[BUFFER_SIZE] = {"CONTENIDO INICIAL\r\n"};


uint8_t buffer_upload[200];
#define MQTT_SEND_CMD(msg)      sim7000g_mqtt_publish("CHECK", msg, strlen(msg))
#define MQTT_SEND_DATA(msg)     sim7000g_mqtt_publish("DATA", msg, strlen(msg))



#define TEST_MSG                      "************************\\
                                        *************************\
                                        **************************\
                                        ***************************\
                                        ****************************\
                                        *****************************\
                                        *************************\
                                        **************************\
                                        ***************************\
                                        ****************************\
                                        *****************************\
                                        *************************\
                                        **************************\
                                        ***************************\
                                        ****************************\
                                        *****************************\
                                        *************************\
                                        **************************\
                                        ***************************\
                                        ****************************\
                                        *****************************\
                                        *************************\
                                        **************************\
                                        ***************************\
                                        ****************************\
                                        *****************************\
                                        ****************************\
                                        *******+"\


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

  counter = 8;
  cmax = 2;
  cmax_interval = 2;
  //mem_s_set_counter(&counter);
  //mem_s_set_max_amount_data(&cmax);
  //mem_s_set_cmax_interval(&cmax_interval);

  //Cargo parametros desde Flash externa
  mem_s_get_counter(&counter);
  mem_s_get_max_amount_data(&cmax);
  mem_s_get_cmax_interval(&cmax_interval);
  
  buffer[100];
  sprintf(buffer,"counter %d cmax%d cinterval%d cimax%d \r\n",counter,cmax,counter_interval,cmax_interval);
  debug_print(buffer);


}


PRIVATE void check_routine(){

  // Encender el modulo
  sim_init();
  // Conectarse a servidor
  wait_for_sim();
  sim_4g_connect();
  sim_mqtt_connect();
  // Enviar mensaje de check
  MQTT_SEND_CMD(CHECK_MSG);
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
 // MQTT_SEND_CMD(buffer_upload);
  debug_print("extrayendo:");

  uint8_t* data = mem_s_get_all_data(counter);
  debug_print("mqtt send:");
  debug_print(data);

  MQTT_SEND_DATA(data);

  sim_deinit();

}

PRIVATE void save_data_routine(){
  sim_init();
  sim_gps_on();
  mem_s_get_counter(&counter);
  uint8_t sensor[80];
  uint8_t gps[100];
  mpu6050_get_measure(sensor,80);
  
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
