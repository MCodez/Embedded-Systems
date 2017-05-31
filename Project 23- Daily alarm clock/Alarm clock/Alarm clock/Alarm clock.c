/*
 * Alarm_clock.c
 *
 * Created: 25-07-2014 15:19:16
 *  Author: JSSATE
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LCD_port PORTC
#define RS 0
#define RW 1
#define EN 2

int B=0,D=6;
int a=0, b=0,c=0,d=0;
int i=0,j=0,k=0,l=0;

void init_TIMER()
{
	OCR0=1000;
	TCCR0=(1<<WGM12)|(1<<CS10);
	TIMSK=(1<<OCIE0);
}

ISR(INT0_vect)
{
	if(i<=9)
	{
		a=i;
		i++;
		
		dis_cmd(0x8A);
		dis_data(a+0x30);
		dis_cmd(0x89);
		dis_data(c+0x30);
		dis_cmd(0x88);
		dis_data(':');
		_delay_ms(1000);
		if(i>9 && j<5)
		{
			j++;
			c=j;
			i=0;
		}
		if(i>9 && j==5)
		{
			j=0;
			c=j;
			i=0;
			k++;
		}
		
		b=k;
		if(b<10)
		{	dis_cmd(0x87);
			dis_data(b+0x30);
		}
		else if(b<60)
		{	dis_cmd(0x86);
			LCD_number(b);
		}
		else
		{
			b=0;
			l++;
		}
		d=l;
		if(d==D)
		{
			if(b==B)
			PORTA=0xFF;
		}
		if(d<10)
		{	dis_cmd(0x84);
			dis_data(d+0x30);
		}
		else if(d<=24)
		{	dis_cmd(0x83);
			LCD_number(d);
		}
		else if(d>24)
		{
			i=0;j=0;k=0;l=0;
		}
	}
}

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

int main(void)
{
	DDRA=0xFF;
	DDRC=0xFF;
	lcd_init();
	dis_cmd(0x83);
	LCD_string("00:00:00");
	init_TIMER();
	sei();
	MCUCR=0x00;
	MCUCSR=0x00;
	GICR=0b01000000;
	while(1)
	{
		
	}
}