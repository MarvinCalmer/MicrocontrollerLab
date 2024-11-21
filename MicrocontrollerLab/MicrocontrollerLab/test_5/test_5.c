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
#include "led.h"
#include "adc.h"
#include "keys.h"


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
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor   ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.1 Counter     ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Press Button TA10");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Timer0:          ");

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
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor   ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.2 Timer       ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"tcvalue:  ");


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

#define cycle_length 10000// equals time of period

uint32_t period=0; // period count
uint32_t tRising=0;
uint32_t tFalling=0;
uint32_t tHigh=0;
uint32_t tLow=0;


void TIMER0_IRQHandler(void)
{
	if (LPC_TIM0->IR&(1))								//MR0 interrupt (MR0)
	{
		LPC_TIM0->IR = (1 << 0);							//Reset interrupt on match (MR0)
		LPC_GPIO2->FIOPIN ^= (1<<5);
		period++;
	}
	
	if (LPC_TIM0->IR&(1<<4))						//CR0 interrupt (CAP0.0) - rising edge
	{
		LPC_TIM0-> IR = (1<<4);					//Reset interrupt on match (MR0)
		tRising = LPC_TIM0->CR0;
		//period = 0;
		tLow = (period * cycle_length) + (tRising - tFalling);
		period = 0;
	}
	
	if (LPC_TIM0->IR&(1<<5))						//CR1 interrupt (CAP0.1) - falling edge
	{
		LPC_TIM0-> IR = (1<<5);					//Reset interrupt on match (MR0)
		tFalling = LPC_TIM0->CR1;
		//period = 0;
		tHigh = (period * cycle_length) + (tFalling - tRising);
		period = 0;
	}
}

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.2 Timer       ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"HighTime:");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"LowTime: ");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);

	GLCD_Simulation();
	Timer_Init (0,cycle_length,1,1,0); // Timer0 , cycleTime of 100us, PCLK of 100MHz -> cplck of 100MHz in Lab, pclk see prev, MR0
	
	LPC_TIM0->MCR |= (1<<0);											//configure to create interupt on match (MR0)
	LPC_TIM0->CCR |= ((1<<0) | (1<<2));				//perform interupt on CAP0.0 rising edge
	LPC_TIM0->CCR |= ((1<<4) | (1<<5));				//perform interupt on CAP0.1 falling edge
	
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_TIM0->IR =(1<<0);
	LPC_TIM0->IR =(1<<5);
	LPC_TIM0->IR =(1<<5);
	NVIC_SetPriority(TIMER0_IRQn, 30);
	
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL3 |= (3<<20);
	LPC_PINCON->PINSEL3 |= (3<<22);
	LPC_GPIO2->FIODIR |= (1UL << 4); //P2.4
	LPC_GPIO2->FIODIR |= (1UL << 5); //P2.5
	LPC_TIM0->TCR = (1<<0);
	
	while(1)
	{
		GLCD_DisplayString(4,10,FONT_16x24,(unsigned char*)lcd_dez(tHigh));
		GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(tLow));
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T54
//================================================================================
#if (T5_4==1)

#define cycle 1000

uint8_t dutyCycleR = 1;
uint8_t dutyCycleG = 1;
uint8_t dutyCycleB = 1;
uint32_t adc_val=0;

void TIMER2_IRQHandler(void){
	if (LPC_TIM2->IR & (1<<0)) 
	{ 
		LPC_TIM2->EMR|=(1<<1); 			//Set MAT2.1
		LPC_GPIO2->FIOPIN^=(1<<5); 	//Toggle P2.5
		LPC_TIM2->IR=(1<<0);				//Reset MR0 -> Timer Cycle
	}
}

void TIMER3_IRQHandler(void)
{
	if (LPC_TIM3->IR&(1<<2))								//MR0 interrupt (MR0)
	{
		LPC_TIM3->EMR|=(1<<1); 			//Set MAT3.1
		LPC_TIM3->EMR|=(1<<0);		 	//Set MAT3.0
		LPC_TIM3->IR=(1<<2);				//Reset MR2 -> Timer Cycle
	}
	

}

int main(void)
{	
	RGB_Init();	
	Switch_Init();
	ADC_Init((1<<4),0);
	
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Lab Microprocessor  ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test 5.4 RGB-PWM");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"Group 11             ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"DCycleRd:");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"DCycleGrn:");
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"DCycleBl:");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);

	GLCD_Simulation();
	Timer_Init (3,cycle,100,1,2); 
	Timer_Init (2,cycle,100,1,0); 
	Timer_Init (3,cycle,100,1,2); 

	// setup LED
	LPC_PINCON->PINSEL0 |= (3 << 22); //RGB1 -> P0.10 -> red auf MAT3.1
	LPC_PINCON->PINSEL9 |= (2 << 26); //RGB2 -> P0.11 -> green auf MAT2.1
	LPC_PINCON->PINSEL0 |= (3 << 20); //RGB0 -> P1.1 -> blue auf MAT3.0
	
	LPC_GPIO2->FIODIR|=(1<<5);
	LPC_GPIO2->FIOCLR=(1<<5);
	
	LPC_TIM3->EMR&=~(3<<6); LPC_TIM3->EMR|=(1<<6); //Clear MAT3.1 if match
	LPC_TIM2->EMR&=~(3<<6); LPC_TIM2->EMR|=(1<<6); //Clear MAT2.1 if match
	LPC_TIM3->EMR&=~(3<<4); LPC_TIM3->EMR|=(1<<4); //Clear MAT3.0 if match
	
	LPC_TIM3->EMR&=~(1<<1); //Reset MAT3.1
	LPC_TIM2->EMR&=~(1<<1); //Reset MAT2.1
	LPC_TIM3->EMR&=~(1<<0); //Reset MAT3.0
	
	LPC_TIM3->MCR|=(1<<6); //Enable Interrupt at MR2 for Cycle Reset
	LPC_TIM2->MCR|=(1<<0); //Enable Interrupt at MR0 for Cycle Reset
	LPC_TIM3->IR=1; //Reset Pending Bits
	LPC_TIM2->IR=1; //Reset Pending Bits
	
	NVIC_ClearPendingIRQ(TIMER3_IRQn);
	NVIC_SetPriority(TIMER3_IRQn,1);
	NVIC_EnableIRQ(TIMER3_IRQn);
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	NVIC_SetPriority(TIMER2_IRQn,2);
	NVIC_EnableIRQ(TIMER2_IRQn);
	
	//SystemCoreClockUpdate();
	
	LPC_TIM2->TCR=(1<<0); // start
	LPC_TIM3->TCR=(1<<0);
	ADC_StartCnv((1<<4),1);

	while(1)
	{
		//ADC_StartCnv((1<<5),0);
		adc_val=ADC_GetValue(4);
		if(Get_SwitchPos() & (1<<7)){	
			dutyCycleR = (ADC_GetValue(4)*100/4095);
			if (dutyCycleR<=1) dutyCycleR=1;
			LPC_TIM3->MR1=(cycle/100)*dutyCycleR;}
		if(Get_SwitchPos() & (1<<6)){
			dutyCycleB = (ADC_GetValue(4)*100/4095);
			if (dutyCycleB<=1) dutyCycleB=1;
			LPC_TIM3->MR0=(cycle/100)*dutyCycleB;}
		if(Get_SwitchPos() & (1<<5)){
			dutyCycleG = (ADC_GetValue(4)*100/4095);
			if (dutyCycleG<=1) dutyCycleG=1;
			LPC_TIM2->MR1=(cycle/100)*dutyCycleG;}
		
		GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(dutyCycleR));
		GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez(dutyCycleG));
		GLCD_DisplayString(7,10,FONT_16x24,(unsigned char*)lcd_dez(dutyCycleB));
		GLCD_Simulation();
		
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  test T5_55
//================================================================================
#if (T5_5==1)

volatile uint8_t increasing = 1;       // Variable, um die Richtung der Frequenzänderung zu verfolgen
volatile uint32_t timer_period = 125000; // Startwert für 400 Hz (100 MHz / (2 * 400 Hz) = 125000)

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & (1 << 0)) {       // Überprüfen, ob Match0-Interrupt ausgelöst wurde
        LPC_TIM0->IR |= (1 << 0);        // Interrupt-Flag zurücksetzen
        
        // Toggle des Pins P1.28 für Rechtecksignal
        LPC_GPIO1->FIOPIN ^= (1 << 28);
        
        // Frequenz erhöhen oder verringern, um ein Auf- und Abschwellen zu erzeugen
        if (increasing) {
            timer_period -= 50;        // Schrittweise Periodenverringerung für Frequenzanstieg
            if (timer_period <= 62500) { // 800 Hz erreicht, Richtung umkehren
                increasing = 0;
            }
        } else {
            timer_period += 50;        // Schrittweise Periodenerhöhung für Frequenzabsenkung
            if (timer_period >= 125000) {// 400 Hz erreicht, Richtung umkehren
                increasing = 1;
            }
        }

        // Aktualisiere Timer-Match-Register für die neue Periodenlänge
        LPC_TIM0->MR0 = timer_period;
    }
}

void Timer0_Init(void) {
    // Timer0 mit 100 MHz und Match-Ausgang konfigurieren
    LPC_SC->PCONP |= (1 << 1);          // Timer0 Power einschalten
    LPC_SC->PCLKSEL0 |= (1 << 2);       // CCLK als Clock-Quelle für Timer0 wählen (100 MHz)
    
    LPC_TIM0->MR0 = timer_period;       // Setze Match-Register auf Startwert 125000 für 400 Hz
    LPC_TIM0->MCR |= (1 << 0) | (1 << 1); // Interrupt und Reset bei Match0
    
    LPC_TIM0->EMR |= (3 << 4);          // Toggle auf MAT0.0/P1.28 bei Match
    
    // Pin P1.28 als MAT0.0 konfigurieren
    LPC_PINCON->PINSEL3 &= ~(3 << 24);  // P1.28 löschen
    LPC_PINCON->PINSEL3 |= (3 << 24);   // P1.28 als MAT0.0 konfigurieren
    
    LPC_TIM0->TCR = 1;                  // Timer0 starten
    NVIC_EnableIRQ(TIMER0_IRQn);        // Timer0-Interrupt im NVIC aktivieren
}

void GPIO_Init(void) {
    // Konfiguriere P1.28 als GPIO-Ausgang, falls erforderlich
    LPC_GPIO1->FIODIR |= (1 << 28);     // P1.28 als Ausgang setzen
}

int main(void) {
    SystemInit();                       // System konfigurieren
    GPIO_Init();                        // GPIO initialisieren
    Timer0_Init();                      // Timer0 initialisieren

    while (1) {

    }
}

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


