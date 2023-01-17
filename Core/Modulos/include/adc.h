












/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"


/**
 * @brief Inicia el ADC1
 * 
*/
 void MX_ADC1_Init(void);


/**
 * @brief Obtener el valor del Adc 
*/
uint32_t get_adc(void);



#ifdef __cplusplus
}
#endif

#endif /* __ADC_H */

