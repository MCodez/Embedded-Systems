/*
 * USART_2.c
 *
 * Created: 7/17/2014 12:21:45 PM
 *  Author: Administrator
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define Baud_Rate 300
#define ubrr_value ((F_CPU/(16*Baud_Rate))-1)

#define LCD_port PORTC
#define RS 0
#define RW 1
#define EN 2
void lcd_init()
{

	dis_cmd(0x02);//HOME POSITION
	dis_cmd(0x28);//SET 4 BIT 16X2
	dis_cmd(0x06);////ENTRY MODE
	dis_cmd(0x0c);//display on cursor off
}
void dis_cmd(unsigned char abc)
{
	char cmd1;
	cmd1=abc&0xf0;
	LCD_cmd(cmd1);
	cmd1=((abc<<4)&(0xf0));
	LCD_cmd(cmd1);
}
void LCD_cmd(unsigned char abc)
{
	LCD_port=abc;
	LCD_port&=~(1<<RS);//RS=0 for command
	LCD_port&=~(1<<RW);///rw=0
	LCD_port|=(1<<EN);///
	_delay_ms(10);///delay for high to low pulse
	LCD_port&=~(1<<EN);
}

void LCD_data(unsigned char abc)
{
	LCD_port=abc;
	LCD_port|=(1<<RS);
	LCD_port&=~(1<<RW);
	LCD_port|=(1<<EN);
	_delay_ms(10);
	LCD_port&=~(1<<EN);
}

void dis_data(unsigned char abc)
{
	char data1;
	data1=abc&0xf0;
	LCD_data(data1);
	data1=((abc<<4)&0xf0);
	LCD_data(data1);
}

void LCD_string(unsigned char *str)
{
	int i;
	while(str[i]!='\0')
	{	dis_data(str[i]);
		i++;
	}

}

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
	int i=0;
	while(str[i]!='\0')
	{	usart_send(str[i]);
		i++;
	}

}

int main(void)
{
	DDRC=0xFF;
	lcd_init();
	usart_init();
	char data;
	dis_cmd(0x1);
	dis_cmd(0x80);
	while(1)
	{
		data=usart_rec();
		dis_data(data);
	}//TODO:: Please write your application code
	
}