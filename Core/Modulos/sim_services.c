#include "sim_services.h"
#include "sim.h"
#include "memory.h"

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



void sim_service_on(){
    sim_init();
   
}


void sim_service_off(){
    sim_deinit();
   
}

