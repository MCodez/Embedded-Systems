/*
 * MATRIX_3.c
 *
 * Created: 7/2/2014 9:55:28 PM
 *  Author: CSS
 */ 


#include <avr/io.h>

int main(void)
{
   DDRC=0xFF;
   DDRD=0xFF;
   PORTD=0xFF;
   PORTC=0x7E;
}