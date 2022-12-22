


#include "core.h"






#define PWRM_SET_SLEEP_()                           {  HAL_SuspendTick(); \
                                                       HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);}\  


#define PWRM_SET_RUN_()                                HAL_ResumeTick()



