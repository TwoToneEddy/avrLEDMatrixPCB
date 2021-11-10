#include "main.h"
/*

Pinout:

  PWM Row:
  0 PD6
  1 PD5
  2 PB1
  3 PB2
  4 PB3
  5 PD3

  Sink Col:
  0 PB0
  1 PB4
  2 PB5
  3 PD2
  4 PD4
  5 PD7

  Serial:
  FT232RL TXD PD0
  FT232RL RXD PD1


*/



int main(void) {


    char buffer[64];
    uint8_t len;
    UART_Init(9600);
    
    
    configurePWM();
    configureDigitalOutputs();
    qtestLeds();

    UART_Printf("Board initialised\n");
    while(1)
    {
        len = UART_RxString(buffer);
        if(len > 1){
          UART_Printf("Recieved: %s, len: %d\n",buffer,len);

          if(buffer[0] == 'T'){
            UART_Printf("Running full LED test\n");
            testLeds(1,1);
          }

          if(buffer[0] == 't'){
            UART_Printf("Running fast LED test\n");
            testLeds(10,0);
          }

        }
    }
    return (0);



}

