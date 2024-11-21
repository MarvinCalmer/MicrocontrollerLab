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
#include "DMA.h"
#include <math.h>
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
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group11        ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"LM35 AD0.3 ");

	//	LPC_SC->PCLKSEL0 &=~(3<<24);
	//	LPC_SC->PCLKSEL0 |=(1<24);
	// set Clock in adc.c
	
	LPC_PINCON->PINMODE4 &= ~(3<<10);
	LPC_PINCON->PINMODE4 |= (2<<10);
	
	LPC_GPIO2->FIODIR |= (1 << 5);
	
	ADC_Init ((1<<3),0); //initialize channel 3 without interrupt -
	// Set P2.0 high before ADC conversion starts
	LPC_GPIO2->FIOSET = (1 << 5); 
	
	ADC_StartCnv ((1<<3), 0);
	while(1){

    // Wait for ADC conversion to complete
		while (!((ADC_Stat() >> 3) & 1)); 

		// Retrieve ADC result for channel 3
		result3 = ADC_GetValue(3); 
		
		// Set P2.0 low after ADC conversion ends
		LPC_GPIO2->FIOCLR = (1 << 5);
		// Start ADC conversion on channel 3
		ADC_StartCnv((1<<3), 0);		

        // Display the result on the GLCD
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
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.1.2: ADC conv  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group 11      ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"POT1 AD0.4 ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"POT2 AD0.5 ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"LM35 AD0.3 ");	
	
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
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.1.2: ADC conv  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group 11      ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"POT1 AD0.4 ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"POT2 AD0.5 ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"LM35 AD0.3 ");	
	
	
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
	// Set P2.5 high at the start of the interrupt handler
	LPC_GPIO2->FIOSET = (1 << 5);
	
	volatile uint32_t adstat;
	adstat=LPC_ADC->ADSTAT;
	if(adstat&(ACTIVE_CHANNEL3))
		adresult[3]=ADC_GetValue(3);
	if(adstat&(ACTIVE_CHANNEL4))	
		adresult[4]=ADC_GetValue(4);
	if(adstat&(ACTIVE_CHANNEL5))
		adresult[5]=ADC_GetValue(5);
	
	// Set P2.5 low at the end of the interrupt handler
	LPC_GPIO2->FIOCLR = (1 << 5);
	
	//for measure timer
	//for(int i=0;i<100;i++);
}
 
int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.1.3: volt/temp ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group 11       ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"POT1 AD0.4 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"POT2 AD0.5 ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"TEMP AD0.3 ");	
	
	//ACTIVATE PDN IN (A/D CONVERTER) IN SIMULATION BEFORE RUNNING CODE
	ADC_Init ((1<<3) |(1<<4)|(1<<5), 1) ; //ADC channel 3,4,5
	ADC_StartCnv ((1<<3) |(1<<4)|(1<<5), 1);
	
	// Configure P2.4 and P2.5 as output pins
	LPC_GPIO2->FIODIR |= (1 << 4) | (1 << 5); 
	
	while(1)
	{
		// Toggle P2.4 at the beginning of each loop iteration
		LPC_GPIO2->FIOPIN ^= (1 << 4);
		
		GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*)AD_Volt((uint16_t)adresult[4]));
		GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*)AD_Volt((uint16_t)adresult[5]));
		GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*)TempConv((uint16_t)adresult[3]));
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_5 4.2.1 Output of a triangle signal with the D/A-converter
//================================================================================
#if (T41_5==1)

#define SIZE 200
#define PERIOD 200 // 200 ms == T
#define U_MAX 1023 
#define U_MIN 0//range 0 to 3.3V

volatile uint32_t i = 0; 
uint32_t sdata [SIZE];

void generateTriangleWave(void) {
    int highpoint = SIZE / 2;
    for (int i = 0; i < highpoint; i++) {
        sdata[i] = (U_MAX * i) / highpoint;  // Rising edge
				sdata[i] =(sdata[i])<<2;
    }
    for (int i = highpoint; i < SIZE; i++) {
        sdata[i] = ((U_MAX - ((U_MAX * (i - highpoint)) / highpoint)));  // Falling edge
				sdata[i] =(sdata[i])<<2;
    }
		
	}

//void generateSinusoidalWave(void) {
//	for (int i = 0; i < SIZE; i++) {
//			// Generate sinusoidal values
//			sdata[i] = ((int32_t)((sin(i * 3.14159265359 / 100) * 500 + 500))&0x3FF)<<6; // 0 to 1023 (0x3FF)
//	}
//}

void DAC_Timer_Init(void) {
    // Set the reload value to 99 for a 1µs period (100MHz / 1MHz = 100, so 100 - 1 = 99)
    LPC_DAC->DACCNTVAL = 99;
    
    // Enable the DAC timer by setting the CNT_ENA bit in DACCTRL
		LPC_DAC->DACCTRL |= (1 << 2);  // CNT_ENA bit to start countdown timer
		// for testing
		//LPC_DAC->DACCTRL &= ~(1 << 2);  // Setzt das CNT_ENA-Bit (Bit 2) auf 0
    
		// Enable DMA burst request generation (INT_DMA_REQ) on timer countdown
    LPC_DAC->DACCTRL |= (1 << 3);  // DMA_ENA bit to route DMA requests to GPDMA

		// Vllt das noch 
		LPC_DAC->DACCTRL &= ~(1<<1); //disable the DACR double-buffering mode
		LPC_DAC->DACCTRL |= 9;
}

void DAC_Init(void) {
    // Select AOUT for P0.26, PINSEL1[21:20] = 10
    LPC_PINCON->PINSEL1 &= ~(3 << 20);
    LPC_PINCON->PINSEL1 |= (2 << 20);
    
    // Set no pull-up and no pull-down, PINMODE1[21:20] = 10
    LPC_PINCON->PINMODE1 &= ~(3 << 20);
    LPC_PINCON->PINMODE1 |= (2 << 20);
	    // Set DAC clock (PCLK), PCLKSEL0[25:24] = 01
    LPC_SC->PCLKSEL0 |= (1<<22); //CLK
}


int main(void)
{	
	DAC_Init();
	generateTriangleWave();
	//generateSinusoidalWave();
	//TEST
	DAC_Timer_Init(); // Initialisiere den DAC-Timer
	DMA_DAC_func (sdata,200);
	
	// Konfiguriere P2.5 als Ausgang für Toggling
	LPC_GPIO2->FIODIR |= (1 << 5);  // Setze P2.5 als Ausgang
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.2.1: DAC ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group 11       ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"output: 		");
	GLCD_DisplayString(4,10,FONT_16x24,(unsigned char*)"triangle");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Period: 		");
	GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(PERIOD));
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"index:  		");	
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"sdata[i]:  ");	
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"U_out:  		");
	GLCD_Simulation();
	
	while(1)
	{
		LPC_GPIO2->FIOPIN ^=(1<<5); //set high
		GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*) lcd_dez(i));	
		GLCD_DisplayString(7,10,FONT_16x24,(unsigned char*) lcd_dez(sdata[i]));	
		GLCD_DisplayString(8,10,FONT_16x24,(unsigned char*) AD_Volt(sdata[i]));
		GLCD_Simulation();
		LPC_GPIO2->FIOCLR |=(1<<5);  // set low
	} // end while(1)
}	// end main()


#endif

//
//================================================================================
//  Test T41_6 Same as above but with DMA
//================================================================================
#if (T41_6==1)

#define SIZE 200
#define PERIOD 200 // 200 ms == T
#define U_MAX 1023 
#define U_MIN 0//range 0 to 3.3V

volatile uint32_t i = 0; 
uint32_t sdata [SIZE];

//Amplitude
//   ^
//U_MAX    |         /\        /\        /\        /\        /\
// 	       |        /  \      /  \      /  \      /  \      /  \
// 			   |       /    \    /    \    /    \    /    \    /    \
// 	  		 |      /      \  /      \  /      \  /      \  /      \
// 	   	 0 |-----/--------\/--------\/--------\/--------\/--------\-----> Time
//		  	 |    T/2      T        3T/2      2T       5T/2      3T
//  			 |
//U_MIN

void DAC_Init(void) {
    // Select AOUT for P0.26, PINSEL1[21:20] = 10
    LPC_PINCON->PINSEL1 &= ~(3 << 20);
    LPC_PINCON->PINSEL1 |= (2 << 20);
    
    // Set no pull-up and no pull-down, PINMODE1[21:20] = 10
    LPC_PINCON->PINMODE1 &= ~(3 << 20);
    LPC_PINCON->PINMODE1 |= (2 << 20);

    // Set DAC clock (PCLK), PCLKSEL0[25:24] = 01
    LPC_SC->PCLKSEL0 |= (1<<22); //CLK
}

void generateTriangleWave(void) {
    int highpoint = SIZE / 2;
    for (int i = 0; i < highpoint; i++) {
        sdata[i] = (U_MAX * i) / highpoint;  // Rising edge
    }
    for (int i = highpoint; i < SIZE; i++) {
        sdata[i] = U_MAX - ((U_MAX * (i - highpoint)) / highpoint);  // Falling edge
    }
	}

	

void SysTick_Handler (void) {
	
		// DAC_Out
		//voltage at P0.26/AOUT : value/1023*VAREF(3,3V)
		LPC_DAC->DACR=((sdata[i]&0x3FF)<<6); 
		if(i<=SIZE)
			i++;	
		else
			i=0;
		
//		LPC_GPIO2->FIOPIN ^= (1 << 5);  // Toggle P2.5
}


int main(void)
{	
	DAC_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000000); // 1ms clock
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.2.1: DAC ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)" Group 11");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"output:");
	GLCD_DisplayString(4,10,FONT_16x24,(unsigned char*)"triangle");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Period:");
	GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(PERIOD));
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"index: ");	
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"sdata[i]: ");	
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"U_out:"); 
	GLCD_Simulation();
	
	generateTriangleWave();
	
	// Configure P2.5 as output for toggling
	LPC_GPIO2->FIODIR |= (1 << 5);  // Set P2.5 as output
	
	while(1)
	{
		LPC_GPIO2->FIOPIN ^= (1 << 5);  // Toggle P2.5
		
		GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*) lcd_dez(i));	
		GLCD_DisplayString(7,10,FONT_16x24,(unsigned char*) lcd_dez(sdata[i]));	
		GLCD_DisplayString(8,10,FONT_16x24,(unsigned char*) AD_Volt(sdata[i])); // currentlsy not working correctly
		GLCD_Simulation();
	} // end while(1)
}	// end main()


#endif

//
//================================================================================
//  Test T42_1 4.2.2 Generate a sinusoidal wave with the D/A-converter
//================================================================================
#if (T41_7==1)



#define SIZE 200
#define PERIOD 200 // 200 ms == T
#define U_MAX 1023 
#define U_MIN 0//range 0 to 3.3V

volatile uint32_t i = 0; 
uint32_t sdata [SIZE];


void DAC_Timer_Init(void) {
    // Set the reload value to 99 for a 1µs period (100MHz / 1MHz = 100, so 100 - 1 = 99)
    LPC_DAC->DACCNTVAL = 99;
    
    // Enable the DAC timer by setting the CNT_ENA bit in DACCTRL
    LPC_DAC->DACCTRL |= (1 << 2);  // CNT_ENA bit to start countdown timer

    // Enable DMA burst request generation (INT_DMA_REQ) on timer countdown
    LPC_DAC->DACCTRL |= (1 << 3);  // DMA_ENA bit to route DMA requests to GPDMA
		
		// Vllt das noch 
//		LPC_DAC->DACCTRL &= ~(1<<1); //disable the DACR double-buffering mode
//		LPC_DAC->DACCTRL |= 9;
}

void generateSinusoidalWave(void) {
    for (int i = 0; i < SIZE; i++) {
        // Generate sinusoidal values
        sdata[i] = ((uint32_t)(sin(i * 3.14159265359 / 100) * 500 + 500)); // 0 to 1023 (0x3FF)
    }
}


//void SysTick_Handler (void) {
//	
//		// DAC_Out
//		//voltage at P0.26/AOUT : value/1023*VAREF(3,3V)
//		LPC_DAC->DACR=((sdata[i]&0x3FF)<<6); 
//		if(i<=SIZE)
//			i++;	
//		else
//			i=0;
//		
//		LPC_GPIO2->FIOPIN ^= (1 << 5);  // Toggle P2.5
//}


int main(void)
{	
	generateSinusoidalWave();
	DAC_Timer_Init(); // Initialisiere den DAC-Timer
	DMA_DAC_func(sdata, SIZE); // Starte den DMA-Transfer

	// Konfiguriere P2.5 als Ausgang für Toggling
	LPC_GPIO2->FIODIR |= (1 << 5);  // Setze P2.5 als Ausgang
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Microproc tech lab  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test4.2.2: DAC DMA ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"output:");
	GLCD_DisplayString(4,10,FONT_16x24,(unsigned char*)"triangle");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Period:");
	GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(PERIOD));
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"index:  		");	
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"sdata[i]:  ");	
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"U_out:  		");
	GLCD_Simulation();
	

	
	while(1)
	{
		GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*) lcd_dez(i));	
		GLCD_DisplayString(7,10,FONT_16x24,(unsigned char*) lcd_dez(sdata[i]));	
		GLCD_DisplayString(8,10,FONT_16x24,(unsigned char*) AD_Volt(sdata[i]));
		GLCD_Simulation();
	} // end while(1)
}	// end main()
#endif

