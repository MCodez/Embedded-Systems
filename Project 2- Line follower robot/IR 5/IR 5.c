/*
 * IR_5.c
 *
 * Created: 7/8/2014 12:59:29 PM
 *  Author: Administrator
 */ 




#include <avr/io.h>
#include <avr/delay.h>
void turn()
{
	PORTB=0x0A;
	if(PINA==0b00000011)
	PORTB=0x06;
	if(PINA==0b00000010)
	PORTB=0x0A;
	if(PINA==0b00000001)
	PORTB=0x05;
	if(PINA==0b00001100)
	turn();
	if(PINA=0b00000011)
	{
		PORTB=0x09;
		turn();
	}
}
int main(void)
{
	DDRA=0x00;
	DDRB=0xFF;
	
	
	while(1)
	{
		
		if(PINA==0b00000011)
		PORTB=0x06;
		if(PINA==0b00010011)
		{
			PORTB=0x00;
			DDRA=0xFF;
			PORTA=0xFF;
			_delay_ms(1000);
		}
		DDRA=0xFF;
		if(PINA==0b00000010)
		PORTB=0x0A;
		if(PINA==0b00000001)
        PORTB=0x05;
		if(PINA==0b00001100)
		{
			turn();
			
		}
		
	}
}
