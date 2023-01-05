#include "sim.h"
#include "debug.h"


#include "uart.h"




#define EXAMPLO_GPS_FORMAT                              ("1,1,20221216181549.000,-34.576180,-58.516807,16.000,0.00,0.0,1,,2.8,3.0,0.9,,10,4,,,40,,␍␊")



#define CMD_OPEN_APN_TUENTI                          "AT+CNACT=1,\"internet.movil\"\r\n"
#define CMD_OPEN_APN_PERSONAL                        "AT+CNACT=1,\"datos.personal.com\"\r\n"
#define CMD_GET_APN                                  "AT+CNACT?\r\n"       


#define  CMD_AT                                       "AT\r\n"
#define  CMD_OK                                       "OK\r\n"
#define  CMD_VERSION                                  "ATI\r\n"
#define  CMD_ECHO_ON                                  "ATE1\r\n"
#define  CMD_ECHO_OFF                                 "ATE0\r\n"
#define  CMD_GET_SIGNAL                               "AT+CSQ\r\n"
#define  CMD_GPS_ON                                   "AT+CGNSPWR=1\r\n"
#define  CMD_GPS_OFF                                  "AT+CGNSPWR=0\r\n"
#define  CMD_GETGPSINFO                                "AT+CGNSINF\r\n"
#define  CMD_GETOPERATOR                               "AT+COPS?\r\n"


#define CMD_MQTT_COMMIT                                 "AT+SMCONN \r\n "
#define CMD_MQTT_SET_URL                            "AT+SMCONF=\"URL\",\"broker.hivemq.com\"\r\n"
#define CMD_ALL_CONFIG                                "AT+SMCONF=\"URL\",\"broker.hivemq.com\";SMCONF=\"QOS\",2 \r\n"
#define CMD_ALL_CONFI2                                "AT+SMCONF=\"URL\",\"broker.hivemq.com\";SMCONF=\"QOS\",2;SMCONN \r\n"

#define CMD_MQTT_PUBLISH                            "AT+SMPUB=\"%s\",\"%d\",2,1 \r\n" 
#define CMD_MQTT_SUBSCRIBE                           "AT+SMSUB=\"%s\",%d \r\n"   // topic , QoS
#define CMD_MQTT_UMSUBSCRIBE                         "AT+SMUMSUB=\"%s\"\r\n"   // topic , QoS


#define CMD_LOW_PWR_ON                              "AT+CPSMS=1,\"01000010\",\"00001010\"\r\n"
#define CMD_LOW_PWR_OFF                             "AT+CPSMS=0 \r\n"

extern UART_HandleTypeDef   huart1;


#define IS_EQUAL                                     (0)
#define SIM_UART                                    &huart1
#define SIM_TIMEOUT                                 1500
#define SIM_BUFFER_SIZE                             255
#define SIM_DEFAULT_TIMEOUT                         1000



PRIVATE uint8_t _SIM_BUFFER_[SIM_BUFFER_SIZE]={0};


#define SIM_BUFFER                                      _SIM_BUFFER_


#define UART_WRITE(buffer,len,timeout)               {\
                                                        HAL_UART_Transmit(SIM_UART,buffer,len,timeout); }\


#define UART_READ(buffer,len,timeout)                {\
                                                        memset(buffer,0,SIM_BUFFER_SIZE);\
                                                        (HAL_UART_Receive(SIM_UART,buffer,len,timeout)); } \



#define SEND_CMD(function,t)                          {\
                                                        uint8_t ret = 0; \
                                                        while((ret = function)== 0)delay(t);}\









      //+CGNSINF: eliminado de la string

#define OFFSET_GPS                                      12      //(strlen("+CGNSINF:"))
#define OFFSET_GPS_END                                   8


#define  GPS_PARSE_SIMPLE(buffer,len)                   {\
                                                    strncpy(buffer,(SIM_BUFFER),strlen(SIM_BUFFER));\
                                                    buffer[len-1]=0;}\


#define GPS_PARSE(buffer,len)                          {\
                                                   strncpy(buffer,(SIM_BUFFER+OFFSET_GPS),strlen((SIM_BUFFER+OFFSET_GPS)-OFFSET_GPS_END)); \
                                                    buffer[len-1]=0;}\                                                      



#define FLAG_PRINT_CHECK                        (0)




void sim_init(){
   
    HAL_GPIO_WritePin(SIM7000G_BAT_ENA_GPIO_Port,SIM7000G_BAT_ENA_Pin,1);
    HAL_GPIO_WritePin(SIM7000G_PWRKEY_GPIO_Port,SIM7000G_PWRKEY_Pin,1);
    MX_USART1_UART_Init();
    sim_echo_off();
}



void sim_deinit(){
   // HAL_UART_DeInit(SIM_UART);
    HAL_GPIO_WritePin(SIM7000G_BAT_ENA_GPIO_Port,SIM7000G_BAT_ENA_Pin,0);
    HAL_GPIO_WritePin(SIM7000G_PWRKEY_GPIO_Port,SIM7000G_PWRKEY_Pin,0);
}







PRIVATE uint8_t check_response(char* response){
   
     if(response == NULL ) return 0;
     uint32_t len_reponse = strlen(response);
     uint32_t len_buffer = strlen(SIM_BUFFER);
     uint32_t index = len_buffer - len_reponse ;  
     uint8_t ret = (strncmp(&(SIM_BUFFER[index]),response,len_reponse) == IS_EQUAL)?1:0;
     uint8_t buff[200]={0};

     #if (FLAG_PRINT_CHECK)
        sprintf(buff,"check (%s == %s)=>%d \r\n",response,SIM_BUFFER,ret);
        debug_print(buff);
     #endif
     return ret;
   
}







 uint8_t send_command(uint8_t* string_cmd,uint8_t* response_expected,size_t timeout, uint8_t print_flag){
    //Envio comando
   if(print_flag)  debug_print("=>");
   if(print_flag)  debug_print(string_cmd);
   UART_WRITE(string_cmd,strlen(string_cmd),timeout);     
   //if(print_flag)  debug_print("\n");
    // leo respuesta y almaceno en buffer SIM7000G
   UART_READ(SIM_BUFFER,SIM_BUFFER_SIZE,timeout);
   //if(print_flag)  debug_print("\n");
   if(print_flag)  debug_print(SIM_BUFFER);
   if(print_flag)  debug_print("<=\n");
    // checkeo buffer rx con respuesta esperada
    uint8_t ret = check_response(response_expected) ;

    return ret;
}




inline void sim_version(){
SEND_CMD(send_command(CMD_VERSION,CMD_OK,SIM_DEFAULT_TIMEOUT,0),2500);
}


inline void sim_echo_off(){
SEND_CMD(send_command(CMD_ECHO_OFF,CMD_OK,SIM_DEFAULT_TIMEOUT,0),2500);
}


inline void sim_mqtt_connect(){

    send_command(CMD_MQTT_SET_URL,CMD_OK,SIM_DEFAULT_TIMEOUT,1) ;
    send_command(CMD_MQTT_COMMIT,CMD_OK,SIM_DEFAULT_TIMEOUT,1) ;

}



inline void sim_4g_connect(){
send_command(CMD_OPEN_APN_PERSONAL,"+APP PDP: ACTIVE\r\n",SIM_DEFAULT_TIMEOUT,1);
}



inline void sim_sleep(){
    send_command(CMD_LOW_PWR_ON,CMD_OK,SIM_DEFAULT_TIMEOUT,1);
}




inline void sim_resumen(){
    send_command(CMD_LOW_PWR_OFF,CMD_OK,SIM_DEFAULT_TIMEOUT,1);
}


inline void sim_gps_on(){
    send_command(CMD_GPS_ON,CMD_OK,SIM_DEFAULT_TIMEOUT,1);

}


inline void sim_gps_off(){
    send_command(CMD_GPS_OFF,CMD_OK,SIM_DEFAULT_TIMEOUT,1);
}


inline void sim_gps_get_info(uint8_t* gps_buffer,size_t len){
   // debug_print('into gps_get info');
   send_command(CMD_GETGPSINFO,CMD_OK,SIM_DEFAULT_TIMEOUT,1);
   GPS_PARSE(gps_buffer,len);
  //
       
    
}


uint8_t*   sim_get_gps_data(){
    return SIM_BUFFER;
}



void sim7000g_mqtt_publish(uint8_t* topic, uint8_t* payload, uint8_t len_payload){
    
    uint8_t  buffer[100]={0};
    if( (topic != NULL) || (payload != NULL)){
        sprintf(buffer,CMD_MQTT_PUBLISH,topic,len_payload);    
        send_command(buffer,CMD_OK,650,1);
        send_command(payload,CMD_OK,650,1);
    }
    
}


void sim7000g_mqtt_subscription(uint8_t* topic){
    
    uint8_t  buffer[100]={0};
        sprintf(buffer,CMD_MQTT_SUBSCRIBE,topic,2);    
        send_command(buffer,CMD_OK,500,1);
    
}


void sim7000g_mqtt_unsubscription(uint8_t* topic){
    
    uint8_t  buffer[100]={0};
        sprintf(buffer,CMD_MQTT_UMSUBSCRIBE,topic);    
        SEND_COMMAND(buffer,CMD_OK,500);
    
}