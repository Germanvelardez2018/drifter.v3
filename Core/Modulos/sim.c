#include "sim.h"
#include "debug.h"


#include "uart.h"






#define  CMD_AT                                        "AT\r\n"
#define  CMD_OK                                       "OK\r\n"
#define  CMD_VERSION                                   "ATI\r\n"
#define  CMD_ECHO_ON                                   "ATE1\r\n"
#define  CMD_ECHO_OFF                                  "ATE0\r\n"
#define  CMD_GET_SIGNAL                                "AT+CSQ\r\n"
#define  CMD_GPS_ON                                "AT+CGNSPWR=1\r\n"
#define  CMD_GPS_OFF                               "AT+CGNSPWR=0\r\n"
#define  CMD_GETGPSINFO                                "AT+CGNSINF\r\n"
#define  CMD_GETOPERATOR                               "AT+COPS?\r\n"




extern UART_HandleTypeDef   huart1;


#define IS_EQUAL                                     (0)
#define SIM_UART                                    &huart1
#define SIM_TIMEOUT                                 1500
#define SIM_BUFFER_SIZE                             200





#define UART_WRITE(buffer,len,timeout)            {\
                                                    HAL_UART_Abort_IT(SIM_UART); \
                                                    HAL_UART_Transmit(SIM_UART,buffer,len,timeout); }\


  #define UART_READ(buffer,len,timeout)                  {\
                                                    HAL_UART_Abort_IT(SIM_UART); \
                                                    (HAL_UART_Receive(SIM_UART,buffer,len,timeout)); } \




PRIVATE uint8_t buffer[SIM_BUFFER_SIZE]={0};


#define SIM_BUFFER                          buffer


void sim_init(){
    MX_USART1_UART_Init();
}



void sim_deinit(){
    HAL_UART_DeInit(SIM_UART);
}








PRIVATE uint8_t check_response(char* response){
   
     if(response == NULL ) return 0;
     uint32_t len_reponse = strlen(response);
     uint32_t len_buffer = strlen(SIM_BUFFER);
     uint32_t index = len_buffer - len_reponse ;  
     uint8_t ret = (strncmp(&(SIM_BUFFER[index]),response,len_reponse) == IS_EQUAL)?1:0;
   
}







 void send_command(uint8_t* string_cmd,uint8_t* response_expected,uint32_t timeout, uint8_t print_flag){
    //Envio comando
   if(print_flag)  debug_print("cmd enviado:");
   if(print_flag)  debug_print(string_cmd);
   UART_WRITE(string_cmd,strlen(string_cmd),timeout);     
   if(print_flag)  debug_print("\n");
    // leo respuesta y almaceno en buffer SIM7000G
    UART_READ(SIM_BUFFER,SIM_BUFFER_SIZE,timeout);
   if(print_flag)  debug_print("respuesta leida:");
   if(print_flag)  debug_print(SIM_BUFFER);
   if(print_flag)  debug_print("\n");
    // checkeo buffer rx con respuesta esperada
   check_response(response_expected) ;
   if(print_flag)  debug_print("\n");
   
}