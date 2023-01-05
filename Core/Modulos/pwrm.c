#include "pwrm.h"
#include "rtc.h"



#define SLEEP_INTERVAL()          {\
                                HAL_SuspendTick();\
                                HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);\
                                }\

#define RESUME_FROM_SLEEP()       {\
                                HAL_ResumeTick();}\



#define INTERVAL_TIME_H        (0)
#define INTERVAL_TIME_M        (0)
#define INTERVAL_TIME_S        (20)


PRIVATE void __update_interval(){

  uint8_t h,m,s ;
  // Obtengo time actual
  rtc_get_time(&h,&m,&s);
  // Aumento el intervalo
  h = h + INTERVAL_TIME_H;
  m = m + INTERVAL_TIME_M;
  s = s + INTERVAL_TIME_S;
  rtc_set_alarm(h,m,s);

}


// Interrupciones que despiertan el micro. Disponibles : Timer y RTC 



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   RESUME_FROM_SLEEP(); 
         
}



void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);  
  //RESUME_FROM_SLEEP();  
  HAL_ResumeTick();
}





void pwrm_init(){

  rtc_init();
 
}


void sleep_interval(){
  __update_interval();
  // sleep
  SLEEP_INTERVAL();


}