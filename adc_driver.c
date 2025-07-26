#include <LPC21xx.H>
#include "header.h"

void adc_init(void)
{
	PINSEL1|=0x15400000;
	ADCR=0x00200400;		 	// channel not select,ADC freq 3+1 mhz, burst off, stop ADC conv, PDN=1, 10bit reso  
}

u32 adc_read(u8 ch_num)	    	// channel number
{
	u32 temp;
	ADCR|= (1<<ch_num);	   		// channel select
	ADCR|= (1<<24);			    // ADC conversion start
	while(((ADDR>>31)&1)==0);   // waiting for ADC convorsion done
	ADCR^= (1<<24); 		    // ADC conv stop
	ADCR^= (1<<ch_num);	   		// channel disselect
	temp=(ADDR>>6)&0x3FF;	    // extract 10bit result
	return temp;			    // return result
}

