/*
 * LCD_8.c
 *
 * Created: 7/3/2014 6:22:12 PM
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
	_delay_ms(1);
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

LCD_cust_char_1()
{
	dis_cmd(0x40);
	dis_data(0x08);
	dis_data(0x0C);
	dis_data(0x06);
	dis_data(0x03);
	dis_data(0x06);
	dis_data(0x0C);
	dis_data(0x08);
	dis_data(0x00);
	
}
LCD_cust_char_2()
{
	dis_cmd(0x48);
	dis_data(0x01);
	dis_data(0x03);
	dis_data(0x06);
	dis_data(0x0C);
	dis_data(0x06);
	dis_data(0x03);
	dis_data(0x01);
	dis_data(0x00);
	
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
	

int main(void)
{
	DDRC=0xFF;
	int a=0, b=0,c=0;
	int i,j,k;
	lcd_init();
	dis_cmd(0x86);
	LCD_string("00:00");
	while(1)
	{
		j=0;
		 while(j<=5)
		  {
		   j++;
		   for(i=0;i<=9;i++)
		   {
						
			   
			a=i;
			dis_cmd(0x8A);
			dis_data(a+0x30);
			dis_cmd(0x89);
			dis_data(c+0x30);
			dis_cmd(0x88);
			dis_data(':');
			_delay_ms(20000);
			
						
			
		   }
		   if(j==6)
		   { c=0;
			  break;} 
			c=j;
		 }
		 _delay_ms(500);
		 k++;
		 b=k;
		 if(b<10)
		 {dis_cmd(0x87);
		 dis_data(b+0x30);}
		 else if(b<60)
		 {dis_cmd(0x86);
		 LCD_number(b);}
		 else
		 b=0;
		 
		
		
		 
	}
	
	
	//TODO:: Please write your application code
	
}