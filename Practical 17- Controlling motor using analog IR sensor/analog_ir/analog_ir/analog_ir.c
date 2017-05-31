/*
 * analog_ir.c
 *
 * Created: 7/20/2014 3:54:15 PM
 *  Author: ONGC
 */ 


#include <avr/io.h>

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
    PORTA=0x00;
	PORTB=0xFF;
	ADC_init();
    unsigned int a;
	while(1)
    {
        a=ADC_read('0');
		if(a>=85)
		PORTB=0x09;
		else
		PORTB=0x00;
		//TODO:: Please write your application code 
    }
}