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
#include "sim_services.h"



#define INIT_MSG              "Init  drifter"
#define BUFFER_SIZE 250
uint8_t buffer[BUFFER_SIZE] = {"CONTENIDO INICIAL\r\n"};


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

  
  // Sensores

  // modulo SIm 

  // Mensaje inicial

  debug_print(INIT_MSG);


}



/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  app_init();
 
  
  while (1)
  {
    

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
