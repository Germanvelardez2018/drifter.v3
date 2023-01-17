#include "wdt.h"




IWDG_HandleTypeDef hiwdg;


#define  FULL_TIME                                        (4095)//4095
#define  WDT_TIME                                         (4095)


uint8_t __WDT_ON__ = 0;

 void MX_IWDG_Init(void)
{

 
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Reload = WDT_TIME;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  __WDT_ON__ = 1;
 

}



 void wdt_refresh(){
  if(__WDT_ON__)HAL_IWDG_Refresh(&hiwdg);
 }
