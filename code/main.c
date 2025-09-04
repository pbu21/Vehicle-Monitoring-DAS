 ////main.c///
 #include "header.h"
   
   int main(){
           uc hr, min, sec, day, index = 0,ch, ch1='%';
           int tt,ldr_per = 0;
          char a[16],b[16];
          char str[7][10] = {"SUN", "MON", "TUE", "WED", "THUR", "FRI", "SAT"};
          ui adc_val1=0, adc_val2=0;
          float vout1 = 0; 
		  		float vout2 = 0;
          float temperature = 0 ;
          ui ldr;
          PINSEL0 |= 0x05;
          uart0_init(9600);
          lcd_init();
          adc_init();
          i2c_init();
          spi0_init();
 
          
          i2c_send(0xD0, 0x2, 0x51);
          i2c_send(0xD0, 0x1, 0x59);
          i2c_send(0xD0, 0x0, 0x55);
 
          while(1){
 
                  adc_val1 = adc_read(1);
                  vout1 = (adc_val1 * 3.3) / 1023;
                  temperature = (vout1 - 0.5) / 0.01;
 
                  adc_val2 = adc_read(2);
                  vout2 = (adc_val2 * 3.3) / 1023;
						
                  ldr = mcp3204_read(2);
                  ldr_per = ldr*100 / 4095;
 
                  lcd_cmd(0xc0);  
                  tt = temperature;  
                						
                  sprintf(a,"T-%2d V-%.1f L%2d%c",tt,vout2,ldr_per,ch1); 
                  lcd_string(a);
						      uart0_string(a);
						      uart0_string("\r\n");
 
                  sec = i2c_read(0xD0, 0x0);
                  min = i2c_read(0xD0, 0x1);
                  hr = i2c_read(0xD0, 0x2);
                  day = i2c_read(0xD0, 0x3);
 
                  hr = hr & 0x1f;
 
                  if(day == 0x01) index = 0;
                          else if(day == 0x02) index = 1;
                          else if(day == 0x03) index = 2;
                          else if(day == 0x04) index = 3;
                          else if(day == 0x05) index = 4;
                          else if(day == 0x06) index = 5;
                          else if(day == 0x07) index = 6;
 
                  if((hr >> 5) & 1){
                           ch='P';
                  }
                  else{
                   ch = 'A';
 
                  }
 
 
                  lcd_cmd(0x80);
                  sprintf(b,"%d%d:%d%d:%d%d %cM %s",hr/0x10, hr%0x10 ,min/0x10,min%0x10,sec/0x10,sec%0x10,ch, str[index]);
                  lcd_string(b);
 
                  uart0_string(b);
                  uart0_string("\r\n");
                  
 
  //              uart0_string("\r\nTime: "); 
  //                      uart0_tx((hr/0x10)+48);
  //                      uart0_tx((hr%0x10)+48);
  //                      uart0_tx(':');
  //                      uart0_tx((min/0x10)+48);
  //                      uart0_tx((min%0x10)+48);
  //                      uart0_tx(':');
  //                      uart0_tx((sec/0x10)+48);
  //                      uart0_tx((sec%0x10)+48);
  //                      uart0_string("  ");
  //                  
  //                      uart0_string("  ");
  //                      uart0_int(temperature);
  //                      uart0_string("  ");
  //                      uart0_int(adc_val2);
  //                      uart0_string("  ");
  //                      uart0_int(ldr);
  //                      uart0_string("\r\n");
                          delay_ms(1000);
          }
 }
 /*
 TIME rtc_data(void){
         TIME t;

         t.hour = i2c_read(0xD0, 0x02);
         t.minute = i2c_read(0xD0, 0x01);
         t.second = i2c_read(0xD0, 0x00);

         return t;
 }


 void uart0_print(TIME t, uc pot, uc tempe, usi ldr){
         uart0_string("Data---------------------------\r\n");
         uart0_string("Time: ");
         uart0_int(t.hour);
         uart0_tx(':');
         uart0_int(t.minute);
         uart0_tx(':');
         uart0_int(t.second);

         uart0_string("\r\n");
         uart0_string("POT Value: ");
         uart0_int(pot);
         uart0_string("\r\nTemperature Value: ");
         uart0_int(tempe);
         uart0_string("\r\nLDR Value: ");
         uart0_init(ldr);
 }
*/
