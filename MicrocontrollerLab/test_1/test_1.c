/******************************************************************************
test_1.c
******************************************************************************/


//	Autor: 
//	date: 
	       

/********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "keys.h"


//================================================================================
//definition constants:
//================================================================================


//================================================================================
//  Main-Funktion Test1 T1_1 Example1
//================================================================================
#if (T1_1 == 1)

#define OUT_PORT 0
#define PORT_PIN 0

int main(void)
{	
	GLCD_Init();
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	
	while(1)
	{	
		GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_HIGH);
		GLCD_Simulation();
		delayXms(5);
		GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);	
		GLCD_Simulation();
		delayXms(5);
	}
	
}	// end main()
#endif


//================================================================================
//  Main-Function Test T1_2 Example 2
//================================================================================
#if (T1_2 == 1)

//uint8_t get_switchPos(void){ //return state of ports S7:S0 (P1.25:P1.18)
//return (LPC_GPIO1->FIOPIN >> 18);} 

//unsigned int Get_TA10Stat(void){return ((LPC_GPIO1->FIOPIN>>26&1));};//return "1" when Button TA10 is pressed

int main(void)
{	
	////necessary init operations for labTest_1
	////init rgb's
	//LPC_GPIO0->FIODIR |=(1UL<<10); 
	//LPC_GPIO0->FIODIR |=(1UL<<11);
	//LPC_GPIO4->FIODIR |=(1UL<<29);
		
	//init switches S0..7:
//	LPC_PINCON->PINMODE3|=(0xAAAA<<4);//P1.18...25
	//init Joystick:
	LPC_PINCON->PINMODE0 |= (2 << 6); //P0.3
	LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21
	LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25
	LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27
	LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
	//init buttons TA10..12
	LPC_PINCON->PINMODE3 |= (2 << 20);//P1.26
	LPC_PINCON->PINMODE3 |= (2 << 22);//P1.27
	LPC_PINCON->PINMODE4 |= (2 << 22);//P2.11

	//init_matrix
	LPC_GPIO2->FIODIR |=(1UL<<3);//P0.3
	LPC_GPIO2->FIODIR |=(1UL<<4);//P0.4
	LPC_GPIO2->FIODIR |=(1UL<<5);//P0.5
	LPC_PINCON->PINMODE0 |= (2 << 8);//P0.4
	LPC_PINCON->PINMODE0 |= (2 << 10);//P0.5
	LPC_PINCON->PINMODE7 |= (2 << 20);//P3.26



		GLCD_Init();
		LED_Init();
		Switch_Init();
		Button_Init();
		GLCD_Simulation();

	while(1)
	{
		uint8_t test=Get_SwitchPos();
		int push= Get_TA12Stat();
		GLCD_Simulation();
		if(push){
			LED_On(5);
			GLCD_Simulation();
		}
		else{
			LED_Off(5);
			GLCD_Simulation();
		}
//		if ((get_switchPos()>>0)&1) LED_On(0);else LED_Off(0);GLCD_Simulation();// as long as switch S0 is on -> LED0 is on
//		if (Get_TA10Stat())         RGB_On(0);else RGB_Off(0);GLCD_Simulation();// as long as button TA10 is pressed -> RGB0 (Blue) is on		
	} 
}	

#endif



//================================================================================
//  Main-Function Test T1_3
//================================================================================
#if (T1_3 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function TestT1_4
//================================================================================
#if (T1_4 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  Main-Function Test T1_5
//================================================================================
#if (T1_5 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Function Test T1_6
//================================================================================
#if (T1_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Funktion Test T1_7
//================================================================================
#if (T1_7 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

