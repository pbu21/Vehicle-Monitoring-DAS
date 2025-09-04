//header.h///
#include<lpc21xx.h>
#include<stdio.h>
 /* 
   typedef struct my_time{
           unsigned char hour;
           unsigned char minute;
           unsigned char second;
   }TIME;
 
  typedef unsigned int ui;
  typedef unsigned char uc;
  typedef unsigned short usi;
 
  void delay_ms(ui ms);
	 void delay_s(ui ms);
  void uart0_init(ui baud);
  void uart0_binary(uc num);
  void uart0_tx(uc num);
  int uart0_atoi(char *p);
  void uart0_string(char *p);
  void uart0_int(int num);
 
  void CONFIG_INTR(void);
  void UART0_EN(void);
 
  void lcd_init(void);
  void lcd_cmd(ui cmd);
  void lcd_data(ui data);
  void lcd_string(char *p);
  void lcd_integer(int num);
 
  void i2c_init(void);
  void i2c_send(uc sa, uc mem, uc data);
  uc i2c_read(uc sa, uc mem);
 
  void spi0_init(void);
  uc spi0(uc data);
  usi mcp3204_read(uc ch);
 
  void adc_init(void);
  uc adc_read(uc ch);
  uc temp_data(void);
  uc pot_data(void);
*/

typedef unsigned int ui;
typedef unsigned char uc;

void adc_init(void);
unsigned int adc_read(unsigned char ch_num);

void i2c_init(void);
void i2c_send(unsigned char sa, unsigned char mr, unsigned char data);
unsigned char i2c_read(unsigned char sa, unsigned char mr);

void delay_ms(unsigned int ms);
void delay_s(unsigned int s);
void lcd_init(void);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(char *ptr);
void lcd_integer(int num);
void lcd_float(float num);

unsigned int mcp3204_read(unsigned char ch_num);

void spi0_init(void);
unsigned char spi0(unsigned char data);

void uart0_string(char *p);
unsigned char uart0_rx(void);
void uart0_tx(unsigned int data);
void uart0_init(unsigned int baud);





