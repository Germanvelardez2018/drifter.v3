#include "pwrm.h"
#include "rtc.h"
#include "wdt.h"
#include "timer.h"

#define SLEEP_INTERVAL()          {\
                                HAL_SuspendTick();\
                                HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);\
                                }\

#define RESUME_FROM_SLEEP()       {\
                                HAL_ResumeTick();}\



#define INTERVAL_TIME_H         (0)
#define INTERVAL_TIME_M         (5)
#define INTERVAL_TIME_S         (0)
#define WAIT_FOR_GPS_TIME_S     (40)
#define WAIT_FOR_SIMCOM         (25)


// Se utiliza para reiniciar wdt
extern TIM_HandleTypeDef htim3;


PRIVATE uint8_t __SLEEP__ = 0; 


PRIVATE void __wait_for_sim(){
   uint8_t h,m,s ;
  // Obtengo time actual
  rtc_get_time(&h,&m,&s);
  // Aumento el intervalo
  s = s + WAIT_FOR_SIMCOM;
  rtc_set_alarm(h,m,s);
  SLEEP_INTERVAL() ;
}


PRIVATE void __wait_for_gps(){
   uint8_t h,m,s ;
  // Obtengo time actual
  rtc_get_time(&h,&m,&s);
  // Aumento el intervalo
  s = s+ WAIT_FOR_GPS_TIME_S;
  rtc_set_alarm(h,m,s);
  SLEEP_INTERVAL() ;
}



PRIVATE void timer_init(){
  //MX_IWDG_Init();
  MX_TIM3_Init();
  HAL_TIM_Base_Start_IT(&htim3);
  wdt_refresh();

}



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
  // Despertar
   RESUME_FROM_SLEEP();
   //Reset  
   wdt_refresh();
   HAL_GPIO_TogglePin(LED_GPIO_Port, GPIO_PIN_2);
   //Si estaba durmiendo, volver a dormir
   if(__SLEEP__)    SLEEP_INTERVAL() ;
}



void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
    RESUME_FROM_SLEEP();
   // wdt_refresh();

    // Despierta
    __SLEEP__ = 0;

}


void pwrm_init(){
  rtc_init();
  //timer_init();
}


void sleep_interval(){
  __update_interval();
  // sleep
  __SLEEP__ = 1;
  SLEEP_INTERVAL();
}


void wait_for_gps(){

  __wait_for_gps();
  __SLEEP__ = 1;
  SLEEP_INTERVAL();
}


void wait_for_sim(){
  
  __wait_for_sim();
  __SLEEP__ = 1; 
  SLEEP_INTERVAL();
    

}


