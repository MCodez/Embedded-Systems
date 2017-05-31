/*
 * Practical_27__different_colours_from_RGB_LED.c
 *
 * Created: 7/15/2014 4:18:21 PM
 *  Author: ONGC
 */ 


#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
    DDRB=0xFF;
	while(1)
    {
        PORTB=0x07;
		_delay_ms(10000);
		PORTB=0x01;
		_delay_ms(10000);
		PORTB=0x02;
		_delay_ms(10000);
		PORTB=0x04;
		_delay_ms(10000);
		PORTB=0x03;
		_delay_ms(10000);
		PORTB=0x06;
		_delay_ms(10000);
		PORTB=0x05;
		_delay_ms(10000);
		PORTB=0x00;
		_delay_ms(10000);//TODO:: Please write your application code 
    }
}