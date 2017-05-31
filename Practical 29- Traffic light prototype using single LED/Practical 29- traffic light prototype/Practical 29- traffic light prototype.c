/*
 * Practical_29__traffic_light_prototype.c
 *
 * Created: 7/15/2014 4:54:29 PM
 *  Author: ONGC
 */ 


#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	DDRB=0xFF;
	while(1)
	{
		PORTB=0x04;
		_delay_ms(100000);
		PORTB=0x06;
		_delay_ms(50000);
		PORTB=0x02;
		_delay_ms(100000);
		//TODO:: Please write your application code
	}
}