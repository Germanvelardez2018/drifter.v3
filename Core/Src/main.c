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

extern TIM_HandleTypeDef htim3;


#define CMD_OPEN_APN_TUENTI                          "AT+CNACT=1,\"internet.movil\"\r\n"
#define CMD_OPEN_APN_PERSONAL                        "AT+CNACT=1,\"datos.personal.com\"\r\n"
#define CMD_GET_APN                                  "AT+CNACT?\r\n"       
#define  CMD_AT                                        "AT\r\n"
#define  CMD_OK                                       "OK\r\n"
#define  CMD_VERSION                                   "ATI\r\n"
#define  CMD_ECHO_ON                                   "ATE1\r\n"
#define  CMD_ECHO_OFF                                  "ATE0\r\n"


static void init_pins_sim(){
  HAL_GPIO_WritePin(SIM7000G_BAT_ENA_GPIO_Port,SIM7000G_BAT_ENA_Pin,1);
  HAL_GPIO_WritePin(SIM7000G_PWRKEY_GPIO_Port,SIM7000G_PWRKEY_Pin,1);
  HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,1);

}



static void deinit_pins_sim(){
  HAL_GPIO_WritePin(SIM7000G_BAT_ENA_GPIO_Port,SIM7000G_BAT_ENA_Pin,0);
  HAL_GPIO_WritePin(SIM7000G_PWRKEY_GPIO_Port,SIM7000G_PWRKEY_Pin,0);
  HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,0);

}



static void init_peripherals(){


  MX_GPIO_Init();
  debug_init();
}


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  HAL_Init();
  clock_master_set(CLOCK_8MHZ);

  init_peripherals();

 

  debug_print("Inicio programa\r\n");
  init_pins_sim();
  sim_init();
  

  debug_print("envio comandos\r\n");  


 sim_version();

 sim_echo_off();
 sim_4g_connect();

 sim_mqtt_connect();




  while(1){
debug_print("test sim sleep:on\r\n");
sim_sleep();
delay(12000);
debug_print("test sim sleep:off\r\n");

sim_resumen();
delay(12000);
debug_print("apagamos modulos sim\r\n");
deinit_pins_sim();
delay(12000);



  }
 
  


  uint8_t counter = 0;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


    init_sim();

    counter ++;
    delay(10000);

    if(counter == 5){
    debug_print("run:0,5mhz\r\n");
    debug_deinit();
    MX_GPIO_Deinit();
    MX_TIM3_Init();
    HAL_DeInit();
    HAL_TIM_Base_Start_IT(&htim3);
    clock_master_set(CLOCK_1MHZ);
    HAL_SuspendTick();
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);    
    HAL_Init();
    HAL_ResumeTick();
    HAL_TIM_Base_Stop_IT(&htim3);
    clock_master_set(CLOCK_8MHZ); 
    init_peripherals();
     debug_print("sleep:off,  \r\n");
     counter = 0;
    }
   


    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* tim){

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
