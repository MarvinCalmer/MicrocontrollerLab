/******************************************************************************
led.c
******************************************************************************/


//	Autor: 
//	date: 
	       

/********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include "led.h"
#include <LPC17xx.h>

extern void LED_Init(void)
{
	//Power Control GPIO
	 LPC_SC->PCONP |= (1<<15); //setting Bit 15 to 1 for GPIO
	
	//LED0...LED7...LEDRGB  Set GPIO Functionality Sets bit 3 
	LPC_PINCON->PINSEL0 &=~(3<<0);  //LED0 P0.0
	LPC_PINCON->PINSEL0 &=~(3<<4);  //LED1 P0.2
	LPC_PINCON->PINSEL1 &=~(3<<12);  //LED2 P0.22
	LPC_PINCON->PINSEL4 &=~(3<<12);  //LED3 P2.6
	LPC_PINCON->PINSEL4 &=~(3<<14);  //LED4 P2.7
	LPC_PINCON->PINSEL4 &=~(3<<16);  //LED5 P2.8
	LPC_PINCON->PINSEL4 &=~(3<<24);  //LED6 P2.12
	LPC_PINCON->PINSEL4 &=~(3<<26);  //LED7 P2.13
	
	//LED0...LED7...LEDRGB  Set GPIO Direction
	LPC_GPIO0->FIODIR |= (1<<0);
	LPC_GPIO0->FIODIR |= (1<<2);
	LPC_GPIO0->FIODIR |= (1<<22);
	LPC_GPIO2->FIODIR |= (1<<6);
	LPC_GPIO2->FIODIR |= (1<<7);
	LPC_GPIO2->FIODIR |= (1<<8);
	LPC_GPIO2->FIODIR |= (1<<12);
	LPC_GPIO2->FIODIR |= (1<<13);
	
	//Set Input Mode to "PullUP" for all LEDs
	LPC_PINCON->PINMODE0 &=~(3<<0);  //LED0 P0.0
	LPC_PINCON->PINMODE0 &=~(3<<4);  //LED1 P0.2
	LPC_PINCON->PINMODE1 &=~(3<<12);  //LED2 P0.22
	LPC_PINCON->PINMODE4 &=~(3<<12);  //LED3 P2.6
	LPC_PINCON->PINMODE4 &=~(3<<14);  //LED4 P2.7
	LPC_PINCON->PINMODE4 &=~(3<<16);  //LED5 P2.8
	LPC_PINCON->PINMODE4 &=~(3<<24);  //LED6 P2.12
	LPC_PINCON->PINMODE4 &=~(3<<26);  //LED7 P2.13

	//LED0...LED7...LEDRGB  Switch OFF
	LPC_GPIO0->FIOCLR = (1<<0);
	LPC_GPIO0->FIOCLR = (1<<2);
	LPC_GPIO0->FIOCLR = (1<<22);
	LPC_GPIO2->FIOCLR = (1<<6);
	LPC_GPIO2->FIOCLR = (1<<7);
	LPC_GPIO2->FIOCLR = (1<<8);
	LPC_GPIO2->FIOCLR = (1<<12);
	LPC_GPIO2->FIOCLR = (1<<13);
}

extern void LED_On (uint8_t num) {
	switch (num) {
		case 0: LPC_GPIO0->FIOPIN |=(1UL<< 0); break;// or LPC_GPIO0->FIOSET=(1UL<< 0);
		case 1: LPC_GPIO0->FIOPIN |=(1UL<< 2); break;
		case 2: LPC_GPIO0->FIOPIN |=(1UL<< 22); break;
		case 3: LPC_GPIO2->FIOPIN |=(1UL<< 6); break;
		case 4: LPC_GPIO2->FIOPIN |=(1UL<< 7); break;
		case 5: LPC_GPIO2->FIOPIN |=(1UL<< 8); break;
		case 6: LPC_GPIO2->FIOPIN |=(1UL<< 12); break;
		case 7: LPC_GPIO2->FIOPIN |=(1UL<<13); break;
	}
}

void LED_Off (uint8_t num) {
	switch (num) { 
		case 0: LPC_GPIO0->FIOPIN &=~(1UL<< 0);break;//or LPC_GPIO0->FIOCLR=(1UL<< 0);
		case 1: LPC_GPIO0->FIOPIN &=~(1UL<< 2);break;
		case 2: LPC_GPIO0->FIOPIN &=~(1UL<< 22);break;
		case 3: LPC_GPIO2->FIOPIN &=~(1UL<< 6);break;
		case 4: LPC_GPIO2->FIOPIN &=~(1UL<< 7);break;
		case 5: LPC_GPIO2->FIOPIN &=~(1UL<< 8);break;
		case 6: LPC_GPIO2->FIOPIN &=~(1UL<< 12);break;
		case 7: LPC_GPIO2->FIOPIN &=~(1UL<<13); break;
	}
}

extern void LED_Toggle(uint8_t LedNum){
	switch (LedNum) { 
		case 0: LPC_GPIO0->FIOPIN ^= (1 << 0);break;
		case 1: LPC_GPIO0->FIOPIN ^= (1 << 2);break;
		case 2: LPC_GPIO0->FIOPIN ^= (1 << 22);break;
		case 3: LPC_GPIO0->FIOPIN ^= (1 << 6);break;
		case 4: LPC_GPIO0->FIOPIN ^= (1 << 7);break;
		case 5: LPC_GPIO0->FIOPIN ^= (1 << 8);break;
		case 6: LPC_GPIO0->FIOPIN ^= (1 << 12);break;
		case 7: LPC_GPIO0->FIOPIN ^= (1 << 13);break;
	}
}

extern void LED_Out(unsigned char value) {
	int i;
	for (i = 0; i < 8; i++) { 
		if (value & (1<<i)) {
			LED_On (i);
		}
		else {LED_Off(i);}
	}
}

extern void RGB_On(uint8_t num){
	switch (num) {
		case 0: LPC_GPIO0->FIOSET =(1<<10); break;// RGB Blue is ON (P0.10) 
		case 2: LPC_GPIO4->FIOSET =(1<<29); break;
		case 1: LPC_GPIO0->FIOSET =(1<<11); break;
	}
}

extern void RGB_Off(uint8_t num){
	switch (num) {
		case 0: LPC_GPIO0->FIOCLR =(1<<10); break;// RGB Blue is Off (P0.10) 
		case 2: LPC_GPIO4->FIOCLR =(1<<29);	break;
		case 1: LPC_GPIO1->FIOCLR =(1<<11);	break;
	}
}


extern void RGB_Init(void){
	
	//Power Control GPIO
	 LPC_SC->PCONP |= (1<<15); 
	
	//LEDRGB  Set GPIO Functionality Sets bit 3 
	LPC_PINCON->PINSEL0 &=~(3<<20);  //RGB Blau P0.10
	LPC_PINCON->PINSEL0 &=~(3<<22);  //RGB Rot P0.11
	LPC_PINCON->PINSEL9 &=~(3<<26);  //RGB Gruen P4.29

	LPC_GPIO0->FIODIR |=(1<<10); 
	LPC_GPIO0->FIODIR |=(1<<11);
	LPC_GPIO4->FIODIR |=(1<<29);
	
	//LEDRGB  Switch OFF
	LPC_GPIO0->FIOCLR = (1<<10);
	LPC_GPIO0->FIOCLR = (1<<11);
	LPC_GPIO4->FIOCLR = (1<<29);
}

extern void RGB_Out(unsigned char value) {
    // Handle the Blue component (bit 0)
    if (value & 0x01) {
        RGB_On(0);  // Turn on Blue
    } else {
        RGB_Off(0); // Turn off Blue
    }

    // Handle the Red component (bit 1)
    if (value & 0x02) {
        RGB_On(2);  // Turn on Red
    } else {
        RGB_Off(2); // Turn off Red
    }

    // Handle the Green component (bit 2)
    if (value & 0x04) {
        RGB_On(1);  // Turn on Green
    } else {
        RGB_Off(1); // Turn off Green
    }
}

