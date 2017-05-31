/*
 * Project_12__password_controlled_app.c
 *
 * Created: 7/17/2014 9:40:12 PM
 *  Author: ONGC
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
	DDRA=0x00;
	DDRD=0xFF;
	PORTA=0xFF;
	PORTD=0x00;
	DDRC=0xFF;
	lcd_init();
	int i,flag=1;
	char A[4];
	char pass[4]="1234";
	while(flag==1)
	{
		dis_cmd(0x1);
		dis_cmd(0x80);
		LCD_string("Enter password");
		dis_cmd(0xC0);
		for(i=0;i<4;i++)
		{
			A[i]=key_scan();
			dis_data('*');
			_delay_ms(1000);
			
		}
		
		for(i=0;i<4;i++)
		{
			if(A[i]==pass[i])
			flag=0;
			else
			flag=1;
		}
		if(flag==0)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("Access Granted");
		}
		else
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
			LCD_string("Access Denied");
		}
		_delay_ms(20000);
	}
	//TODO:: Please write your application code
	
}
