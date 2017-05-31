/*
 * IR_2.c
 *
 * Created: 7/8/2014 11:35:54 AM
 *  Author: Administrator
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
	DDRA=0x00;
	DDRC=0xFF;
	lcd_init();
	ADC_init();
	unsigned int a;
	dis_cmd(0x82);
	LCD_string("cm");
	while(1)
	{
		a=ADC_read('0');
		if(a>=60 && a<65)
		{dis_cmd(0x1);
		dis_cmd(0x80);
		LCD_number(20);
		dis_cmd(0x82);
		LCD_string("cm");}
		else if(a>=65 && a<70)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
	     LCD_number(19);
		 dis_cmd(0x82);
	 LCD_string("cm");}
	    else if(a>=70 && a<75)
	    {dis_cmd(0x1);
			dis_cmd(0x80);
	    LCD_number(18);
		dis_cmd(0x82);
	LCD_string("cm");}
	    else if(a>=75 && a<80)
	    {dis_cmd(0x1);
			dis_cmd(0x80);
	    LCD_number(17);
		dis_cmd(0x82);
	LCD_string("cm");}
	    else if(a>=80 && a<85)
	    {dis_cmd(0x1);
			dis_cmd(0x80);
        LCD_number(16);
		dis_cmd(0x82);
	LCD_string("cm");}
        if(a>=85 && a<92)
        {dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(15);dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=92 && a<96)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(14);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=96 && a<99)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(13);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=99 && a<113)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(12);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=113 && a<120)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(11);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=120 && a<152)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(10);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=152 && a<184)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(9);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=184 && a<216)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(8);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=216 && a<248)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(7);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=248 && a<280)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(6);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=280 && a<418)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(5);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=418 && a<556)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(4);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=556 && a<694)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(3);dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=694 && a<832)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		LCD_number(2);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=832 && a<950)
		{dis_cmd(0x1);
		dis_cmd(0x80);
		LCD_number(1);
		dis_cmd(0x82);
	LCD_string("cm");}
		else if(a>=950)
		{dis_cmd(0x1);
			dis_cmd(0x80);
		dis_data('0');
		dis_cmd(0x82);
	LCD_string("cm");}
			
		_delay_ms(100);
	}
}  //TODO:: Please write your application code

