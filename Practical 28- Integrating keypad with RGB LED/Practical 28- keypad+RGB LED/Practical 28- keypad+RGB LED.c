/*
 * Practical_28__keypad_RGB_LED.c
 *
 * Created: 7/15/2014 5:13:19 PM
 *  Author: ONGC
 */ 

#include <avr/io.h>
#include <avr/delay.h>

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
	DDRB=0xFF;
	DDRA=0x00;
	DDRD=0xFF;
	PORTA=0xFF;
	PORTD=0x00;
	char a;
	while(1)
	{
		a=key_scan();
		if(a=='0')
		PORTB=0x00;
		if(a=='1')
		PORTB=0x01;
		if(a=='2')
		PORTB=0x02;
		if(a=='3')
		PORTB=0x03;
		if(a=='4')
		PORTB=0x04;
		if(a=='5')
		PORTB=0x05;
		if(a=='6')
		PORTB=0x06;
		if(a=='7')
		PORTB=0x07;
	    _delay_ms(1000);
	}
}