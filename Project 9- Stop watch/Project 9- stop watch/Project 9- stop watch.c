/*
 * Project_9__stop_watch.c
 *
 * Created: 7/9/2014 8:51:53 PM
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
		else if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('X');
		}
		else if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('-');
		}
		else if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('+');
		}
		
		else 
		{
		PORTD=0x0D;
		_delay_ms(5);
		}
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('9');
		}
		else if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('6');
		}
		else if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('3');
		}
		else if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('=');
		}
		
		else
		{
		PORTD=0x0B;
		_delay_ms(5);
		}
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('8');
		}
		else if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('5');
		}
		else if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('2');
		}
		else if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('0');
		}
		
		else
		{
		PORTD=0x07;
		_delay_ms(5);
		}
		if((PINA&0x01)==0)
		{
			while(!(PINA&0x01));
			return('7');
		}
		else if((PINA&0x02)==0)
		{
			while(!(PINA&0x02));
			return('4');
		}
		else if((PINA&0x04)==0)
		{
			while(!(PINA&0x04));
			return('1');
		}
		else if((PINA&0x08)==0)
		{
			while(!(PINA&0x08));
			return('C');
		}
		else
		return('\0');
    }
	
}


int main(void)
{
	DDRA=0x00;
	DDRD=0xFF;
	DDRC=0xFF;
	unsigned int a=0, b=0,c=0,flag=0;
	unsigned int i,j,k=0;
	char d;
	lcd_init();
	PORTA=0xFF;
	PORTD=0x00;
	dis_cmd(0x86);
	LCD_string("00:00");
	d=key_scan();
	while(1)
	{
		if(d=='9')
		{
			dis_cmd(0x86);
			LCD_string("00:00");
		}
		else if(d=='8' && flag==0)
		{
			do
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
						d=key_scan();
						if(d=='\0' && i<9)
						continue;
						else if(d=='\0' && i==9)
						break;
						else if(d=='8')
						{
							flag=1;
							break;
						}
						
						
					}
					if(flag==1)
					break;
					else if(j==6)
					{ 
						c=0;
						break;
					}
					else
					c=j;
				}
				_delay_ms(500);
				b=k+1;
				if(flag==1)
				break;
				else if(b<10)
				{
					dis_cmd(0x87);
					dis_data(b+0x30);
				}
				else if(b<60)
				{
					dis_cmd(0x86);
					LCD_number(b);
				}
				else
				b=0;
			}while(d=='\0');
	
		}
		d=key_scan();
		if(d=='8');
		flag=0;
	}
	//TODO:: Please write your application code
	
}