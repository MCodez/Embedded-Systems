/*
 * MATRIX_2.c
 *
 * Created: 7/2/2014 9:50:48 PM
 *  Author: CSS
 */ 


#include <avr/io.h>

int main(void)
{
   DDRC=0xFF;
   DDRD=0xFF;
   PORTC=0x00;
   PORTD=0x81;
}