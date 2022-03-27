#include "main.h"

int main(void) {

    char buffer[64];
    uint8_t len,byte0,byte1,byte2,duty;
    uint8_t bufIndx = 0;
    uint8_t commandCounter = 0;
    uint8_t noOfCommandedCols = 0;
    uint8_t invalidCommand = 0;
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

          bufIndx = 0;
          commandCounter = 0;
          noOfCommandedCols = 0;
          invalidCommand = 0;

          // Set to invalid values
          //demand = -1;
          duty = 255;
        
          
          while(commandCounter < 2) {
            switch (commandCounter) {
                case 0:
                    demandStr = &buffer[bufIndx];
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

          if((demand > 1835008) || (demand < 0) || (duty > 100) || (noOfCommandedCols > MAX_COLS))
            UART_Printf("Invalid command\n");
          else{
            UART_Printf("OK\r\n");
            setLED(byte0,byte1,byte2,duty);
          }
          

        }
    }
    return (0);

}

