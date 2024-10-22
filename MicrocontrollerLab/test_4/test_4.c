/******************************************************************************

test_4.c

	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//Einbinden v. Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"
#include "adc.h"
#include "lcd.h"
//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//
//================================================================================
//  Test T41_1 Task4.1.1 A/D-conversion without interrupt and without burst
//================================================================================
#if (T41_1==1)

uint32_t result3=0;

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.11: ADC conv  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group_13       ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"LM35 AD0.3 ");
	
	
	ADC_Init ((1<<3),0); //initialize channel 3 without interrupt -
	ADC_StartCnv ((1<<3), 0);
	while(1){
		while (!((ADC_Stat ()>>3)&1));//wait for end of conversion
		result3=ADC_GetValue (3); //output result3 to the LCD
		
		ADC_StartCnv ((1<<3), 0);
		GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*)lcd_dez(result3));
		GLCD_Simulation();
	}

}	// end main()

#endif

//
//================================================================================
//  Test T41_2 4.1.2 A/D-conversion of channels 3,4,5 and visualization on the LCD
//================================================================================
#if (T41_2==1)

uint32_t result3=0,result4=0,result5=0;

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.12: ADC conv  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group_13       ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"POT1 AD0.4 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"POT2 AD0.5 ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"LM35 AD0.3 ");	
	
	
	ADC_Init ((1<<3)|(1<<4)|(1<<5),0); //initialize channel 3 without interrupt -



	
	while(1){
		ADC_StartCnv ((1<<3), 0);
		while (!((ADC_Stat ()>>3)&1));//wait for end of conversion
		result3=ADC_GetValue (3); //output result3 to the LCD
		ADC_StartCnv ((1<<3), 0);
		GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*)lcd_dez(result3));
		
		ADC_StartCnv ((1<<4), 0);
		while (!((ADC_Stat ()>>4)&1));//wait for end of conversion
		result4=ADC_GetValue (4); //output result3 to the LCD
		ADC_StartCnv ((1<<4), 0);
		GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*)lcd_dez(result4));
		
		ADC_StartCnv ((1<<5), 0);
		while (!((ADC_Stat ()>>5)&1));//wait for end of conversion
		result5=ADC_GetValue (5); //output result3 to the LCD
		ADC_StartCnv ((1<<5), 0);
		GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*)lcd_dez(result5));
		
		GLCD_Simulation();
	}

}	// end main()

#endif



//
//================================================================================
//  Test T41_3 4.1.3 Output the measured values in volts and degrees centigrade
//================================================================================
#if (T41_3==1)

uint32_t result3=0,result4=0,result5=0;

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.12: ADC conv  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group_13       ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"POT1 AD0.4 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"POT2 AD0.5 ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"LM35 AD0.3 ");	
	
	
	ADC_Init ((1<<3)|(1<<4)|(1<<5),0); //initialize channel 3 without interrupt -



	
	while(1){
		ADC_StartCnv ((1<<3), 0);
		while (!((ADC_Stat ()>>3)&1));//wait for end of conversion
		result3=ADC_GetValue (3); //output result3 to the LCD
		ADC_StartCnv ((1<<3), 0);
		GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*)TempConv(result3));
		
		ADC_StartCnv ((1<<4), 0);
		while (!((ADC_Stat ()>>4)&1));//wait for end of conversion
		result4=ADC_GetValue (4); //output result3 to the LCD
		ADC_StartCnv ((1<<4), 0);
		GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*)AD_Volt(result4));
		
		ADC_StartCnv ((1<<5), 0);
		while (!((ADC_Stat ()>>5)&1));//wait for end of conversion
		result5=ADC_GetValue (5); //output result3 to the LCD
		ADC_StartCnv ((1<<5), 0);
		GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*)AD_Volt(result5));
		
		GLCD_Simulation();
	}

}	// end main()

#endif
//
//================================================================================
//  Test T41_4 4.1.4 A/D-conversion with Interrupt, Burst Mode and visualization on the LCD
//================================================================================
#if (T41_4==1)

#define ACTIVE_CHANNELS (7<<3)
#define ACTIVE_CHANNEL3 (1<<3)
#define ACTIVE_CHANNEL4 (1<<4)
#define ACTIVE_CHANNEL5 (1<<5)

uint32_t adresult[8]={0,0,0,0,0,0,0,0};

void ADC_IRQHandler(void)
{
	volatile uint32_t adstat;
	adstat=LPC_ADC->ADSTAT;
	if(adstat&(ACTIVE_CHANNEL3))
		adresult[3]=ADC_GetValue(3);
	if(adstat&(ACTIVE_CHANNEL4))	
		adresult[4]=ADC_GetValue(4);
	if(adstat&(ACTIVE_CHANNEL5))
		adresult[5]=ADC_GetValue(5);
}
 
int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.13: volt/temp ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group_13       ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"POT1 AD0.4 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"POT2 AD0.5 ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"TEMP AD0.3 ");	
	
	//ACTIVATE PDN IN (A/D CONVERTER) IN SIMULATION BEFORE RUNNING CODE
	ADC_Init ((1<<3) |(1<<4)|(1<<5), 1) ; //ADC channel 3,4,5
	ADC_StartCnv ((1<<3) |(1<<4)|(1<<5), 1);
	
	while(1)
	{
		GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*)AD_Volt((uint16_t)adresult[4]));
		GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*)AD_Volt((uint16_t)adresult[5]));
		GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*)TempConv((uint16_t)adresult[3]));
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_5
//================================================================================
#if (T41_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_6
//================================================================================
#if (T41_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_1
//================================================================================
#if (T42_1==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_2
//================================================================================
#if (T42_2==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif
