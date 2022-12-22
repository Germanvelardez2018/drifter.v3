#include "pwrm.h"
#include "drifter_state.h"

#define _CHECK_STATUS_()      (*(get_device()->mcu))



// Interrupciones que despiertan el micro. Disponibles : Timer y RTC 



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // led encendido en modo run  
  //toogle le consume 1mA
  // HAL_GPIO_TogglePin(LED_GPIO_Port, GPIO_PIN_2);
         
}



void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
  
}






