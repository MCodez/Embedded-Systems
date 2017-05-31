/*
 * MATRIX_5.c
 *
 * Created: 7/2/2014 11:12:21 PM
 *  Author: CSS
 */ 


#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{
    DDRC=0xFF;
	DDRD=0xFF;
	while(1)
    {
    PORTD=0x41;
	PORTC=0x00;
	_delay_ms(20);
	PORTD=0x22;
	PORTC=0xFD;
	_delay_ms(20);
	PORTD=0x14;
	PORTC=0xFB;
	_delay_ms(20);
	PORTD=0x08;
	PORTC=0xF7;
	_delay_ms(50);
	    //TODO:: Please write your application code 
    }
}