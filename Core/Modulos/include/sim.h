
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIM_H
#define __SIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"


 void sim_init();



 void sim_deinit();



uint8_t sim_send_command(uint8_t* string_cmd,uint8_t* response_expected,uint32_t timeout, uint8_t print_flag);




 void sim_version();

 void sim_echo_off();
void sim_4g_connect();

 void sim_mqtt_connect();




 void sim_sleep();
  

 void sim_resumen();




  void sim_gps_on();


 void sim_gps_off();


 void sim_gps_get_info(uint8_t* gps_buffer,size_t len);


 void debug_print(uint8_t* buffer);


 uint8_t*   sim_get_gps_data();


#ifdef __cplusplus
}
#endif

#endif /* __SIM_H */


#include "core.h"

