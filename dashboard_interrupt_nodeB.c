#include <LPC21xx.H>
#include "header.h"

CAN2 v1;
u8 flag=0;

void CAN2_ISR(void)__irq
{
	v1.id=C2RID;
	v1.dlc=(C2RFS>>16)&0xF;
	v1.rtr=((C2RFS>>30)&1);
	
	if(v1.rtr==0)
	{
		v1.byteA=C2RDA;
		v1.byteB=C2RDB;
	}	

	C2CMR=(1<<2);
	flag=1;
	VICVectAddr=0;				
}


void config_vic_for_can2(void)
{   
	VICIntSelect=0;
	VICVectCntl6=27|(1<<5);
	VICVectAddr6=(u32)CAN2_ISR;
	VICIntEnable|=(1<<27);
}

void config_can2(void)
{
	C2IER=1;
}

