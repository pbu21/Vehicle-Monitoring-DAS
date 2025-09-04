//uart_driver.c//
#include <LPC21XX.h>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart0_init(unsigned int baud)
{

int result=0,pclk;
int a[]={15,30,60,0,15};
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0|=0X5;
U0LCR=0X83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0X3;
}

void uart0_tx(unsigned int data)
{
U0THR=data;
while(THRE==0);
}

unsigned char uart0_rx(void)
{
while(RDR==0);
return U0RBR;
}

void uart0_string(char *p)
{
	while(*p!=0)
	{
		uart0_tx(*p);
		*p++;
	}
}
