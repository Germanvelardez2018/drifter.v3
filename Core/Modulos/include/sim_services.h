
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIM_SERVICES__H
#define __SIM_SERVICES__H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"

void sim_service_init();
uint8_t sim_get_upload_flag();
uint8_t sim_get_datasave_flag();




#ifdef __cplusplus
}
#endif

#endif /* __SIM_SERVICES__H */
