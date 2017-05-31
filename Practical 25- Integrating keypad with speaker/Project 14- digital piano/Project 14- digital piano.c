/*
 * Project_14__digital_piano.c
 *
 * Created: 7/7/2014 7:33:28 AM
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

void timer0_CTC()
{
	TCCR0|=(1<<WGM01)|(1<<COM00)|(1<<CS01);
	DDRB|=(1<<PB3);
}

int main(void)
{
	unsigned char a;
	DDRC=0xFF;
	DDRB=0xFF;
	DDRA=0x00;
	DDRD=0xFF;
	lcd_init();
	timer0_CTC();
	PORTA=0xFF;
	PORTD=0x00;
	PORTB=0x00;
	
	
	
	while(1)
	{
		a=key_scan();
		if(a=='1')
		{OCR0=59*3;
		
		PORTC=0x80;
		LCD_string("Sa");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='2')
		{OCR0=52*3;
			PORTC=0x80;
		
		LCD_string("Re");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='3')
		{OCR0=46*3;
		PORTC=0x80;
		LCD_string("Ga");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='4')
		{OCR0=44*3;
		PORTC=0x80;
		LCD_string("Ma");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='5')
		{OCR0=38*3;
			PORTC=0x80;
		LCD_string("Pa");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='6')
		{OCR0=34*5;
			PORTC=0x80;
		LCD_string("Dha");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='7')
		{OCR0=30*7;
			PORTC=0x80;
		LCD_string("Ni");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		if(a=='8')
		{OCR0=28*7;
			PORTC=0x80;
		LCD_string("Sa'");
		_delay_ms(1000);
		OCR0=0;
		dis_cmd(0x1);}
		
			}
}