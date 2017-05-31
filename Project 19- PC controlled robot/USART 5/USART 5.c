/*
 * USART_5.c
 *
 * Created: 7/18/2014 10:40:29 AM
 *  Author: ONGC
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define Baud_Rate 300
#define ubrr_value ((F_CPU/(16*Baud_Rate))-1)

void usart_init()
{
	UBRRL=ubrr_value;
	UBRRH=(ubrr_value>>8);
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UCSRB=(1<<RXEN)|(1<<TXEN);
}

void usart_send(unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));
	UDR=data;
}

unsigned char usart_rec()
{
	while(!(UCSRA&(1<<RXC)));
	return UDR;
}

void usart_string(unsigned char *str)
{
	int i;
	while(str[i]!='\0')
	{	usart_send(str[i]);
		i++;
	}

}

int main(void)
{
	DDRB=0xFF;
	usart_init();
	char a;
	while(1)
	{
		a=usart_rec();
		if(a=='w')
		PORTB=0x09;
		if(a=='s')
		PORTB=0x06;
		if(a=='a')
		PORTB=0x0A;
		if(a=='d')
		PORTB=0x05;
		
		
		//TODO:: Please write your application code
	}
}