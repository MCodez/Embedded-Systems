/*
 * KEY_3.c
 *
 * Created: 7/4/2014 8:12:14 PM
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

char key_scan()
{
	while(1)
	{
		PORTD=0x0E;
		_delay_ms(5);
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return(0x2F);
		}
		if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return(0x2A);
		}
		if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return(0x2D);
		}
		if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return(0x2B);
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
			return(0x3D);
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
			return(0x20);
		}
	}
}



int main(void)
{
	char a,b,c,d,e=0x24;
	int i,j,k,A,B,res,flag;
	int num[5];
	DDRC=0xFF;
	DDRA=0x00;
	DDRD=0xFF;
	lcd_init();
	PORTA=0xFF;
	PORTD=0x00;
	d=key_scan();
	dis_data(d);
	dis_cmd(0x1);
	dis_cmd(0x80);	
	while(1)
	{
		A=0;
		B=0;
		flag=0;
		num[5]=0;
		i=0;
		if(e==0x20)
		{
			dis_cmd(0x1);
			dis_cmd(0x80);
		}
		a=key_scan();
		while(a!=0x2B && a!=0x2D && a!=0x2A && a!=0x2F && a!=0x3D && a!=0x20)
		{
			flag=1;
			dis_data(a);
			if(a==0x31)
			num[i]=1;
			else if(a==0x32)
			num[i]=2;
			else if(a==0x33)
			num[i]=3;
			else if(a==0x34)
			num[i]=4;
			else if(a==0x35)
			num[i]=5;
			else if(a==0x36)
			num[i]=6;
			else if(a==0x37)
			num[i]=7;
			else if(a==0x38)
			num[i]=8;
			else if(a==0x39)
			num[i]=9;
			else if(a==0x30)
			num[i]=0;
			i+=1;
			a=key_scan();
		}
		if(flag==1)
		{
			for(j=0;i>0;j++,i--)
			{
				if(num[i-1]!=0)
				{
					for(k=0;k<j;k++)
						num[i-1]*=10;
					A+=num[i-1];
				}
				else
				continue;
			}
		}
		if(a==0x20)
		continue;
		else 
		b=a;
		dis_data(b);
		i=0;
		num[5]=0;
		flag=0;
		c=key_scan();
		while(c!=0x3D && c!=0x20)
		{
			flag=1;
			dis_data(c);
			if(c==0x31)
			num[i]=1;
			if(c==0x32)
			num[i]=2;
			if(c==0x33)
			num[i]=3;
			if(c==0x34)
			num[i]=4;
			if(c==0x35)
			num[i]=5;
			if(c==0x36)
			num[i]=6;
			if(c==0x37)
			num[i]=7;
			if(c==0x38)
			num[i]=8;
			if(c==0x39)
			num[i]=9;
			if(c==0x30)
			num[i]=0;
			i+=1;
			c=key_scan();
		}
		if(flag==1)
		{
			for(j=0;i>0;j++,i--)
			{
				
				if(num[i-1]!=0)
				{
					for(k=0;k<j;k++)
						num[i-1]*=10;
					B+=num[i-1];
				}
				else
				continue;
			}
		}
		if(c==0x20)
		continue;
		else 
		{	
			dis_cmd(0xC0);
			dis_data(c);
			if(b==0x2B)
			LCD_number(A+B);
			else if(b==0x2D)
			LCD_number(A-B);
			else if(b==0x2A)
			LCD_number(A*B);
			else if(b==0x2F) 
			LCD_number(A/B);
		}
		_delay_ms(1000);
		e=key_scan();
		
	}
}



