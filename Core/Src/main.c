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





/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  HAL_Init();

  
clock_master_set(CLOCK_8MHZ);
  
  MX_GPIO_Init();


  debug_init();
  /* USER CODE END 2 */

  debug_print("run:8mhz\r\n");

  uint8_t counter = 0;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    counter ++;
    delay(1000);

    if(counter == 10){
    debug_print("run:1mhz\r\n");
     
     clock_master_set(CLOCK_1MHZ);
     delay(10000);
     clock_master_set(CLOCK_8MHZ);
     debug_print("sleep:on\r\n");


     HAL_SuspendTick();


      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
      HAL_ResumeTick();
      clock_master_set(CLOCK_8MHZ);

      debug_print("sleep:off\r\n");
      counter = 0;
    }
   // debug_print("test\r\n");
   // HAL_GPIO_TogglePin(LED_PIN_GPIO_Port,LED_PIN_Pin);


    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
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
