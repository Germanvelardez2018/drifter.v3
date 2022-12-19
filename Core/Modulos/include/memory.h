/**
 * @file mmap.h
 * @author German Velardez (gvelardez@inti.gob.ar)
 * @brief  Mapa de memoria
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 *
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MEMORY_H
#define __MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif



#include "core.h"
/* Includes ------------------------------------------------------------------*/





uint8_t mem_s_init();



uint8_t mem_s_deinit();



uint8_t mem_s_get_fsm_state(uint8_t* fsm_state);
uint8_t mem_s_set_fsm_state(uint8_t* fsm_state);



uint8_t mem_s_get_counter(uint8_t* counter);
uint8_t mem_s_set_counter(uint8_t* counter);



// Interval
uint8_t mem_s_get_interval(uint8_t* interval);
uint8_t mem_s_set_interval(uint8_t* interval);


uint8_t mem_s_get_max_amount_data(uint8_t* max_amount_data);
uint8_t mem_s_set_max_amount_data(uint8_t* max_amount_data);








uint8_t mem_s_get_x_offset(int16_t* x);


uint8_t mem_s_get_y_offset(int16_t* y);


uint8_t mem_s_get_z_offset(int16_t* z);




uint8_t mem_s_set_x_offset(int16_t x);


uint8_t mem_s_set_y_offset(int16_t y);


uint8_t mem_s_set_z_offset(int16_t z);






uint8_t mem_s_get_max_accelerometer_offset(int16_t* x,int16_t* y, int16_t* z );
uint8_t mem_s_set_max_accelerometer_offset(int16_t* x, int16_t* y,int16_t* z);



// Los datos se guardan como lifo
uint8_t mem_s_load_data(uint8_t* string );


// Para leer todos los datos almacenados recomienda usar dentro 
// de un bucle while con condicion (ret = mem_s_download_data(buffer) != STATUS__ERROR)
uint8_t mem_s_download_data(uint8_t* string);






uint8_t write_data(uint8_t* buffer, uint32_t page);






uint8_t read_data(uint8_t* buffer, uint32_t page);





void mem_full_clear();










#ifdef __cplusplus
}
#endif

#endif /* __MEMORY_H */