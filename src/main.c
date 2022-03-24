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
    uint8_t noOfCommandedCols = 0;
    char *dutyStr;
    char *demandStr;
    long demand;

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
          noOfCommandedCols = 0;
          
          if(1==0)
            UART_Printf("Invalid command");
          else{
            while(commandCounter < 2) {
              switch (commandCounter) {
                  case 0:
                      demandStr = &demandStr[bufIndx];
                      demand = atol(demandStr);
                      break;
                  case 1:
                      dutyStr = &buffer[bufIndx];
                      duty = atoi(dutyStr);
                      break;
              }
              commandCounter++;
              
              //Iterate through to next comma
              if(commandCounter < 2) {
                  while (buffer[bufIndx] != ',') {
                      bufIndx++;
                  }
                  bufIndx++;
              }

            }

            // Split long into bytes
            byte0= demand & 0x0000FF;
            byte1= (demand & 0x00FF00)>>8;
            byte2= (demand & 0xFF0000)>>16;

            noOfCommandedCols += countSetBits(byte0);
            noOfCommandedCols += countSetBits(byte1);
            noOfCommandedCols += countSetBits(byte2);

            if(noOfCommandedCols > MAX_COLS)
              UART_Printf("Too many LEDs\n");
            else
              setLED(byte0,byte1,byte2,duty);
          }

        }
    }
    return (0);

}

