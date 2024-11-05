#include <LPC17xx.h>
#include "prio.h"
#define CLKDIV 7

extern void ADC_Init (uint8_t chsel, uint8_t intEn){
	// Power on Bit PCADC
	LPC_SC->PCONP|= (1<<12); 
	LPC_SC->PCONP |=(1<<15);
	
	if ((chsel>>3)&1) {
		//Select required ADC inputPin
		LPC_PINCON->PINSEL1 &= ~(3<<20);
		LPC_PINCON->PINSEL1 |= (1<<20);
		//Select mode for input pins to no pullup nor pulldown
		LPC_PINCON->PINMODE1 &= ~(3<<20);
		LPC_PINCON->PINMODE1 |= (1<<20);
	}
	if ((chsel>>4)&1) {
		//Select required ADC inputPin
		LPC_PINCON->PINSEL3 &= ~(3<<28);
		LPC_PINCON->PINSEL3 |= (3<<28);
		//Select mode for input pins to no pullup nor pulldown
		LPC_PINCON->PINMODE3 &= ~(3<<28);
		LPC_PINCON->PINMODE3 |= (1<<28);
	}
	if ((chsel>>5)&1) {
		//Select required ADC inputPin
		LPC_PINCON->PINSEL3 &= ~(3<<30);
		LPC_PINCON->PINSEL3 |= (3<<30);
		//Select mode for input pins to no pullup nor pulldown
		LPC_PINCON->PINMODE3 &= ~(3<<30);
		LPC_PINCON->PINMODE3 |= (1<<30);
	}

	//Eanble 25Mhz Clock
	//LPC_SC->PCLKSEL0&=~(3<<24); //CCLK/4
	LPC_SC->PCLKSEL0 |= (1<<24); //CLK
	//Set the ADCR register without the select field SEL. 
	LPC_ADC->ADCR|=(CLKDIV<<8);	
	//PDN
	LPC_ADC->ADCR |= (1<<21);
	
	//enable interrupts if intEN is 1
	if(intEn)
		{	
			LPC_ADC->ADINTEN=0;		//Reset ADINTEN register
			LPC_ADC->ADINTEN |= (1UL<<8);  // interrupt by global done flag
				if((chsel>>0)&1UL)    
				{LPC_ADC->ADINTEN|=(1UL<<0);
					LPC_ADC->ADDR0;}
				if((chsel>>1)&1UL) 
					{LPC_ADC->ADINTEN|=(1UL<<1);
					LPC_ADC->ADDR1;}
				if((chsel>>2)&1UL)  
				{	LPC_ADC->ADINTEN|=(1UL<<2);
					LPC_ADC->ADDR2;}
				if((chsel>>3)&1UL)  
				{	LPC_ADC->ADINTEN|=(1UL<<3);
					LPC_ADC->ADDR3;}
				if((chsel>>4)&1UL)  
				{	LPC_ADC->ADINTEN|=(1UL<<4);
					LPC_ADC->ADDR4;}
				if((chsel>>5)&1UL)  
				{	LPC_ADC->ADINTEN|=(1UL<<5);
					LPC_ADC->ADDR5;}
				if((chsel>>6)&1UL)  
				{	LPC_ADC->ADINTEN|=(1UL<<6);
					LPC_ADC->ADDR6;}
				if((chsel>>7)&1UL)  
				{	LPC_ADC->ADINTEN|=(1UL<<7);
					LPC_ADC->ADDR7;}
	
			//NVIC config
			NVIC_ClearPendingIRQ(ADC_IRQn);
			NVIC_SetPriority(ADC_IRQn,PRIO_ADC_IRQN);
			NVIC_EnableIRQ(ADC_IRQn);
		} 
		else {
			LPC_ADC->ADINTEN=0;
		}
}
	
extern void ADC_StartCnv(uint8_t chsel, uint8_t burst){
	
	LPC_ADC->ADCR &= ~(0xFF<<0) & ~(1<<16)  &~(7<<24);
	
	if(burst){
		LPC_ADC->ADINTEN&=~(1UL<<8); //0 in Burst Mode
	  LPC_ADC->ADCR|=(chsel); 
		LPC_ADC->ADCR|=(1UL<<16); 
	}
	else{
		if ( (chsel>>0)&1) {
			LPC_ADC->ADCR |=(1 << 0);
			LPC_ADC->ADDR0;
		}
		else if ( (chsel>>1)&1) {
			LPC_ADC->ADCR |=(1 << 1);
			LPC_ADC->ADDR1;
		}
		else if ( (chsel>>2)&1) {
			LPC_ADC->ADCR |=(1 << 2);
			LPC_ADC->ADDR2;
		}
		else if ( (chsel>>3)&1) {
			LPC_ADC->ADCR |=(1 << 3);
			LPC_ADC->ADDR3;
		}
		else if ( (chsel>>4)&1) {
			LPC_ADC->ADCR |=(1 << 4);
			LPC_ADC->ADDR4;
		}
		else if ( (chsel>>5)&1) {
			LPC_ADC->ADCR |=(1 << 5);
			LPC_ADC->ADDR5;
		}
		else if ( (chsel>>6)&1) {
			LPC_ADC->ADCR |=(1 << 6);
			LPC_ADC->ADDR6;
		}
		else if ( (chsel>>7)&1) {
			LPC_ADC->ADCR |=(1 << 7);
			LPC_ADC->ADDR7;
		}
		// Start
		LPC_ADC->ADCR |= (1<<24);
	}
}

extern void ADC_StopCnv(){
	//Deactivate Burst Mode
	LPC_ADC->ADCR&=~(1UL<<16);
}

extern uint32_t ADC_Stat(){
	return (LPC_ADC->ADSTAT&(0xFF));
}

extern uint32_t ADC_GetValue(unsigned int channel){
	switch(channel){
		case 0:return ((LPC_ADC->ADDR0>>4)&0xFFF);
		case 1:return ((LPC_ADC->ADDR1>>4)&0xFFF);
		case 2:return ((LPC_ADC->ADDR2>>4)&0xFFF);
		case 3:return ((LPC_ADC->ADDR3>>4)&0xFFF);
		case 4:return ((LPC_ADC->ADDR4>>4)&0xFFF);
		case 5:return ((LPC_ADC->ADDR5>>4)&0xFFF);
		case 6:return ((LPC_ADC->ADDR6>>4)&0xFFF);
		case 7:return ((LPC_ADC->ADDR7>>4)&0xFFF);
		default:return 0;
	}
}