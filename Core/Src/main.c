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

extern TIM_HandleTypeDef htim3;

#define BUFFER_SIZE 250
uint8_t buffer[BUFFER_SIZE] = {"CONTENIDO INICIAL\r\n"};

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
  mem_s_init();
  debug_print("\r\n\t\t Inicio programa\r\n");
  debug_print("test memoria externa \r\n");

  // mpu6050_init();
  debug_print("\r\ncontenido inicial del buffer: ");
  debug_print(buffer);

  // memset(buffer, 0, BUFFER_SIZE);
  debug_print(" \r\nEscribir memoria externa:\r\n");

  mem_write_data("!hola mundo, test de escritura \r\n", 0);
  // debug_print('\r\nLeo buffer');
  memset(buffer, 0, 250);
  mem_read_data(buffer, 0);
  debug_print("buffer:");

  debug_print(buffer);

 

  debug_print("\r\nentrando al while \r\n");
  while (1)
  {
    
  mem_write_data("!hola mundo, test de escritura \r\n", 0);
  // debug_print('\r\nLeo buffer');
  memset(buffer, 0, 250);
  mem_read_data(buffer, 0);
  debug_print("buffer:");

  debug_print(buffer);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    delay(2500);
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

#ifdef USE_FULL_ASSERT
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
