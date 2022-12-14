


#include <stdiont.h>




typedef enum{
    PWR_M_NULL = 0,     // ! El modulo no se inicializo aun
    PWR_M_TIMER = 1,    //! El Timmer es el elemento que debe desperta el micro
    PWR_M_RTC = 1       //! El RTC es el elemneto que debe despertar el micro

}pwr_manager_token_t;






void pwrm_set_delay_ms(uint32_t delay);

void pwrm_set_delay_rtc(uint8 h, uint8_t m, uint8_t s);




