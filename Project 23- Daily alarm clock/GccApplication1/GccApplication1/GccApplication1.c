/*
 * GccApplication1.c
 *
 * Created: 20-08-2014 11:30:34
 *  Author: JSSATE
 */ 


#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{
	DDRC=0xFF;
	DDRD=0XFF;
	
    while(1)
    {
		PORTC=0x82;
		PORTD=0xDF;
		_delay_ms(2000);
		PORTC=0x00;
		PORTD=0x40;
		_delay_ms(2000);
		PORTC=0x28;
		PORTD=0x7F;
		_delay_ms(2000);
		PORTC=0x10;
		PORTD=0xFE;
		_delay_ms(2000);
			
		
        //TODO:: Please write your application code 
    }
}