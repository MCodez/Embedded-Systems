/*
 * RELAY_1.c
 *
 * Created: 7/11/2014 10:57:59 AM
 *  Author: ONGC
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD=0xFF;
	while(1)
    {
        PORTD=0x02;
		_delay_ms(1000);
		PORTD=0x00;
		_delay_ms(1000);
		//TODO:: Please write your application code 
    }
}