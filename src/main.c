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
    uint8_t len,col,row,duty;
    uint8_t bufIndx = 0;
    uint8_t commandCounter = 0;
    char *dutyStr;
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
          bufIndx = 0;
          commandCounter = 0;
          
          if(strchr(buffer,'c')==NULL || strchr(buffer,'d')==NULL || strchr(buffer,'r')==NULL || strlen(buffer)!=10)
            UART_Printf("Invalid command");
          else{
            while(commandCounter < 3) {
              switch (buffer[bufIndx]) {
                  case 'c':
                      bufIndx++;
                      col = buffer[bufIndx] - '0';
                      break;
                  case 'r':
                      bufIndx++;
                      row = buffer[bufIndx] - '0';
                      break;
                  case 'd':
                      bufIndx++;
                      dutyStr = &buffer[bufIndx];
                      duty=atoi(dutyStr);
                      break;
              }
              commandCounter++;
              if(commandCounter < 3) {
                  while (buffer[bufIndx] != ',') {
                      bufIndx++;
                  }
                  bufIndx++;
              }

            }
            clearLEDS();
            setLED(row,col,duty);
        }

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

