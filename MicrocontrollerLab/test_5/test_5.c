/*******************************************************************************

test5.c


	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"
#include "timer.h"
#include "lcd.h"


//================================================================================
//Definition 
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24


//================================================================================
//  test T51 Task 5.1
//================================================================================
#if (T5_1==1)

int main(void)
{	
	Counter_Init(0,0,1);
	uint8_t countvalue=0;
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.1 Counter");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Press Button TA11");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Timer0: 					");

	GLCD_Simulation();
	while(1)
	{
			countvalue= LPC_TIM0->TC;
			GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez(countvalue));
			GLCD_Simulation();

	} // end while(1)
}	// end main()

#endif



#if (T5_2==1)
//
//================================================================================
//  test T52  Task 5.2
//================================================================================

uint32_t tcvalue=0;

void TIMER0_IRQHandler(void){


	if (LPC_TIM0->IR&(1))								//MR0 interrupt (MR0)
		{
			LPC_GPIO2->FIOPIN ^= (1<<5);
			LPC_TIM0-> IR |= (1);							//Reset interrupt on match (MR0)
		}
}

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.2 Timer");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"tcvalue:	");


	GLCD_Simulation();
	//SystemCoreClockUpdate();
	Timer_Init (0,1000,100,1,0);
	
	LPC_TIM0->MCR |= (1);							//configure to create interupt on match (MR0)
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, 30);
	//LPC_TIM0 -> TCR = 1;
	
	LPC_GPIO2->FIODIR |= (1UL << 5); //P2.5

	while(1)
	{
		tcvalue=LPC_TIM0->TC;
		GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(tcvalue));
		GLCD_Simulation();
		
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  test T53 Task 5.3
//================================================================================
#if (T5_3==1)

//uint32_t tcvalue=0;

void TIMER0_IRQHandler(void){
	if (LPC_TIM0->IR&(1))								//MR0 interrupt (MR0)
		{
			LPC_GPIO2->FIOPIN ^= (1<<5);
			LPC_TIM0-> IR |= (1);							//Reset interrupt on match (MR0)
		}
		if (LPC_TIM0->IR&(1<<4))						//CR0 interrupt (CAP0.0) - rising edge
		{
			LPC_GPIO2->FIOPIN |= (1<<4);
			LPC_TIM0-> IR |= (1<<4);					//Reset interrupt on match (MR0)
		}
		if (LPC_TIM0->IR&(1<<5))						//CR1 interrupt (CAP0.1) - falling edge
		{
			LPC_GPIO2->FIOPIN &= ~(1<<4);
			LPC_TIM0-> IR |= (1<<5);					//Reset interrupt on match (MR0)
		}
}


int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.2 Timer");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
//	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"tcvalue:	");


	GLCD_Simulation();
	//SystemCoreClockUpdate();
	Timer_Init (0,1000,100,1,0);
	
	LPC_TIM0->MCR |= (1);											//configure to create interupt on match (MR0)
	LPC_TIM0->CCR |= ((1<<0) | (1<<2));				//perform interupt on CAP0.0 rising edge
	LPC_TIM0->CCR |= ((1<<4) | (1<<5));				//perform interupt on CAP0.1 falling edge
	
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, 30);
	
	LPC_PINCON->PINSEL3 |= (3<<20);
	LPC_PINCON->PINSEL3 |= (3<<22);
	//LPC_PINCON->PINSEL4 |= (2<<10);
	LPC_GPIO2->FIODIR |= (1UL << 4); //P2.4
	LPC_GPIO2->FIODIR |= (1UL << 5); //P2.5
	LPC_TIM0 -> TCR = 1;
	
	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T54
//================================================================================
#if (T5_4==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  test T5_55
//================================================================================
#if (T5_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


#if (T5_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  test T5_7
//================================================================================
#if (T5_7==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


