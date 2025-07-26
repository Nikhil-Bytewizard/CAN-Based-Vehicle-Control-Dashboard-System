#include <LPC21xx.H>
#include "header.h"

void can2_init(void)
{
			  		// 60 mhz
	PINSEL1|=0x00014000;		// RD2=p0.23, TD2=p0.24;
	C2MOD=1;					// reset mode ON
	VPBDIV=1;
	C2BTR=0x001C001D;			// 125khz baud setting
	AFMR=2;						// AccBP=1; accept all receive msg, bypass
	C2MOD=0;					// mode OFF
}

#define TCS ((C2GSR>>3)&1)

void can2_tx(CAN2 v)
{
	C2TID1=	v.id;				// identifier
	C2TFI1=	v.dlc<<16;			// RTR=0,standard DF, DLC;
	
	if(v.rtr==0)
	{
		C2TDA1= v.byteA;
		C2TDB1= v.byteB;
	}
	else
	C2TFI1|=1<<30;				// RTR=1

	C2CMR=1|(1<<5);				// start transmission and select tx buffer 1
	while(TCS==0);
}

#define RBS (C2GSR&1)

void can2_rx(CAN2 *ptr)
{
	while(RBS==0);
	ptr->id=C2RID;
	ptr->dlc=(C2RFS>>16)&0xF;		// extract DLC
	ptr->rtr=(C2RFS>>30)&1;			// extract rtr

	if(ptr->rtr==0)					// if data frame
	{
		ptr->byteA=C2RDA;			// get lower 4 bytes data
		ptr->byteB=C2RDB;			// get higher 4 bytes data
	}

	C2CMR=(1<<2);			  		// release rx buffer
}

