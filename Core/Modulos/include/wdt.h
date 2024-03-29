


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WDT_H
#define __WDT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"

/**
 *  Configuracion del WDT
*/
 void MX_IWDG_Init(void);



/***
 * @brief Reinicia el WDT 
*/
 void wdt_refresh();


#ifdef __cplusplus
}
#endif

#endif /* __WDT_H */