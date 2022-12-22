
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRIFTER_STATE_H
#define __DRIFTER_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"


/* Inicializo el periferico que soporta el debug: UART2 por default
*/
 void drifter_init();


/* Desinicializo el periferico que soporta el drifter: UART2 por default
*/
void  drifter_deinit();





#ifdef __cplusplus
}
#endif

#endif /* __DRIFTER_STATE_H */