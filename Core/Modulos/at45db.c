/***
 * 
 * 
*/



#include "at45db.h"





/***
 * 
 * 
*/
void at45db_init(){
    return 0;
}

/***
 * 
 * 
*/
void at45db_deinit(){
    return 0;
}



/**
 * @brief 
 * 
 */
uint8_t at45db_download_measure(uint8_t* buffer, uint8_t len){
    return 0;
}


/**
 * @brief 
 * 
 * @param buffer 
 * @param len 
 * @return ** uint8_t 
 */
uint8_t at45db_save_measure(uint8_t* buffer){
    return 0;
}


/**
 * @brief Get the status object
 * 
 * @return ** uint8_t 
 */
 uint8_t get_status(void){
    return 0;
 }


/**
 * @brief check the status register. If the device is bussy return 0 else return 1 
 * 
 * @return ** uint8_t 
 */
 uint8_t is_ready(void){
    return 0;
 }


/**
 * @brief  The memory page size for default its 264 bytes per page. 
 * 
 * @param size 265 bytes or 256 bytes
 * @return ** uint8_t 
 */
 uint8_t at45db_set_size_page( size_page_t size){
    return 0;
 }


/**
 * @brief Write in buffer 1, SRAM....volatile
 * 
 * @param data  bytes array 
 * @param len   lenght of the array
 * @param pos   Initial position into the buffer1
 * @return ** uint8_t 
 */
 uint8_t at45db_write_buffer1(uint8_t* data,uint8_t len, uint8_t pos){
    return 0;
 }


/**
 * @brief Read en buffer 1, en SRAM ...volatile
 * 
 * @param data  bytes array
 * @param len  lenght of the array
 * @param pos Initial position into the buffer1
 * @return ** uint8_t 
 */
uint8_t at45db_read_buffer1(uint8_t* data,uint8_t len, uint8_t pos){
    return 0;
}




/**
 * @brief Write in buffer 1, SRAM....volatile
 * 
 * @param data  bytes array 
 * @param len   lenght of the array
 * @param pos   Initial position into the buffer1
 * @return ** uint8_t 
 */
 uint8_t at45db_write_buffer2(uint8_t* data,uint8_t len, uint8_t pos){
    return 0;
 }


/**
 * @brief Read en buffer 1, en SRAM ...volatile
 * 
 * @param data  bytes array
 * @param len  lenght of the array
 * @param pos Initial position into the buffer1
 * @return ** uint8_t 
 */
uint8_t at45db_read_buffer2(uint8_t* data,uint8_t len, uint8_t pos){
    return 0;
}

/**
 * @brief 
 * 
 * @param data  data to write in page. You can write more than one page
 * @param len   length of the data
 * @param pag   page to write. AT45DB041E has 2048 pages
 * @param pos   Initial position in the page
 * @return ** uint8_t 
 */
uint8_t at45db_write_page(uint8_t* data, uint8_t len, uint32_t pag,uint8_t pos){
    return 0;
}


/**
 * @brief 
 * 
 * @param data  buffer to use. You can read more than one page
 * @param len   length of the data
 * @param pag   page to read. AT45DB041E has 2048 pages
 * @param pos   Initial position in the page
 * @return ** uint8_t  
 */
uint8_t at45db_read_page(uint8_t* data, uint8_t len, uint32_t pag,uint8_t pos){
    return 0;
}


/**
 * @brief Resume the device from the sleep mode
 * 
 * @return ** void 
 */
void at45db_resumen(){
    return 0;
}


/**
 * @brief  Sleep mode
 * 
 * @return ** void 
 */
void at45db_sleep(){
    return 0;
}
