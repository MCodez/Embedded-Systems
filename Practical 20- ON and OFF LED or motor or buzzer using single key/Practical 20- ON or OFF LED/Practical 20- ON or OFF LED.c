/*
 * Practical_20__ON_or_OFF_LED.c
 *
 * Created: 7/20/2014 4:41:26 PM
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
    DDRA=0x00;
	DDRD=0xFF;
	DDRB=0xFF;
	char a;
	int i=0;
	while(1)
    {
        a=key_scan();
		if(a=='1' && i%2==0)
		{
			PORTB=0x01;
			i++;
		}
		if(a=='1' && i%2!=0)
		{
			PORTB=0x00;
			i++;
		}
		//TODO:: Please write your application code 
    }
}