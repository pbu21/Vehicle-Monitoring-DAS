//spio_driver.c//
#include <LPC21xx.H>
#define SPIF (S0SPSR&0x80)

void spi0_init(void)
	{
	PINSEL0|=0x1500;//P0.4->SCK0, P0.5->MISO0, P0.6->MOSI0
	IODIR0|=(1<<7);//P0.7->Output dir (CS)
	IOSET0=(1<<7);//CS=1 (Disable Slave)
	S0SPCCR=150;//100Kbps Commu Speed
	S0SPCR=0x0020;//MSTR Mode, 8bits per transfer,
							//CPOL=CPHA=0, MSB First	
}

unsigned char spi0(unsigned char data)
{
	S0SPDR=data;//Send data from master-->slave
	while(SPIF==0);//waiting for spi transfer to complete
	return S0SPDR;//return data received from slave
}
