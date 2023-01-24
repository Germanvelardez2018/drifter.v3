
#include "uart.h"
#include "debug.h"



extern UART_HandleTypeDef   huart2;

#define DEBUG_UART          &huart2
#define DEBUG_TIMEOUT       (500)
#define DEBUG_ON            1


inline void debug_init(){
    #if (DEBUG_ON == 1)
    MX_USART2_UART_Init();
    #endif   
}


inline void debug_deinit(){
    #if (DEBUG_ON == 1)
    HAL_UART_DeInit(DEBUG_UART);
    #endif
    
}


inline void debug_print(uint8_t* buffer){
    #if (DEBUG_ON == 1)
    HAL_UART_Transmit(DEBUG_UART,buffer,strlen((char*)buffer),DEBUG_TIMEOUT);
    #endif
    
}


inline void debug_print_raw(uint8_t* buffer,size_t len){
    #if (DEBUG_ON == 1)
    HAL_UART_Transmit(DEBUG_UART,buffer,len,DEBUG_TIMEOUT);
    #endif
    
}