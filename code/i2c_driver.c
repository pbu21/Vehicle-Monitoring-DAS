/*i2c_driver.c*/
#include <LPC21xx.H>
//#include "header.h"
void uart0_string(char *p);

void i2c_init(void){
	//PINSEL init
	PINSEL0|=0x50;//P0.2->SCL, P0.3->SDA
	
	//En i2c interface & select master mode
	I2CONSET=(1<<6);//I2EN=1,AA=0
	
  //clock or freq init  
	I2SCLH=I2SCLL=75;//100Kbps speed
}

#define SI ((I2CONSET>>3)&1)
void i2c_send(unsigned char sa, unsigned char mr, unsigned char data){
	/*1. generate start condi*/
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	I2CONCLR=(1<<5);//STA=0
	
	/*2. send SA+W & check ack*/
	I2DAT=sa;//send sa+w
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	if(I2STAT==0x20){
		uart0_string("Err: SA+W\r\n");
		goto exit;
	}
	
	/*3. send mr addr & check ack*/
	I2DAT=mr;//send mr addr
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	if(I2STAT==0x30){
		uart0_string("Err: Memory addr\r\n");
		goto exit;
	}
	
	/*4. send data & check ack*/
	I2DAT=data;//send data
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	if(I2STAT==0x30){
		uart0_string("Err: Data\r\n");
		goto exit;//optional
	}
	
	/*5. generate stop condi*/
	exit:
		I2CONSET=(1<<4);//STO=1
		I2CONCLR=(1<<3);//*clear SI
}

unsigned char i2c_read(unsigned char sa, unsigned char mr){
	unsigned char temp=0;
	/*1. generate start condi*/
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	I2CONCLR=(1<<5);//STA=0
	
	/*2. send SA+W & check ack*/
	I2DAT=sa&0xFE;//send sa+w
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	if(I2STAT==0x20){
		uart0_string("Err: SA+W\r\n");
		goto exit;
	}
	
	/*3. send mr addr & check ack*/
	I2DAT=mr;//send mr addr
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	if(I2STAT==0x30){
		uart0_string("Err: Memory addr\r\n");
		goto exit;
	}
	
	/*4 generate start condi again*/
	I2CONSET=(1<<5);//STA=1
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor SI
	I2CONCLR=(1<<5);//STA=0
	
	/*5. send SA+R & check ack*/
	I2DAT=sa;//send sa+r
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//monitor si
	if(I2STAT==0x48){
		uart0_string("Err: SA+R\r\n");
		goto exit;
	}
	
	/*6. read data & send noack*/
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//waiting for data to receive
	temp=I2DAT;
	
	/*7. generate stop condi*/
	exit:
		I2CONSET=(1<<4);//STO=1
		I2CONCLR=(1<<3);//*clear SI
	/*8. return data*/
	return temp;
}






