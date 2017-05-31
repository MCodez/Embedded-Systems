/*
 * INTERRUPT_1.c
 *
 * Created: 7/16/2014 10:55:48 AM
 *  Author: ONGC
 */ 


#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
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

ISR(INT0_vect)
{
	PORTB=0xF0;
	_delay_ms(1000);
	dis_cmd(0x1);
	dis_cmd(0x80);
	LCD_string("Interrupt running");
}

int main(void)
{
    DDRC=0xFF;
	DDRB=0xFF;
	lcd_init();
	
	PORTD=0b00000100;
	sei();
	MCUCR=0x00;
	MCUCSR=0x00;
	GICR=0b01000000;
	while(1)
    {
        PORTB=0x0F;
		dis_cmd(0x1);
		dis_cmd(0x80);
		LCD_string("Main program");
		_delay_ms(1000);//TODO:: Please write your application code 
    }
}