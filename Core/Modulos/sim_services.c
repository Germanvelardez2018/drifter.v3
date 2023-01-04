#include "sim_services.h"
#include "memory.h"

#define   COUNTER_DEFAULT                               0
#define   COUNTER_MAX_DEFAULT                           0
#define   SENSOR_COUNTER_DEFAULT                        0
#define   SENSOR_CMAX_DEFAULT                     10



PRIVATE    uint8_t __SIM_COUNTER__        = COUNTER_DEFAULT;                 // se recarga cada intervalo check
PRIVATE    uint8_t __SIM_CONTER_MAX__     = COUNTER_MAX_DEFAULT;
PRIVATE    uint8_t __SIM_SENSOR_COUNTER__ = SENSOR_COUNTER_DEFAULT;
PRIVATE    uint8_t __SIM_SENSOR_CMAX__    = SENSOR_CMAX_DEFAULT;
PRIVATE    uint8_t FLAG_UPLOAD          = 0;
PRIVATE    uint8_t FLAG_SAVE_DATA           = 0;






#define  __CHECK_COUNTER_MAX__           (3)      // Obtener el Contador maximo de memoria
#define  __CHECK_GET_COUNTER__           (__SIM_COUNTER__)       // Obtener contador real del gps en memoria   
#define  __CHECK_GET_SENSOR_COUNTER__    (mem_s_get_counter(&__SIM_SENSOR_COUNTER__))
#define  __CHECK_GET_SENSOR_CMAX__       (mem_s_get_max_amount_data(&__SIM_SENSOR_CMAX__)  )

//   Inicio el modulo 4g ( demora 30s en encender)
//      si necesito chequear GPS (muestreo) lo inicio y sigo
//              conecto con servidor
//                  si tengo flag download
//                                  download
//                  sino    envio check
//              desconecto con servidor
//
//              por ultimo...obtengo muestra de gps si toca
//                              y almaceno en memoria flash



void sim_service_init(){

    // Obtengo los parametros desde memoria flash
    __SIM_CONTER_MAX__ = __CHECK_COUNTER_MAX__;
    __SIM_COUNTER__    = __CHECK_GET_COUNTER__;
    __CHECK_GET_SENSOR_COUNTER__;
    __CHECK_GET_SENSOR_CMAX__;
 
   // si el contador llega al maximo, es momento de realizar una muestra de GPS (IMPLICA ENCENDER GPS)
    if(__SIM_COUNTER__ == __SIM_CONTER_MAX__) FLAG_SAVE_DATA = 1; 

    // Si se han alcanzado el maximo de muestra, es momento de upload
    if(__SIM_SENSOR_COUNTER__ == __SIM_SENSOR_CMAX__) FLAG_UPLOAD = 1; 
}



uint8_t sim_get_upload_flag(){
    return FLAG_UPLOAD;
}
uint8_t sim_get_datasave_flag(){
    return FLAG_SAVE_DATA;
}

void sim_services_gps_on(){

}


void sim_services_gps_off(){
    
}