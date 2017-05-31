/*
 * practical_15.c
 *
 * Created: 7/19/2014 11:58:29 AM
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
	int i;
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
	DDRB=0xFF;
	DDRA=0x00;
	DDRC=0xFF;
	lcd_init();
	ADC_init();
	unsigned int a;
	int distance,time=0,speed;
	while(ADC_read('1')<=950)
	{
		PORTB=0x09;
		time+=1;
		a=ADC_read('0');
		if(a>=60 && a<65)
		distance=20;
		else if(a>=65 && a<70)
		distance=19;
		else if(a>=70 && a<75)
		distance=18;
		else if(a>=75 && a<80)
		distance=17;
		else if(a>=80 && a<85)
		distance=16;
		else if(a>=85 && a<92)
		distance=15;
		else if(a>=92 && a<96)
		distance=14;
		else if(a>=96 && a<99)
		distance=13;
		else if(a>=99 && a<113)
		distance=12;
		else if(a>=113 && a<120)
		distance=11;
		else if(a>=120 && a<152)
		distance=10;
		else if(a>=152 && a<184)
		distance=9;
		else if(a>=184 && a<216)
		distance=8;
		else if(a>=216 && a<248)
		distance=7;
		else if(a>=248 && a<280)
		distance=6;
		else if(a>=280 && a<418)
		distance=5;
		else if(a>=418 && a<556)
		distance=4;
		else if(a>=556 && a<694)
		distance=3;
		else if(a>=694 && a<832)
		distance=2;
		else if(a>=832 && a<950)
		distance=1;
		else if(a>=950)
		distance=0;
		speed=distance/time;
		dis_cmd(0x1);
		dis_cmd(0x80);
		LCD_string("Speed");
		dis_cmd(0xC0);
		LCD_number(speed);
		_delay_ms(1000);
	}
}  //TODO:: Please write your application code

