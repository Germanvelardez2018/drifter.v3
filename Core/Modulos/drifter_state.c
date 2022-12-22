#include "drifter_state.h"
#include "sim.h"
#include "pwrm.h"


PRIVATE drifter_t __DEVICE__ ;



/* Inicializo el periferico que soporta el debug: UART2 por default
*/
 void drifter_init(){

    __DEVICE__.mcu =        RUN;
    __DEVICE__.sim_module = SIM_OFF;
    __DEVICE__.conn =       CONN_4G_OFF;
    __DEVICE__.mqtt =       MQTT_DISCONNECTED;
    __DEVICE__.gps =        GPS_OFF;

 }


/* Desinicializo el periferico que soporta el drifter: UART2 por default
*/
void  drifter_deinit();



void drifter_slepp(){
    // SET parametro en estructura
    __DEVICE__.mcu = SLEEP;

    //Funcionalidad
}

void drifter_run(){
    // SET parametro en estructura
    __DEVICE__.mcu = RUN;


    //Funcionalidad
}

void drifter_gps_run(){
    // SET parametro en estructura
    __DEVICE__.gps = GPS_ON;

    //Funcionalidad
}

void drifter_gps_stop(){
    // SET parametro en estructura
    __DEVICE__.gps = GPS_OFF;


    //Funcionalidad
}

void drifter_4g_run(){
    // SET parametro en estructura
    __DEVICE__.conn = CONN_4G_ON;


    //Funcionalidad
}

void drifter_4g_stop(){
    // SET parametro en estructura

    __DEVICE__.conn = CONN_4G_OFF;

    //Funcionalidad
}


void drifter_mqtt_run(){
    // SET parametro en estructura
    __DEVICE__.mqtt = MQTT_CONNECTED;

    //Funcionalidad
}

void drifter_mqtt_stop(){
    // SET parametro en estructura
    __DEVICE__.mqtt = MQTT_DISCONNECTED;


    //Funcionalidad
}

