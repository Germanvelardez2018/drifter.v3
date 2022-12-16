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



uint8_t buffer[100]={0};







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

      sim_init();
      debug_print("Inicio programr\n");
      delay(20000);

    
   
      sim_echo_off();



      sim_version();



      uint8_t init = 0;
#define TIME_GPS_ON             (50000)
while(1){

    if(init) {
      // levanto el sim
      sim_init();
      debug_print("Inicio modulo sim nuevamente\r\n");
     

      
    // debug_print("sin 7000g config\r\n");  
      sim_echo_off();
      sim_version();
    }

    debug_print("encendiendo GPS...\r\n");
    sim_resumen();
    sim_gps_on();   // 80mA
    delay(TIME_GPS_ON);
    sim_gps_get_info(buffer,100);
    debug_print(sim_get_gps_data());


    debug_print("apagando  GPS y modulo...\r\n");
    //sim_gps_off();   //69mA
    //sim_sleep();
      

    sim_deinit();
      
    delay(25000);
   

  init = 1;

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
