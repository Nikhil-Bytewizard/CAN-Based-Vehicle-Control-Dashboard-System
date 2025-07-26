#include <LPC21xx.H>
#include "header.h"		 

void lcd_data(unsigned char data)
{				   
	// higher bit
	unsigned int temp;
	IOCLR1=0xFE<<16;
	temp=(data&0xF0)<<16;
	IOSET1=temp;
	
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
	
	// lower bit
	IOCLR1=0xFE<<16;
	temp=(data&0x0F)<<20;
	IOSET1=temp;
	
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;	
}

void lcd_cmd(unsigned char cmd)
{
	// higher bit
	unsigned int temp;
	IOCLR1=0xFE<<16;
	temp=(cmd&0xF0)<<16;
	IOSET1=temp;

	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;

	// lower bit
	IOCLR1=0xFE<<16;
	temp=(cmd&0x0F)<<20;
	IOSET1=temp;

	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(2);
	IOCLR1=1<<19;
}

void lcd_init(void)
{
	IODIR1=0xFE<<16;
	PINSEL2|=0x0;
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
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
{
	int a[10],i;
	
	if(num==0)
	{
		lcd_data('0');
		return;
	}
	if(num<0)
	{
		num=-num;
		lcd_data('-');
	}
	i=0;
	
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	a[i]='\0';
	

	for(i=i-1;i>=0;i--)
	lcd_data(a[i]);
}

void lcd_float(float f)
{
	int num;
	if(f==0)
	{
		lcd_string("0.0");
		return;
	}		
	
	if(f<0)
	{
		lcd_data('-');
		f=-f;
	}

	num=f;
	lcd_integer(num);
	lcd_data('.');
	num=(f-num)*1000000;
	lcd_integer(num);
		   

}

void lcd_cgram()
{
		int i;
		unsigned char a[10]={0x0, 0xA, 0x15, 0x11, 0x11, 0xA, 0x04};
		unsigned char a1[10]={0x0, 0xA, 0xA, 0x0, 0x0, 0xE, 0x11, 0x0};
		
		lcd_cmd(0x40);
		for(i=0;i<8;i++)
		{
			lcd_data(a[i]);
		}

		lcd_cmd(0x48);
		for(i=0;i<8;i++)
		{
			lcd_data(a1[i]);
		}	
}

void lcd_hex(int temp)
{
	int temp1,temp2;

	temp1=temp/16;
	if(temp1<10)
	lcd_data(temp1+48);
	else
	lcd_data(65+(temp1-10));

	temp2=temp%16;
	if(temp2<10)
	lcd_data(temp2+48);
	else
	lcd_data(65+(temp2-10));
}


/***********************************************************************/

// for DASHBOARD project

//******************* tepm**********************

void degree_cgram()
{
	int i;
	unsigned char d[10]={0x00,0x00,0x0E,0x10,0x10,0x10,0x0E,0x00};
	lcd_cmd(0x70);
	for(i=0;i<8;i++)
	{
		lcd_data(d[i]);
	}
}

//void lcd_ascii(int num)
//{
//	lcd_data((num/100)+48);
//	lcd_data(((num/10)%10)+48);
//	lcd_data((num%10)+48);
//}

/***************************** ON ****************************************/




// left indicaor

void left_indicator_cgram()
{
		int i;
  		unsigned char l[10]={0x0, 0x01, 0x02, 0x07, 0x07, 0x02, 0x01,0x0};
  		unsigned char l1[10]={0x10, 0x0, 0x0, 0x1F, 0x1F, 0x0, 0x0, 0x10};
  		lcd_cmd(0x60);
  		for(i=0;i<8;i++)
		{
			lcd_data(l[i]);
		}
  		lcd_cmd(0x68);
  		for(i=0;i<8;i++)
		{
			lcd_data(l1[i]);
		}	
}


// right indicaor

void right_indicator_cgram()
{
		int j;
  		unsigned char r[10]={0x1, 0x0, 0x0, 0x1F, 0x1F, 0x0,0x0,0x1};
  		unsigned char r1[10]={0x0, 0x10, 0x08, 0x1C, 0x1C, 0x08, 0x10, 0x0};
  		lcd_cmd(0x50);
  		for(j=0;j<8;j++)
		{
			lcd_data(r[j]);
		}
  		lcd_cmd(0x58);
  		for(j=0;j<8;j++)
		{
			lcd_data(r1[j]);
		}	
}


// headlight

void head_light_cgram()

{
		int i;
  		unsigned char h[10]={0x0, 0x01, 0x03, 0x07, 0x0F, 0x0F, 0x0F,0x0};
  		unsigned char h1[10]={0x0, 0x10, 0x18, 0x1C, 0x1E, 0x1E, 0x1E, 0x0};
  		lcd_cmd(0x40);
  		for(i=0;i<8;i++)
		{
			lcd_data(h[i]);
		}

		lcd_cmd(0x48);
  		for(i=0;i<8;i++)
		{
			lcd_data(h1[i]);
		}	
}

/**************************************************************************/





/***************************** OFF ****************************************/

// left indicaor

void left_indicator_cgram1()
{

		int i;
  		unsigned char l[10]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,0x0};
  		unsigned char l1[10]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  		lcd_cmd(0x60);
  		for(i=0;i<8;i++)
		{
			lcd_data(l[i]);
		}
  		lcd_cmd(0x68);
  		for(i=0;i<8;i++)
		{
			lcd_data(l1[i]);
		}	
}




// right indicaor

void right_indicator_cgram1()
{
		int j;
  		unsigned char r[10]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0,0x0,0x0};
  		unsigned char r1[10]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  		lcd_cmd(0x50);
  		for(j=0;j<8;j++)
		{
			lcd_data(r[j]);
		}

		lcd_cmd(0x58);

		for(j=0;j<8;j++)
		{
			lcd_data(r1[j]);
		}	
}


// headlight

void head_light_cgram1()
{
		int i;
  		unsigned char h[10]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,0x0};
  		unsigned char h1[10]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  		lcd_cmd(0x40);
  		for(i=0;i<8;i++)
		{
			lcd_data(h[i]);
		}

		lcd_cmd(0x48);

		for(i=0;i<8;i++)
		{
			lcd_data(h1[i]);
		}	
}



/**************************************************************************/


