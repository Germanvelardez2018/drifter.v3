#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t* data[12]={
    "do 1:",
    "do 2:",
    "do 3:",
    "do 4",
    "do 5",
    "do 6",
    "do 7",
    "do 8",
    "do 9",
    "do 10",
    "do 11",
    "do 12"
};




uint8_t sim_buffer_512b(uint8_t *buffer, uint32_t len)
{
   uint8_t pos = 0;
   uint8_t c = 11;
   //READ memory
   uint32_t llen =0;
   //printf("debug: ./for\r\n");
   for( int run = 1; run == 1;)
   {
    llen = strlen(data[c]);
    printf("dato extraido:%s\r\n",data[c]);
     if((pos + llen) < (len-1)){
        sprintf(&(buffer[pos])," %s%c",data[c],'\n');
        pos = pos +llen+1;
        printf("pos actual:%d\r\n",pos);
        if((c - 1)!= 0){
            c--;
        }
        else{run = 0;}
    }
    else{
        run = 0;
    }
    buffer[len-1]= 0;
   }
    return pos;
}


int main(){


    for(int i = 0; i < 10 ; i++){
//printf("%s \r\n",data[i]);
    }

   uint8_t b[500];
   int pos =  sim_buffer_512b(b, 500);
    printf("buffer final:%s\r\n",b);
    printf("pos:%d\r\n",pos);
    return 0;
}