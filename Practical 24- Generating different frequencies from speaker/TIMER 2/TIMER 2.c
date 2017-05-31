/*
 * TIMER_2.c
 *
 * Created: 7/5/2014 12:48:11 PM
 *  Author: CSS
 */ 



#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


void timer0_CTC()
{
	TCCR0|=(1<<WGM01)|(1<<COM00)|(1<<CS01);
	DDRB|=(1<<PB3);
}

int main(void)
{

	timer0_CTC();
	while(1)
	{
		
			 OCR0=59*3;
			 _delay_ms(1000);
			 OCR0=52*3;
			 _delay_ms(1000);
			 OCR0=46*3;
			 _delay_ms(1000);
			 OCR0=44*3;
			 _delay_ms(1000);
			 OCR0=38*3;
			 _delay_ms(1000);
			 OCR0=34*5;
			 _delay_ms(1000);
			 OCR0=30*7;
			 _delay_ms(1000);
			 OCR0=28*7;
			 _delay_ms(1000);
			}
		}