/*
 * digi_ir.c
 *
 * Created: 7/20/2014 3:48:09 PM
 *  Author: ONGC
 */ 


#include <avr/io.h>

int main(void)
{
    DDRA=0x00;
	DDRB=0xFF;
	while(1)
    {
        if(PINA==0b00000001)
		PORTB=0x09;
		else
		PORTB=0x00;//TODO:: Please write your application code 
    }
}