/*
 * IR_and_speaker.c
 *
 * Created: 25-07-2014 08:53:31
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

void timer0_CTC()
{
	TCCR0|=(1<<WGM01)|(1<<COM00)|(1<<CS01);
	DDRB|=(1<<PB3);
}


int main(void)
{
	DDRA=0x00;
	ADC_init();
	timer0_CTC();
	unsigned int a;
	while(1)
	{
		a=ADC_read('0');
		if(a>=60 && a<85)
		OCR0=50*1;
		else if(a>=85 && a<120)
		OCR0=50*3;
		else if(a>=120 && a<152)
		OCR0=50*5;
		else if(a>=152 && a<418)
		OCR0=50*7;
		else if(a>=418 && a<950)
		OCR0=50*9;
		else if(a>=950)
		OCR0=55*5;
		_delay_ms(100);
	}
}