#include "main.h"

uint8_t countSetBits(uint8_t n)
{
    uint8_t count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/*
volatile uint16_t * getRowPtr(int col){
  switch (col)
  {
  case 0:
    DDRD |= 1 << PIND6;
    DDRD &= ~(1 << PIND5);
    return (volatile uint16_t *)&OCR0A;
    break;
  case 1:
    DDRD |= 1 << PIND5;
    DDRD &= ~(1 << PIND6);
    return (volatile uint16_t *)&OCR0B;
  case 2:
    DDRB |= 1 << PINB1;
    return &OCR1A;
    break;
  case 3:
    DDRB |= 1 << PINB2;
    return &OCR1B;
    break;
  case 4:
    DDRB |= 1 << PINB3;
    DDRD &= ~(1 << PIND3);
    return (volatile uint16_t *)&OCR2A;
    break;
  case 5:
    DDRD |= 1 << PIND3;
    DDRB &= ~(1 << PINB3);
    return (volatile uint16_t *)&OCR2B;
    break;
  default:
    DDRD |= 1 << PIND6;
    return &OCR1A;
    break;
  }

}*/

void setDuty(int dutyCycle){
  int weight = 0xFF / 100;
  OCR0A= 0xFF - (dutyCycle*weight);
}

/*
    Sets single output to selected value, clears all other outputs
*/
/*
void setColOutput(int output,int val)
{
    // Clear outputs
    PORTB = 0;
    PORTD = 0;


    if(val > 0){
        if(output < 3)
            PORTB |= (1 << digitalOuputs[output]);
        else
            PORTD |= (1 << digitalOuputs[output]);
    }
}
*/
/*
void clearLEDS(){

  for(int row = 0; row < 6; row++){
    for(int col = 0; col < 6; col++){
      setLED(row,col,0);
    }
  }

}*/

uint8_t reverse(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

// Byte 2 only has 5 bits
int setLED(uint8_t byte0,uint8_t byte1,uint8_t byte2,int duty){

  SPDR0 = reverse(byte2<<3);
  while(!(SPSR0 & (1<<SPIF)));
  SPDR0 = reverse(byte1);
  while(!(SPSR0 & (1<<SPIF)));
  SPDR0 = reverse(byte0);
  while(!(SPSR0 & (1<<SPIF)));

  //Toggle latch to copy data to the storage register
  SHIFT_PORT |= LATCH;
  SHIFT_PORT &= ~LATCH;
  
  setDuty(duty);
  return 0;
}

