
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"


/* Inicializo el periferico que soporta el debug: UART2 por default
*/
 void debug_init();


/* Desinicializo el periferico que soporta el debug: UART2 por default
*/
void  debug_deinit();


void debug_print(uint8_t* buffer);



void debug_print_raw(uint8_t* buffer,size_t len);


#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H */
