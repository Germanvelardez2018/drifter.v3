
#include "uart.h"
#include "debug.h"



extern UART_HandleTypeDef   huart2;

#define DEBUG_UART          &huart2
#define DEBUG_TIMEOUT       (500)



inline void debug_init(){
    MX_USART2_UART_Init();
}




inline void debug_print(uint8_t* buffer){
    HAL_UART_Transmit(DEBUG_UART,buffer,strlen((char*)buffer),DEBUG_TIMEOUT);
}