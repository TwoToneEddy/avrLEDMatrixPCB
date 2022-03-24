#include "main.h"

void configurePWM(){


    // For OCR0A and OCR0B, set 8bit fast pwm, inverting, max 0xFF (8-bit)
    TCCR0A |= 1 << WGM00 | 1 << WGM01 | 1 << COM0A1 | 1 << COM0A0 | 1 << COM0B1 | 1 << COM0B0;
    TCCR0B |= 1 << CS00;
    OCR0A = 0; //PD6
    DDRD |= (1 << PIND6);
}

void configureSPI()
{  
    //Setup IO
    SHIFT_REGISTER |= (DATA | LATCH | CLOCK); //Set control pins as outputs
    SHIFT_PORT &= ~(DATA | LATCH | CLOCK);        //Set control pins low
 
    //Setup SPI
    SPCR0 = (1<<SPE) | (1<<MSTR);  //Start SPI as Master
 
    //Pull LATCH low (Important: this is necessary to start the SPI transfer!)
    SHIFT_PORT &= ~LATCH;

    // Clear all bits
    SPDR0 = 0;
    while(!(SPSR0 & (1<<SPIF)));
    SPDR0 = 0;
    while(!(SPSR0 & (1<<SPIF)));
    SPDR0 = 0;
    while(!(SPSR0 & (1<<SPIF)));
    SHIFT_PORT |= LATCH;
    SHIFT_PORT &= ~LATCH;
    
}