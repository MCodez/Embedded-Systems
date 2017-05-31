/*
 * TIMER_1.c
 *
 * Created: 7/5/2014 11:50:19 AM
 *  Author: CSS
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


void InitPWM()
{
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
	DDRB=0x08;
}

int main(void)
{

InitPWM();
int i;
while(1)
{
for(i=0;i<=255;i++)
{OCR0=i;
 _delay_ms(30);}
for(i=255;i>=0;i--)
{OCR0=i;
_delay_ms(30);}
}
}