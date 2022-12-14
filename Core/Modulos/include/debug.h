












/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"



 void debug_init();




 void debug_print(uint8_t* buffer);

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H */
