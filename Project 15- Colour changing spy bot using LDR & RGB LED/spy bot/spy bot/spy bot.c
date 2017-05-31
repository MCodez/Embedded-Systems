/*
 * spy_bot.c
 *
 * Created: 25-07-2014 15:03:12
 *  Author: JSSATE
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void ADC_init(void)
{
	ADMUX=(1<<REFS0);
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

unsigned int ADC_read(unsigned char ch)
{
	ch=ch&0b00000111;
	ADMUX|=ch;
	ADCSRA|=(1<<ADSC);
	while(!(ADCSRA&(1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	return ADC;
}


int main(void)
{
	DDRA=0x00;
	DDRB=0xFF;
	ADC_init();
	unsigned int a;
	while(1)
	{
		a=ADC_read('0');
		if(a>180 && a<=320)
		PORTB=0x01;
		if(a>320 && a<=400)
		PORTB=0x04;
		if(a>400 && a<=500)
		PORTB=0x02;
		if(a>550 && a<=600)
		PORTB=0x06;
		if(a>600)
		PORTB=0x07;
		_delay_ms(1000);
	}
}

