/*
 * MOTOR_2.c
 *
 * Created: 7/3/2014 12:29:40 PM
 *  Author: CSS
 */ 



#include <avr/io.h>
#include <avr/delay.h>
#define LCD_port PORTD
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



int main(void)
{
	DDRB=0xFF;
	DDRD=0xFF;
	int i;
	lcd_init();
	while(1)
	{
	LCD_string("CLOCKWISE");
	for(i=0;i<4;i++)
	{
	PORTB=(1<<i);
	_delay_ms(1000);	
	}
	dis_cmd(0x1);
	LCD_string("ANTI-CLOCKWISE");
	PORTB=0x04;
	_delay_ms(1000);
	PORTB=0x02;
	_delay_ms(1000);
	PORTB=0x01;
	_delay_ms(1000);
	PORTB=0x08;
	_delay_ms(1000);
	PORTB=0x00;
	dis_cmd(0x1);
	}
	

}