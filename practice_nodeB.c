#include <LPC21xx.H>
#include "header.h"

#define LED1 1<<17
#define LED2 1<<18
#define LED3 1<<19

extern CAN2 v1;
extern u8 flag;

main()
{
	IODIR0|=LED1|LED2|LED3;
	IOSET0|=LED1|LED2|LED3;

	can2_init();
	lcd_init();

	uart0_init(9600);
	config_vic_for_can2();
	config_can2();
	
	lcd_cmd(0x01);				   		

	while(1)
	{
	   if(flag)
		{
		   flag=0;

//			uart0_tx_string("SPEED : ");
//			uart0_tx_integer(v1.byteB&0xFFFF);
//
//			uart0_tx_string("	  TEMP : ");
//			uart0_tx_integer((v1.byteB>>16)&0xFFFF);
//			uart0_tx_string("'C");
//
//			uart0_tx_string("\r\n");

			lcd_cmd(0x80);
			lcd_string("T:");
			lcd_data(((((v1.byteB>>16)&(0xFFFF))/10)+48));
			//lcd_data((((((v1.byteB>>16)&(0xFFFF))/10)%10)+48));
			lcd_data(((((v1.byteB>>16)&(0xFFFF))%10)+48));
			lcd_string("'C");
	
			lcd_cmd(0x86);
			lcd_string(" SP:");
			lcd_data(((((v1.byteB&0xFFFF))/100)+48));
			lcd_data((((((v1.byteB&0xFFFF))/10)%10)+48));
			lcd_data(((((v1.byteB&0xFFFF))%10)+48));
			lcd_string("kph");			
			
			switch(v1.byteA&0xFF)
			{
				case 0x10: 
							//uart0_tx_string("headlight ON\r\n");
							head_light_cgram();
							lcd_cmd(0xC1);
							lcd_data(0);
							lcd_cmd(0xC2);
							lcd_data(1);
							IOCLR0=LED1;
							break;

				case 0x11: 
							//uart0_tx_string("headlight OFF\r\n");
							head_light_cgram1();
							lcd_cmd(0xC1);
							lcd_data(0);
							lcd_cmd(0xC2);
							lcd_data(1);
							IOSET0=LED1;
							break;

				case 0x12: 
							//uart0_tx_string("R indi ON\r\n");
							
							// L indi off 
							left_indicator_cgram1();
							lcd_cmd(0xC8);
							lcd_data(4);
							lcd_cmd(0xC9);
							lcd_data(5);
							
							right_indicator_cgram();
							lcd_cmd(0xCD);
							lcd_data(2);
							lcd_cmd(0xCE);
							lcd_data(3);
							IOCLR0=LED2;
							IOSET0=LED3;
							break;

				case 0x13: 
							//uart0_tx_string("R indi OFF\r\n");
							right_indicator_cgram1();
							lcd_cmd(0xCD);
							lcd_data(2);
							lcd_cmd(0xCE);
							lcd_data(3);
							IOSET0=LED2;
							break;

				case 0x14: 
							//uart0_tx_string("L indi ON\r\n");

							// R indi off
							right_indicator_cgram1();
							lcd_cmd(0xCD);
							lcd_data(2);
							lcd_cmd(0xCE);
							lcd_data(3);

							left_indicator_cgram();
							lcd_cmd(0xC8);
							lcd_data(4);
							lcd_cmd(0xC9);
							lcd_data(5);
							IOCLR0=LED3;
							IOSET0=LED2;
							break;

				case 0x15: 
							//uart0_tx_string("L indi OFF\r\n");
							left_indicator_cgram1();
							lcd_cmd(0xC8);
							lcd_data(4);
							lcd_cmd(0xC9);
							lcd_data(5);
							IOSET0=LED3;
							break;
			}
		}
	}
}

