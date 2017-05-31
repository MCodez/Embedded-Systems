/*
 * MATRIX_4.c
 *
 * Created: 7/2/2014 11:03:41 PM
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
     PORTD=0xFF;
	 PORTC=0x7E;
	 _delay_ms(50);
	 PORTD=0x81;
	 PORTC=0x00;
	 _delay_ms(100);   //TODO:: Please write your application code 
    }
}