//mpc3204_driver.c//
#include <lpc21xx.h>
#define cs0 (1<<17)

unsigned char spi0(unsigned char data);

unsigned int mcp3204_read(unsigned char ch_num)
{
   unsigned int result = 0;
    unsigned char byteH = 0, byteL = 0;
    ch_num <<= 6;
    IOCLR0 = cs0;
    spi0(0x06);
    byteH = spi0(ch_num);
    byteL = spi0(0x00);
    IOSET0 = cs0;
    byteH &= 0X0F;
    result = (byteH << 8) | byteL;
    return result;
}


