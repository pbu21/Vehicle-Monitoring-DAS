//lcd_4bit_driver//
#include <lpc21xx.h>

void delay_ms(unsigned int ms)
{
T0PC=0;
T0PR=15000-1;
//T0TC=0;
T0TCR=1;
while(T0TC<ms);
T0TCR=0;
}
void delay_s(unsigned int s)
{
T0PC=0;
T0PR=15000000-1;
//T0TC=0;
T0TCR=1;
while(T0TC<s);
T0TCR=0;
}

void lcd_data(unsigned char data)
{
//higher nibble
unsigned int temp;
IOCLR1=0XFE<<16;
temp=(data&0XF0)<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

//LOWER nibble
IOCLR1=0XFE<<16;
temp=(data&0X0F)<<20;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_cmd(unsigned char cmd)
{
//higher nibble
unsigned int temp;
IOCLR1=0XFE<<16;
temp=(cmd&0XF0)<<16;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
	
	//lower nibble

IOCLR1=0XFE<<16;
temp=(cmd&0X0F)<<20;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_init(void)
{
IODIR1=0XFE<<16;
//PINSEL2=0X00;
IOCLR1=1<<19;
lcd_cmd(0X02);
lcd_cmd(0X28);
lcd_cmd(0X0E);
lcd_cmd(0X01);
}

void lcd_string(char *ptr)
{
	while(*ptr!=0)
	{
		lcd_data(*ptr);
		ptr++;
	}
}

void lcd_integer(int num)
{ int a[10],i;
	if(num==0)
		lcd_data('0');
	if(num<0)
	{
		num=-num;
		lcd_data('-');
	}
	i=0;
	while(num>0)
	{
		a[i]=(num%10)+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		lcd_data(a[i]);
	}
}


void lcd_float(float num)
{
	int j;
	int i= num;
	lcd_integer(i);
	lcd_data('.');
	num=num-i;
	j=num*100;
	lcd_integer(j);
}
