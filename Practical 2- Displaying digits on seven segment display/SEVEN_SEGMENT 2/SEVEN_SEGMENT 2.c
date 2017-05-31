/*
 * SEVEN_SEGMENT_2.c
 *
 * Created: 7/2/2014 9:28:19 PM
 *  Author: CSS
 */ 


#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
    DDRD=0xFF;
	PORTD=0x00;
	while(1)
    {
     PORTD=0x40;
	 _delay_ms(10000);
     PORTD=0x79;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x24;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x30;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x19;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x12;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x02;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x78;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x00;
	 _delay_ms(10000);   //TODO:: Please write your application code
     PORTD=0x10;
	 _delay_ms(10000);   //TODO:: Please write your application code
	    //CTODO:: Please write your application code 
    }
}