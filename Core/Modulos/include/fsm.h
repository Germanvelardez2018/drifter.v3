
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSM_H
#define __FSM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"


/* Inicializo la maquina de estados asociada a la aplicacion
*/
void fsm_init();

uint8_t fsm_get_state();

void fsm_set_state(uint8_t state);


#ifdef __cplusplus
}
#endif

#endif /* __FSM_H */
