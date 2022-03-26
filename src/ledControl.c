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

void setDuty(int dutyCycle){
  int weight = 0xFF / 100;
  OCR0A= 0xFF - (dutyCycle*weight);
}

uint8_t reverse(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

// Byte 2 only has 5 bits
int setLED(uint8_t byte0,uint8_t byte1,uint8_t byte2,int duty){

  SPDR0 = byte2;
  while(!(SPSR0 & (1<<SPIF)));
  SPDR0 = byte1;
  while(!(SPSR0 & (1<<SPIF)));
  SPDR0 = byte0;
  while(!(SPSR0 & (1<<SPIF)));

  //Toggle latch to copy data to the storage register
  SHIFT_PORT |= LATCH;
  SHIFT_PORT &= ~LATCH;
  
  setDuty(duty);
  return 0;
}

