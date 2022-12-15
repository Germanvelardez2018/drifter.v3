/***
 * 
 * 
 * 
*/


#include "core.h"


 void sim_init();



 void sim_deinit();



void sim_send_command(uint8_t* string_cmd,uint8_t* response_expected,uint32_t timeout, uint8_t print_flag);
