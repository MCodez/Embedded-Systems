/*
 * KEY_2.c
 *
 * Created: 7/4/2014 8:00:17 PM
 *  Author: CSS
 */ 


#include <avr/io.h>
#include <avr/delay.h>
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
	cmd1=abc&0xF0;
	LCD_cmd(cmd1);
	cmd1=((abc<<4)&(0xF0));
	LCD_cmd(cmd1);
}
void LCD_cmd(unsigned char abc)
{
	LCD_port=abc;
	LCD_port&=~(1<<RS);//RS=0 for command
	LCD_port&=~(1<<RW);///rw=0
	LCD_port|=(1<<EN);///
	_delay_ms(1);///delay for high to low pulse
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
	data1=abc&0xF0;
	LCD_data(data1);
	data1=((abc<<4)&0xF0);
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

char key_scan()
{
	while(1)
	{
		PORTD=0x0E;
		_delay_ms(5);
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('/');
		}
		if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('X');
		}
		if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('-');
		}
		if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('+');
		}
		
		PORTD=0x0D;
		_delay_ms(5);
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('9');
		}
		if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('6');
		}
		if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('3');
		}
		if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('=');
		}
		
		
		PORTD=0x0B;
		_delay_ms(5);
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('8');
		}
		if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('5');
		}
		if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('2');
		}
		if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('0');
		}
		
		
		PORTD=0x07;
		_delay_ms(5);
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('7');
		}
		if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('4');
		}
		if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('1');
		}
		if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('C');
		}
	}
}



int main(void)
{
	unsigned char a;
	DDRC=0xFF;
	DDRB=0xFF;
	DDRA=0x00;
	DDRD=0xFF;
	lcd_init();
	PORTA=0xFF;
	PORTD=0x00;
	PORTB=0x00;
	
	
	while(1)
	{
		a=key_scan();
		
		dis_data(a);
		if(a=='1')
		PORTB=0x09;
		if(a=='0')
		PORTB=0x06;
		
	}

}

