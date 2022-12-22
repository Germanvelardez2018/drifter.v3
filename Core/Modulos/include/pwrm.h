


#include "core.h"




typedef enum{
    PWR_M_NULL = 0,     // ! El modulo no se inicializo aun
    PWR_M_TIMER = 1,    //! El Timmer es el elemento que debe desperta el micro
    PWR_M_RTC = 1       //! El RTC es el elemneto que debe despertar el micro

}pwrm_token_t;








