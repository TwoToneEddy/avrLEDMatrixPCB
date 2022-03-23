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
    uint8_t len,byte0,byte1,byte2,duty;
    uint8_t bufIndx = 0;
    uint8_t commandCounter = 0;
    char *dutyStr;
    char *byte0Str;
    char *byte1Str;
    char *byte2Str;
    UART_Init(9600);
    configurePWM();
    configureSPI();
    _delay_ms(100);
    setDuty(0);


    UART_Printf("Board initialised\n");
    while(1)
    {
        len = UART_RxString(buffer);
        if(len > 1){
          UART_Printf("Recieved: %s, len: %d\n",buffer,len);
          bufIndx = 0;
          commandCounter = 0;
          
          if(1==0)
            UART_Printf("Invalid command");
          else{
            while(commandCounter < 4) {
              switch (commandCounter) {
                  case 0:
                      byte0Str = &buffer[bufIndx];
                      byte0 = atoi(byte0Str);
                      break;
                  case 1:
                      byte1Str = &buffer[bufIndx];
                      byte1 = atoi(byte1Str);
                      break;
                  case 2:
                      byte2Str = &buffer[bufIndx];
                      byte2 = atoi(byte2Str);
                      break;
                  case 3:
                      dutyStr = &buffer[bufIndx];
                      duty = atoi(dutyStr);
                      break;
              }
              commandCounter++;
              
              //Iterate through to next comma
              if(commandCounter < 4) {
                  while (buffer[bufIndx] != ',') {
                      bufIndx++;
                  }
                  bufIndx++;
              }

            }
            //clearLEDS();
            setLED(byte0,byte1,byte2,duty);
        }

          if(buffer[0] == 'T'){
            UART_Printf("Running full LED test\n");
          }

          if(buffer[0] == 't'){
            UART_Printf("Running fast LED test\n");
          }

        }
    }
    return (0);



}

