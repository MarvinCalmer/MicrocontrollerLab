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
#include "led.h"
#include "keys.h"
#include "lcd.h"


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
//  Test T2_2 Task 2.1 & Task 2.2
//================================================================================
#if (T2_2 == 1)



int main(void)
{	
	Switch_Init();
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test2.1 switchpos");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group .... ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Binary: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"hex: ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Decimal: ");
	
	GLCD_Simulation();
	while(1)
	{
		uint8_t value = Get_SwitchPos();
		
		GLCD_DisplayString(4,10,FONT_16x24,(unsigned char*)lcd_bin(value));
		GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_hex(value));
		GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez(value));
		
		GLCD_Bargraph(30,160,255,20,value*4);
		
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_3 	Task 2.3
//================================================================================
#if (T2_3 == 1)

int main(void)
{	
	Switch_Init();
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test2.2 Switches");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group .... ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Value");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Voltage");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Temperature");
	
	while(1)
	{
		unsigned short value = (Get_SwitchPos ()<<4)| 0xF;
		
		GLCD_DisplayString(4,15,FONT_16x24,(unsigned char*)lcd_dez(value));
		GLCD_DisplayString(5,15,FONT_16x24,(unsigned char*) AD_Volt(value));
		GLCD_DisplayString(6,15,FONT_16x24,(unsigned char*) TempConv(value));
		GLCD_Simulation();
		
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
	Switch_Init();
	Matrix_Init();
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test2.3 Matrix");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group .... ");
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Key");
	GLCD_Simulation();
	
	while(1)
	{
		unsigned char matrixKey =Get_Mkey();
		GLCD_DisplayString(8,15,FONT_16x24,&matrixKey);
		GLCD_Simulation();
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



