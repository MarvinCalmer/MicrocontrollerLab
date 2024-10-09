/******************************************************************************
test_2.c
*******************************************************************************
	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"


//================================================================================
//Definitions and constants:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24


//================================================================================
//  Test T2_1
//================================================================================
#if (T2_1 == 1)

#include "GLCD.h"
#include "gpio.h"


#define OUT_PORT PORT2
#define PORT_PIN 2


int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"PORT_PIN=");

	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	GLCD_Simulation();


	while(1)
	{	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_HIGH);
		GLCD_Simulation();
		GLCD_DisplayString(5,9,FONT_16x24,(unsigned char*)"1");
		GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
		GLCD_Simulation();		
		GLCD_DisplayString(5,9,FONT_16x24,(unsigned char*)"0");
	}
	
}	// end main()

#endif


//
//================================================================================
//  Test T2_2
//================================================================================
#if (T2_2 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_3
//================================================================================
#if (T2_3 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T2_4
//================================================================================
#if (T2_4 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_5
//================================================================================
#if (T2_5 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T2_6
//================================================================================
#if (T2_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



