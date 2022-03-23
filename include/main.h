#include <avr/io.h>      // this contains all the IO port definitions
#include <util/delay.h>
#include "uart.h"



#define F_CPU 8000000  // by default we have the 1MHz internal oscillator


#define OUT0  PINB0
#define OUT1  PINB4
#define OUT2  PINB5
#define OUT3  PIND2
#define OUT4  PIND4
#define OUT5  PIND7

#define SHIFT_REGISTER DDRB
#define SHIFT_PORT PORTB
#define DATA (1<<PB3)           //MOSI (SI)
#define LATCH (1<<PB2)          //SS   (RCK)
#define CLOCK (1<<PB5)          //SCK  (SCK)

void configurePWM();
void configureSPI();
volatile uint16_t * getRowPtr(int col);
void setRowAndDuty(volatile uint16_t *OCRxx,int dutyCycle);
void setColOutput(int output,int val);
void clearLEDS();
int setLED(uint8_t byte0,uint8_t byte1,uint8_t byte2,int duty);
uint8_t reverse(uint8_t b);


// Array to store output pins in an iterable way
int digitalOuputs[6];
int currentRow,currentCol,currentDuty;