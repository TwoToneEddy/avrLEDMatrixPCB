#include "main.h"

void configurePWM(){


    // For OCR0A and OCR0B, set 8bit fast pwm, inverting, max 0xFF (8-bit)
    TCCR0A |= 1 << WGM00 | 1 << WGM01 | 1 << COM0A1 | 1 << COM0A0 | 1 << COM0B1 | 1 << COM0B0;

    // For OCR1A and OCR1B, set 8bit fast pwm, inverting, max 0x00FF 
    //TCCR1A |= 1 << WGM10 | 1 << COM1A1 | 1 << COM1A0 | 1 << COM1B1 | 1 << COM1B0;
    //TCCR1B |= 1 << WGM12;

    // For OCR0A and OCR0B, set 8bit fast pwm, inverting, max 0xFF (8-bit)
    //TCCR2A |= 1 << WGM20 | 1 << WGM21 | 1 << COM2A1 | 1 << COM2A0 | 1 << COM2B1 | 1 << COM2B0;

    TCCR0B |= 1 << CS00;
    //TCCR1B |= 1 << CS10;
    //TCCR2B |= 1 << CS20;


    OCR0A = 0; //PD6
    //OCR0B = 0; //PD5
    //OCR1A = 0; //PB1
    //OCR1B = 0; //PB2
    //OCR2A = 0; //PB3
    //OCR2B = 0; //PD3
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


    SPDR0 = 0;
    while(!(SPSR0 & (1<<SPIF)));
    SPDR0 = 0;
    while(!(SPSR0 & (1<<SPIF)));
    SPDR0 = 0;
    while(!(SPSR0 & (1<<SPIF)));
    SHIFT_PORT |= LATCH;
    SHIFT_PORT &= ~LATCH;
    
}