/*
 * BUZZER_1.c
 *
 * Created: 7/18/2014 12:08:56 PM
 *  Author: ONGC
 */ 


#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
    while(1)
	{
		DDRA=0xFF;
		PORTA=0xFF;
		_delay_ms(1000);
	}
}