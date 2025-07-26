#include<lpc21xx.h>
  #include "header.h"
  void delay_sec(unsigned int sec)
  {
  	int a[]={15,60,30,15};
	u32 pclk=a[VPBDIV]*1000000-1;
  	T0PC=0;
	T0PR=pclk;      // for 1 sec
	T0TC=0;
	T0TCR=1;
	while(T0TC<sec);
	T0TCR=0;
  }

  void delay_ms(unsigned int ms)
  {
  	int a[]={15,60,30,15};
	u32 pclk=a[VPBDIV]*1000-1;
  	T0PC=0;
	T0PR=pclk;      // for 1 milisec
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
  }

