/*
 * LDR_2.c
 *
 * Created: 7/18/2014 11:13:32 AM
 *  Author: ONGC
 */ 



#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
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
LCD_number(unsigned int num)
{
	int N[10],M[10],count=0,i=0,j,num1;
	while(num>0)
	{
		num1=num%10;
		N[i]=num1;
		i++;
		num=num/10;
		count++;
		
	}
	for(j=0,i=(count-1);j<count,i>=0;j++,i--)
	{
		M[j]=N[i];
		dis_data(M[j]+0x30);
	}
}

void LCD_string(unsigned char *str)
{
	int i=0;
	while(str[i]!='\0')
	{	dis_data(str[i]);
		i++;
	}

}

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
	DDRC=0xFF;
	lcd_init();
	ADC_init();
	unsigned int a;
	while(1)
	{
		a=ADC_read('0');
		if(a<=180)
		{	
			dis_cmd(0x1);
			dis_cmd(0x80);
		    LCD_string("BLACK");
		    _delay_ms(1000);
		}
		if(a>180 && a<=320)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("BLUE");
			_delay_ms(1000);
		}
		if(a>320 && a<=400)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("RED");
			_delay_ms(1000);
		}
		if(a>400 && a<=500)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("GREEN");
			_delay_ms(1000);
		}
		if(a>500 && a<=550)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("ORANGE");
			_delay_ms(1000);
		}
		if(a>550 && a<=600)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("YELLOW");
			_delay_ms(1000);
		}
		if(a>600)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("WHITE");
			_delay_ms(1000);
		}
	}
}

