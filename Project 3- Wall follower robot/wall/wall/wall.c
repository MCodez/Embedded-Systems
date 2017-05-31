/*
 * wall.c
 *
 * Created: 25-07-2014 10:16:00
 *  Author: JSSATE
 */ 


#include <avr/io.h>

int main(void)
{
	DDRA=0x00;
	DDRB=0xFF;
	
	
	while(1)
	{
		
		if(PINA==0b00000010)
		PORTB=0x09;
		if(PINA==0b00000000)
		PORTB=0x0A;
	}
}