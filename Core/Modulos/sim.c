#include "sim.h"
#include "debug.h"


#include "uart.h"




#define CMD_OPEN_APN_TUENTI                          "AT+CNACT=1,\"internet.movil\"\r\n"
#define CMD_OPEN_APN_PERSONAL                        "AT+CNACT=1,\"datos.personal.com\"\r\n"

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


#define CMD_MQTT_COMMIT                                 "AT+SMCONN \r\n "
#define CMD_MQTT_SET_URL                            "AT+SMCONF=\"URL\",\"broker.hivemq.com\"\r\n"
#define CMD_ALL_CONFIG                                "AT+SMCONF=\"URL\",\"broker.hivemq.com\";SMCONF=\"QOS\",2 \r\n"
#define CMD_ALL_CONFI2                                "AT+SMCONF=\"URL\",\"broker.hivemq.com\";SMCONF=\"QOS\",2;SMCONN \r\n"




#define CMD_LOW_PWR_ON                              "AT+CPSMS=1,\"01000010\",\"00001010\"\r\n"
#define CMD_LOW_PWR_OFF                             "AT+CPSMS=0 \r\n"

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






#define SEND_CMD(function)                          {\
                                                        uint8_t ret = 0; \
                                                        while((ret = function)== 0)delay(1000);}\





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
    // uint8_t buff[200]={0};
    // sprintf(buff,"check (%s == %s)=>%d \r\n",response,SIM_BUFFER,ret);
    // debug_print(buff);
     return ret;
   
}







 uint8_t send_command(uint8_t* string_cmd,uint8_t* response_expected,uint32_t timeout, uint8_t print_flag){
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
    uint8_t ret = check_response(response_expected) ;
    return ret;
}




inline void sim_version(){
SEND_CMD(send_command(CMD_VERSION,CMD_OK,1000,1));
}


inline void sim_echo_off(){
SEND_CMD(send_command(CMD_ECHO_OFF,CMD_OK,1000,1));
}


inline void sim_mqtt_connect(){

    send_command(CMD_MQTT_SET_URL,CMD_OK,1000,1) ;
   // send_command(CMD_MQTT_SET_URL,CMD_OK,1000,1) ;
    send_command(CMD_MQTT_COMMIT,CMD_OK,1000,1) ;

}



inline void sim_4g_connect(){
send_command(CMD_OPEN_APN_PERSONAL,"+APP PDP: ACTIVE\r\n",1000,1);
   // SEND_CMD(send_command(CMD_OPEN_APN_PERSONAL,"+APP PDP: ACTIVE\r\n",1000,1));

}



inline void sim_sleep(){
    send_command(CMD_LOW_PWR_ON,CMD_OK,1000,1);
}




inline void sim_resumen(){
    send_command(CMD_LOW_PWR_OFF,CMD_OK,1000,1);
}