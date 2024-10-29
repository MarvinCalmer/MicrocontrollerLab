#include "tests.h"

// with TimerNum = 0,1,2,3, the desired timer number
// CapIn = 0,1, the desired CAP input (CAPx.0 and CAPx.1)
// edge: the desired edge, 1: rising edge , 2: falling edge , 3:both edges
extern void Counter_Init(uint8_t TimerNum, uint8_t CapIn, uint8_t edge){
	//Power Control GPIO
	LPC_SC->PCONP |= (1<<15);
	
	if (TimerNum==0)
			{
			LPC_SC->PCONP |= (1<<1);// Power Timer 0 
		
			LPC_TIM0->CTCR&=~(3<<0) & (3<<2);	
			
			if(!CapIn){
				LPC_PINCON->PINSEL3 |= (3<<20); // P1.26=CAP0.0/clockinput
				LPC_PINCON->PINMODE3&=~(3<<20);		// no Pullup 	
				LPC_PINCON->PINMODE3|=(2<<20);
			}
			else {
				LPC_PINCON->PINSEL3 |= (3<<22); // P1.26=CAP0.0/clockinput
				LPC_PINCON->PINMODE3&=~(3<<22); // no Pullup 
				LPC_PINCON->PINMODE3|=(2<<22);
			}
			switch (edge){
				case 1:
					LPC_TIM0->CTCR|=(1<<0);
				case 2:
					LPC_TIM0->CTCR|=(2<<0);
				case 3:
					LPC_TIM0->CTCR|=(3<<0);
				default: break;
			}	
			LPC_TIM0->TCR=(1<<1); //RESET Timer
			LPC_TIM0->TCR=(1<<0); //START TIMER
			} 
	else if (TimerNum==1)
			{
			LPC_SC->PCONP |=(1<<2);		//POWER CONTROL TIMER1
		
			LPC_TIM1->CTCR&=~(3<<0) & (3<<2);	
			
			if(!CapIn){
				LPC_PINCON->PINSEL3|=(3<<4);
				LPC_PINCON->PINMODE3&=~(3<<4);
				LPC_PINCON->PINMODE3|=(2<<4);
			}
			else {
				LPC_PINCON->PINSEL3|=(3<<6);
				LPC_PINCON->PINMODE3&=~(3<<6);
				LPC_PINCON->PINMODE3|=(2<<6);
			}
			switch (edge){
				case 1:
					LPC_TIM1->CTCR|=(1<<0);
				case 2:
					LPC_TIM1->CTCR|=(2<<0);
				case 3:
					LPC_TIM1->CTCR|=(3<<0);
				default: break;
			}	
			LPC_TIM1->TCR=(1<<1); //RESET Timer
			LPC_TIM1->TCR=(1<<0); //START TIMER
			} 
	else if (TimerNum==2)
			{
			LPC_SC->PCONP |=(1<<22);		//POWER CONTROL TIMER2
		
			LPC_TIM2->CTCR&=~(3<<0) & (3<<2);	
			
			if(!CapIn){
				LPC_PINCON->PINSEL0|=(3<<8);
				LPC_PINCON->PINMODE0&=~(3<<8);
				LPC_PINCON->PINMODE0|=(2<<8);
			}
			else {
				LPC_PINCON->PINSEL0|=(3<<10);
				LPC_PINCON->PINMODE0&=~(3<<10);
				LPC_PINCON->PINMODE0|=(2<<10);
			}
			switch (edge){
				case 1:
					LPC_TIM2->CTCR|=(1<<0);
				case 2:
					LPC_TIM2->CTCR|=(2<<0);
				case 3:
					LPC_TIM2->CTCR|=(3<<0);
				default: break;
			}	
			LPC_TIM2->TCR=(1<<1); //RESET Timer
			LPC_TIM2->TCR=(1<<0); //START TIMER
			} 
		else if (TimerNum==3)
			{
			LPC_SC->PCONP |=(1<<23);		//POWER CONTROL TIMER2
		
			LPC_TIM3->CTCR&=~(3<<0) & (3<<2);	
			
			if(!CapIn){
				LPC_PINCON->PINSEL1|=(3<<14);
				LPC_PINCON->PINMODE1&=~(3<<14);
				LPC_PINCON->PINMODE1|=(2<<14);
			}
			else {
				LPC_PINCON->PINSEL1|=(3<<16);
				LPC_PINCON->PINMODE1&=~(3<<16);
				LPC_PINCON->PINMODE1|=(2<<16);
			}
			switch (edge){
				case 1:
					LPC_TIM3->CTCR|=(1<<0);
				case 2:
					LPC_TIM3->CTCR|=(2<<0);
				case 3:
					LPC_TIM3->CTCR|=(3<<0);
				default: break;
			}	
			LPC_TIM3->TCR=(1<<1); //RESET Timer
			LPC_TIM3->TCR=(1<<0); //START TIMER
			} 
}

// TimerNum Timer 0..3
// cycle : timer period in timer increments/counts of the timer)
// TimerDivid: Clock divider (prescaler) in Timer (LPC_TimX->PR)+1
// pclksrc: pclk/clocksource for timer (0:cclk/4, 1: cclk /1; 2:cclk /2, 3:cclk /8)
// ResetMR 0:reset at MR0, 1:MR1:1, 2:MR2:2, 3:MR3, >=4:no Reset)
extern void Timer_Init (uint8_t TimerNum, uint32_t cycle, uint32_t TimerDivid, uint8_t pclksrc , uint8_t ResetMR){
	//Power Control GPIO
	LPC_SC->PCONP |= (1<<15);
	
	if (TimerNum==0)
		{
		LPC_SC->PCONP |= (1<<1);// Power Timer 0 
		LPC_TIM0->CTCR = 0;	// TImer Mode
			
		LPC_SC->PCLKSEL0&=~(3<<2);		//PCLK=CCLK/4 Reset, default
		if (pclksrc==1)
			{LPC_SC->PCLKSEL0|=(1<<2);}
		else if (pclksrc==2)
			{LPC_SC->PCLKSEL0|=(2<<2);}
		else if (pclksrc==3)
			{LPC_SC->PCLKSEL0|=(3<<2);}
		
		// Clock
		LPC_TIM0->PR=(TimerDivid)-1;
			
		if (ResetMR == 0)
		{
			LPC_TIM0->MCR |= (1<<1);					//configure to reset on match (MR0)
			LPC_TIM0->MR0 = cycle-1;						//set Match register MR0 to cycle (reset of timer counter)
		}
		else if (ResetMR == 1)
		{
			LPC_TIM0->MCR |= (1<<4);					//configure to reset on match (MR1)
			LPC_TIM0->MR1 = cycle-1;						//set Match register MR1 to cycle (reset of timer counter) 
		}
		else if (ResetMR == 2)
		{
			LPC_TIM0->MCR |= (1<<7);
			LPC_TIM0->MR2 = cycle-1;
		}
		else if (ResetMR == 3)
		{
			LPC_TIM0->MCR |= (1<<10);
			LPC_TIM0->MR3 = cycle-1;
		}
		else
		{
			LPC_TIM0->MCR = 0;
		}	
		
		LPC_TIM0->TCR=(1<<1); //RESET Timer
		LPC_TIM0->TCR=(1<<0); //START TIMER
		} 
	if (TimerNum==1)
		{
		LPC_SC->PCONP |= (1<<2);// Power Timer 0 
		LPC_TIM1->CTCR = 0;	// TImer Mode
			
		LPC_SC->PCLKSEL0&=~(3<<2);		//PCLK=CCLK/4 Reset, default
		if (pclksrc==1)
			{LPC_SC->PCLKSEL0|=(1<<2);}
		else if (pclksrc==2)
			{LPC_SC->PCLKSEL0|=(2<<2);}
		else if (pclksrc==3)
			{LPC_SC->PCLKSEL0|=(3<<2);}
		
		// Clock
		LPC_TIM1->PR=(TimerDivid)-1;
			
		if (ResetMR == 0)
		{
			LPC_TIM1->MCR |= (1<<1);					//configure to reset on match (MR0)
			LPC_TIM1->MR0 = cycle-1;						//set Match register MR0 to cycle (reset of timer counter)
		}
		else if (ResetMR == 1)
		{
			LPC_TIM1->MCR |= (1<<4);					//configure to reset on match (MR1)
			LPC_TIM1->MR1 = cycle-1;						//set Match register MR1 to cycle (reset of timer counter) 
		}
		else if (ResetMR == 2)
		{
			LPC_TIM1->MCR |= (1<<7);
			LPC_TIM1->MR2 = cycle-1;
		}
		else if (ResetMR == 3)
		{
			LPC_TIM1->MCR |= (1<<10);
			LPC_TIM1->MR3 = cycle-1;
		}
		else
		{
			LPC_TIM1->MCR = 0;
		}	
		
		LPC_TIM1->TCR=(1<<1); //RESET Timer
		LPC_TIM1->TCR=(1<<0); //START TIMER
		} 
	if (TimerNum==2)
		{
		LPC_SC->PCONP |= (1<<22);// Power Timer 0 
		LPC_TIM2->CTCR = 0;	// TImer Mode
			
		LPC_SC->PCLKSEL0&=~(3<<2);		//PCLK=CCLK/4 Reset, default
		if (pclksrc==1)
			{LPC_SC->PCLKSEL0|=(1<<2);}
		else if (pclksrc==2)
			{LPC_SC->PCLKSEL0|=(2<<2);}
		else if (pclksrc==3)
			{LPC_SC->PCLKSEL0|=(3<<2);}
		
		// Clock
		LPC_TIM2->PR=(TimerDivid)-1;
			
		if (ResetMR == 0)
		{
			LPC_TIM2->MCR |= (1<<1);					//configure to reset on match (MR0)
			LPC_TIM2->MR0 = cycle-1;						//set Match register MR0 to cycle (reset of timer counter)
		}
		else if (ResetMR == 1)
		{
			LPC_TIM2->MCR |= (1<<4);					//configure to reset on match (MR1)
			LPC_TIM2->MR1 = cycle-1;						//set Match register MR1 to cycle (reset of timer counter) 
		}
		else if (ResetMR == 2)
		{
			LPC_TIM2->MCR |= (1<<7);
			LPC_TIM2->MR2 = cycle-1;
		}
		else if (ResetMR == 3)
		{
			LPC_TIM2->MCR |= (1<<10);
			LPC_TIM2->MR3 = cycle-1;
		}
		else
		{
			LPC_TIM2->MCR = 0;
		}	
		
		LPC_TIM2->TCR=(1<<1); //RESET Timer
		LPC_TIM2->TCR=(1<<0); //START TIMER
		} 
	if (TimerNum==3)
		{
		LPC_SC->PCONP |= (1<<23);// Power Timer 0 
		LPC_TIM3->CTCR = 0;	// TImer Mode
			
		LPC_SC->PCLKSEL0&=~(3<<2);		//PCLK=CCLK/4 Reset, default
		if (pclksrc==1)
			{LPC_SC->PCLKSEL0|=(1<<2);}
		else if (pclksrc==2)
			{LPC_SC->PCLKSEL0|=(2<<2);}
		else if (pclksrc==3)
			{LPC_SC->PCLKSEL0|=(3<<2);}
		
		// Clock
		LPC_TIM3->PR=(TimerDivid)-1;
			
		if (ResetMR == 3)
		{
			LPC_TIM3->MCR |= (1<<1);					//configure to reset on match (MR0)
			LPC_TIM3->MR0 = cycle-1;						//set Match register MR0 to cycle (reset of timer counter)
		}
		else if (ResetMR == 1)
		{
			LPC_TIM3->MCR |= (1<<4);					//configure to reset on match (MR1)
			LPC_TIM3->MR1 = cycle-1;						//set Match register MR1 to cycle (reset of timer counter) 
		}
		else if (ResetMR == 2)
		{
			LPC_TIM3->MCR |= (1<<7);
			LPC_TIM3->MR2 = cycle-1;
		}
		else if (ResetMR == 3)
		{
			LPC_TIM3->MCR |= (1<<10);
			LPC_TIM3->MR3 = cycle-1;
		}
		else
		{
			LPC_TIM3->MCR = 0;
		}	
		
		LPC_TIM3->TCR=(1<<1); //RESET Timer
		LPC_TIM3->TCR=(1<<0); //START TIMER
		} 
}