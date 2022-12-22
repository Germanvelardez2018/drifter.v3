#include "sim_services.h"



PRIVATE    uint8_t CSIM = 0;        // Contador sim, aumenta en un con cada funcion iniciada: 
                                    //gps, mqtt, etc. Si esta en 0 apagar modulo

#define __CSIM_INC__()                  (CSIM++)
#define __CSIM_DEC__()                  (CSIM--)




void sim_service_init()



void sim_services_gps_on();





void sim_services_gps_off();