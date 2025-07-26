#include <LPC21xx.H>
#include "header.h"
#include <string.h>
#include<stdio.h>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(u32 baud)
{
	char a[]={15,60,30,15};
	u32 pclk=0,result=0;
	pclk=a[VPBDIV]*1000000;	
	result= pclk/(16*baud);
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLL=result&0xFF;
	U0DLM=(result>>8)&0xFF;
	U0LCR=0x03;
}

void uart0_tx(u8 data)
{
	U0THR=data;
	while(THRE==0);	
}

u8 uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_string(s8 *ptr)
{
	while(*ptr)
	{
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}
}												 

void uart0_rx_string(char *ptr,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		while(RDR==0);
		ptr[i]=U0RBR;

		if(ptr[i]=='\r')
		break;
	}
	ptr[i]='\0';
}

void uart0_hex(u8 temp)
{
		u8 temp1,temp2;
		temp1=temp/16;
		if(temp1<10)
		uart0_tx(temp1+48);
		else
		uart0_tx(65+(temp1-10));
		
		temp2=temp%16;
		if(temp2<10)
		uart0_tx(temp2+48);
		else
		uart0_tx(65+(temp2-10));
}

u8 my_strcmp(s8 *p,s8 *q)
{
	u8 i;
	for(i=0;p[i];i++)
	{
		if(p[i]!=q[i])
		break;
	}
	if(p[i]==q[i])
	return 1;
	else
	return 0;
}

// convert integer to ascii
void uart0_tx_integer(int num)
{
	char a[10];
	int i;

	if(num==0)
	{
		uart0_tx('0');
		return;
	}
	if(num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	i=0;
	while(num>0)
	{
		a[i]=num%10+48;	
		num=num/10;
		i++;
	}

	for(i=i-1;i>=0;i--)
	uart0_tx(a[i]);
}

// convert float to ascii
/*void uart0_tx_int(float f)
{
	char a[10];
	int i;

	if(f==0)
	{
		uart0_tx_string("0.0");
		return;
	}
	if(f<0)
	{
		uart0_tx('-');
		f=-f;
	}
	i=0;
	while(f>0)
	{
		a[i]=f%10+48;	
		num=num/10;
		i++;
	}

	for(i=i-1;i>=0;i--)
	uart0_tx(a[i]);
} */

int uart0_rx_int()
{
	int i,num=0;
	char a[10];
	
	uart0_rx_string(a,10);

	if(a[0]=='-' || a[0]=='+')
	i=1;
	else
	i=0;

	for(i=0;a[i];i++)
	num=num*10+a[i]-48;

	if(a[0]=='-')
	num=-num;

	return num;
}

int uart0_rx_integer(char *a)
{
	int i,num=0;
	//char a[10];

	if(a[0]=='-' || a[0]=='+')
	i=1;
	else
	i=0;

	for(;a[i];i++)
	num=num*10+a[i]-48;

	if(a[0]=='-')
	num=-num;

	return num;
}

/*void uart0_tx_integer(int num)
{
	s8 a[10];
	sprintf(a,"%d",num);
	uart0_tx_string(a);
} */

/*void uart0_tx_float(float num)
{
	s8 a[10];
	sprintf(a,"%f",num);
	uart0_tx_string(a);
}*/












