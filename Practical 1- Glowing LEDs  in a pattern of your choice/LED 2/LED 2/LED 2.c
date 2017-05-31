/*
 * LED_2.c
 *
 * Created: 7/2/2014 9:14:45 PM
 *  Author: CSS
 */ 


#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{
	DDRB=0xFF;
	while(1)
    {
     PORTB=0x05;
	 _delay_ms(1000);
	 PORTB=0x0A;
	 _delay_ms(1000);   //TODO:: Please write your application code 
    }
}