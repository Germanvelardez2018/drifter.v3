/***
 * 
 * 
 * 
 * 
*/

#include "mapmem.h"
#include "memory.h"
#include "at45db.h"








PRIVATE  inline void mem_resume(){
    at45db_resumen();
}


PRIVATE  inline void mem_sleep(){
    at45db_sleep();
}


PRIVATE void inline mem_init(){
    at45db_init();
    
}





PRIVATE void mem_write_page(uint8_t* data, uint8_t len, uint16_t pag,uint8_t pos){
     at45db_write_page(data,  len, pag, pos);
}


PRIVATE void mem_read_page(uint8_t* data, uint8_t len, uint16_t pag,uint8_t pos){
     at45db_read_page(data,len,pag,pos);
}


PRIVATE void mem_read_buffer(uint8_t* data, uint8_t len,uint8_t pos){
     at45db_read_buffer2(data,len,pos);
}


PRIVATE void mem_write_buffer(uint8_t* data, uint8_t len,uint8_t pos){
     at45db_write_buffer2(data,len,pos);
}










void mem_s_init(){
    mem_init();
    mem_resume();

}



void mem_s_deinit(){
   at45db_deinit();
}



// 10 es una posicion randow dentro de la pagina (el ultimo param de mem_read_page)
void  mem_s_get_fsm_state(uint8_t* fsm_state){
    mem_resume();
    mem_read_page(fsm_state,1,MMAP_FSM_STATE,10);
    mem_sleep();
}

// 10 es una posicion randow dentro de la pagina (el ultimo param de mem_write_page)

void  mem_s_set_fsm_state(uint8_t* fsm_state){
    mem_resume();
    mem_write_page(fsm_state,1,MMAP_FSM_STATE,10);
    mem_sleep();
}




void  mem_s_set_counter(uint8_t* counter){
    at45db_resumen();
    mem_set_counter(counter);
    at45db_sleep();
}


void  mem_s_get_counter(uint8_t* counter){
    at45db_resumen();
    mem_get_counter(counter);
    at45db_sleep();
}




void mem_s_set_interval(uint8_t* interval){
    mem_resume();
    mem_write_page(interval,1,MMAP_INTERVAL,0);
    mem_sleep();
}


void mem_s_get_max_amount_data(uint8_t* max_amount_data){
    mem_resume();
    mem_read_page(max_amount_data,1,MMAP_MAX_AMOUNT_DATA,0);
    mem_sleep();
}


void mem_s_set_max_amount_data(uint8_t* max_amount_data){
 
    mem_resume();
    mem_write_page(max_amount_data,1,MMAP_MAX_AMOUNT_DATA,0);    
    mem_sleep();
}





void mem_s_get_x_offset(int16_t* x){
    mem_resume();
    mem_read_page(x,2,MMAP_OFFSET_ACELEROMETER_X,0);
    mem_sleep();
}
void mem_s_get_y_offset(int16_t* y){
    mem_resume();
    mem_read_page(y,2,MMAP_OFFSET_ACELEROMETER_Y,0);
    mem_sleep();
}

void mem_s_get_z_offset(int16_t* z){
    mem_resume();
    mem_read_page(z,2,MMAP_OFFSET_ACELEROMETER_Z,0);
    mem_sleep();
}



// La clave aqui es darle un formato al paso de uint8_t a 16 y respetarlo
void mem_s_set_x_offset(int16_t x){
    uint8_t buffer[2]= {x & 0xff, x >> 8 };
    mem_resume();
    mem_write_page(buffer,2,MMAP_OFFSET_ACELEROMETER_X,0);    
    mem_sleep();
}


void mem_s_set_y_offset(int16_t y){
    uint8_t buffer[2]= {y & 0xff, y >> 8 };
    mem_resume();
    mem_write_page(buffer,2,MMAP_OFFSET_ACELEROMETER_Y,0);    
    mem_sleep();
}


void mem_s_set_z_offset(int16_t z){
    uint8_t buffer[2]= {z & 0xff, z >> 8 };
    mem_resume();
    mem_write_page(buffer,2,MMAP_OFFSET_ACELEROMETER_Z,0);    
    mem_sleep();
}




void mem_s_get_max_accelerometer_offset(int16_t* x,int16_t* y, int16_t* z ){
   #define MEM_SIZE  (6)
   uint8_t data[MEM_SIZE]={0};
   mem_read_page(data,6,MMAP_OFFSET_ACELEROMETER,0);
   // Si ocurre error de lectura, enviar valor por default

    (*x) = (int16_t)(data[0] << 8 | data [1]);
    (*x) = (*x);
    (*y) = (int16_t)(data[2] << 8 | data [3]);
    (*y) = (*y);
    (*z) = (int16_t)(data[4] << 8 | data [5]);   
    (*z) = (*z);

    
}


void mem_s_set_max_accelerometer_offset(int16_t* x, int16_t* y,int16_t* z){
    #define MEM_SIZE  (6)
    uint8_t data[MEM_SIZE]={0};
    uint8_t* p_data;
    data[0] = ((*x) >> 8) & 0xff;
    data[1] = (*x) & 0xff;
    data[2] = ((*y) >> 8) & 0xff;
    data[3] = (*y) & 0xff;
    data[4] = ((*z) >> 8) & 0xff;
    data[5] = (*z) & 0xff;  
    // |   x H L       |      y H L           |       z H L          |
   mem_write_page(data,MEM_SIZE,MMAP_OFFSET_ACELEROMETER,0);
   // Si ocurre error de lectura, enviar valor por default    
}





void mem_full_clear(){
    at45db_full_erase_memory();
}


//



void   mem_write_data(uint8_t* buffer, uint32_t page){
    uint8_t len =  strlen(buffer)+1;
    uint8_t _len = len;
    at45db_resumen();
    at45db_write_page(&(_len),1,(page+ MMAP_DATA_OFSSET),0);
    at45db_write_page(buffer ,len,(page+ MMAP_DATA_OFSSET),1);
    at45db_sleep();
}


void   mem_read_data(uint8_t* buffer, uint32_t page){
    uint8_t len=0;
    at45db_resumen();
    at45db_read_page((&len),1,(page + MMAP_DATA_OFSSET),0);
    at45db_read_page(buffer ,len,(page + MMAP_DATA_OFSSET),1);
    at45db_sleep();
}



