/*
 * LCD_7.c
 *
 * Created: 7/3/2014 4:38:40 PM
 *  Author: CSS
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
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
	_delay_ms(1);
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

LCD_cust_char_1()
{
	dis_cmd(0x40);
	dis_data(0x08);
	dis_data(0x0C);
	dis_data(0x06);
	dis_data(0x03);
	dis_data(0x06);
	dis_data(0x0C);
	dis_data(0x08);
	dis_data(0x00);
	
}
LCD_cust_char_2()
{
	dis_cmd(0x48);
	dis_data(0x01);
	dis_data(0x03);
	dis_data(0x06);
	dis_data(0x0C);
	dis_data(0x06);
	dis_data(0x03);
	dis_data(0x01);
	dis_data(0x00);
	
}

int main(void)
{
	DDRD=0xFF;
	int i=0;
	lcd_init();
	dis_cmd(0x80);
	LCD_cust_char_1();
	LCD_cust_char_2();
	while(i<16)
	{
		
		dis_data(0x00);
		dis_cmd(0x1);
		for(int j=0;j<=i;j++)
		dis_cmd(0x14);
		i++;
		_delay_ms(200);
		dis_data(0x01);
		dis_cmd(0x1);
		for(int j=0;j<=i;j++)
		dis_cmd(0x14);
		i++;
		_delay_ms(100);
		
	}
	
	
	//TODO:: Please write your application code
	
}