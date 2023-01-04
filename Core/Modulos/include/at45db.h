/**
 * @file at45db.h
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
#ifndef __AT45DB_H
#define __AT45DB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"








/*-----------------------------------------------------------------------------*/




/***
 * 
 * 
*/
void at45db_init();

/***
 * 
 * 
*/
void at45db_deinit();







/**
 * @brief Write in buffer 1, SRAM....volatile
 * 
 * @param data  bytes array 
 * @param len   lenght of the array
 * @param pos   Initial position into the buffer1
 * @return ** uint8_t 
 */
 void at45db_write_buffer1(uint8_t* data,uint8_t len, uint8_t pos);


/**
 * @brief Read en buffer 1, en SRAM ...volatile
 * 
 * @param data  bytes array
 * @param len  lenght of the array
 * @param pos Initial position into the buffer1
 * @return ** uint8_t 
 */
void at45db_read_buffer1(uint8_t* data,uint8_t len, uint8_t pos);




/**
 * @brief Write in buffer 1, SRAM....volatile
 * 
 * @param data  bytes array 
 * @param len   lenght of the array
 * @param pos   Initial position into the buffer1
 * @return ** uint8_t 
 */
 void at45db_write_buffer2(uint8_t* data,uint8_t len, uint8_t pos);


/**
 * @brief Read en buffer 1, en SRAM ...volatile
 * 
 * @param data  bytes array
 * @param len  lenght of the array
 * @param pos Initial position into the buffer1
 * @return ** uint8_t 
 */
void at45db_read_buffer2(uint8_t* data,uint8_t len, uint8_t pos);

/**
 * @brief 
 * 
 * @param data  data to write in page. You can write more than one page
 * @param len   length of the data
 * @param pag   page to write. AT45DB041E has 2048 pages
 * @param pos   Initial position in the page
 * @return ** void
 */
void at45db_write_page(uint8_t* data, uint8_t len, uint32_t pag,uint8_t pos);


/**
 * @brief 
 * 
 * @param data  buffer to use. You can read more than one page
 * @param len   length of the data
 * @param pag   page to read. AT45DB041E has 2048 pages
 * @param pos   Initial position in the page
 * @return ** void 
 */
void at45db_read_page(uint8_t* data, uint8_t len, uint32_t pag,uint8_t pos);


/**
 * @brief Resume the device from the sleep mode
 * 
 * @return ** void 
 */
void at45db_resumen();


/**
 * @brief  Sleep mode
 * 
 * @return ** void 
 */
void at45db_sleep();







#ifdef __cplusplus
}
#endif

#endif /* __AT45DB_H */