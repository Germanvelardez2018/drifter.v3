/***
 * 
 * 
 * 
*/


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