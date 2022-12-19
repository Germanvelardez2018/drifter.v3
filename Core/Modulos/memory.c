/***
 * 
 * 
 * 
 * 
*/

#include "mapmem.h"
#include "memory.h"














PRIVATE status_t inline mem_resume(){
    at45db_resumen();
}


PRIVATE status_t inline mem_sleep(){
    at45db_sleep();
}


PRIVATE void inline mem_init(){
    at45db_init();
    
}








uint8_t mem_s_init(){
    return 0;
}



uint8_t mem_s_deinit(){
    return 0;
}



uint8_t mem_s_get_fsm_state(uint8_t* fsm_state){
    return 0;
}
uint8_t mem_s_set_fsm_state(uint8_t* fsm_state){
    return 0;
}



uint8_t mem_s_get_counter(uint8_t* counter){
    return 0;
}
uint8_t mem_s_set_counter(uint8_t* counter){
    return 0;
}



// Interval
uint8_t mem_s_get_interval(uint8_t* interval){
    return 0;
}
uint8_t mem_s_set_interval(uint8_t* interval){
    return 0;
}


uint8_t mem_s_get_max_amount_data(uint8_t* max_amount_data){
    return 0;
}
uint8_t mem_s_set_max_amount_data(uint8_t* max_amount_data){
    return 0;
}








uint8_t mem_s_get_x_offset(int16_t* x){
    return 0;
}


uint8_t mem_s_get_y_offset(int16_t* y){
    return 0;
}


uint8_t mem_s_get_z_offset(int16_t* z){
    return 0;
}




uint8_t mem_s_set_x_offset(int16_t x){
    return 0;
}


uint8_t mem_s_set_y_offset(int16_t y){
    return 0;
}


uint8_t mem_s_set_z_offset(int16_t z){
    return 0;
}






uint8_t mem_s_get_max_accelerometer_offset(int16_t* x,int16_t* y, int16_t* z ){
    return 0;
}
uint8_t mem_s_set_max_accelerometer_offset(int16_t* x, int16_t* y,int16_t* z){
    return 0;
}



// Los datos se guardan como lifo
uint8_t mem_s_load_data(uint8_t* string ){
    return 0;
}


// Para leer todos los datos almacenados recomienda usar dentro 
// de un bucle while con condicion (ret = mem_s_download_data(buffer) != STATUS__ERROR)
uint8_t mem_s_download_data(uint8_t* string){
    return 0;
}






uint8_t write_data(uint8_t* buffer, uint32_t page){
    return 0;
}






uint8_t read_data(uint8_t* buffer, uint32_t page){
    return 0;
}





void mem_full_clear(){

}
