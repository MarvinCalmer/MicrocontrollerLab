#include "keys.h"
#include <LPC17xx.h>

extern void Switch_Init(){
	//switch on GPIO-Power
	LPC_SC->PCONP |= (1 << 15);
	
	//PinConnect Block GPIO-Function (PINSELx-Reg. (Reset-Value))
	LPC_PINCON->PINSEL3 &= ~(3 << 4); //P1.18
	LPC_PINCON->PINSEL3 &= ~(3 << 6); //P1.19
	LPC_PINCON->PINSEL3 &= ~(3 << 8); //P1.20
	LPC_PINCON->PINSEL3 &= ~(3 << 10); //P1.21
	LPC_PINCON->PINSEL3 &= ~(3 << 12); //P1.22
	LPC_PINCON->PINSEL3 &= ~(3 << 14); //P1.23
	LPC_PINCON->PINSEL3 &= ~(3 << 16); //P1.24
	LPC_PINCON->PINSEL3 &= ~(3 << 18); //P1.25
	
	//Selection neither PullUp nor pull down */
	LPC_PINCON->PINMODE3 &= ~( 3 << 4);LPC_PINCON->PINMODE3 |= ( 2 << 4); //P1.18
	LPC_PINCON->PINMODE3 &= ~( 3 << 6);LPC_PINCON->PINMODE3 |= ( 2 << 6); //P1.19
	LPC_PINCON->PINMODE3 &= ~( 3 << 8);LPC_PINCON->PINMODE3 |= ( 2 << 8); //P1.20
	LPC_PINCON->PINMODE3 &= ~( 3 << 10);LPC_PINCON->PINMODE3 |= ( 2 << 10); //P1.21
	LPC_PINCON->PINMODE3 &= ~( 3 << 12);LPC_PINCON->PINMODE3 |= ( 2 << 12); //P1.22
	LPC_PINCON->PINMODE3 &= ~( 3 << 14);LPC_PINCON->PINMODE3 |= ( 2 << 14); //P1.23
	LPC_PINCON->PINMODE3 &= ~( 3 << 16);LPC_PINCON->PINMODE3 |= ( 2 << 16); //P1.24
	LPC_PINCON->PINMODE3 &= ~( 3 << 18);LPC_PINCON->PINMODE3 |= ( 2 << 18); //P1.25
	
	LPC_GPIO1->FIODIR &= ~(1<<18);
	LPC_GPIO1->FIODIR &= ~(1<<19);
	LPC_GPIO1->FIODIR &= ~(1<<20);
	LPC_GPIO1->FIODIR &= ~(1<<21);
	LPC_GPIO1->FIODIR &= ~(1<<22);
	LPC_GPIO1->FIODIR &= ~(1<<23);
	LPC_GPIO1->FIODIR &= ~(1<<24);
	LPC_GPIO1->FIODIR &= ~(1<<25);
}

extern uint8_t Get_SwitchPos(void){
	//return state of ports S7:S0 (P1.25:P1.18) : The result is a single byte, where each bit represents the state of one switch
	// P1.18 LSB ... P1.25 MSB
	uint8_t pos;

	pos |= (LPC_GPIO1->FIOPIN & (1 << 18)) ? (1 << 0) : 0;  // S0 -> P1.18
	pos |= (LPC_GPIO1->FIOPIN & (1 << 19)) ? (1 << 1) : 0;  // S1 -> P1.19
	pos |= (LPC_GPIO1->FIOPIN & (1 << 20)) ? (1 << 2) : 0;  // S2 -> P1.20
	pos |= (LPC_GPIO1->FIOPIN & (1 << 21)) ? (1 << 3) : 0;  // S3 -> P1.21
	pos |= (LPC_GPIO1->FIOPIN & (1 << 22)) ? (1 << 4) : 0;  // S4 -> P1.22
	pos |= (LPC_GPIO1->FIOPIN & (1 << 23)) ? (1 << 5) : 0;  // S5 -> P1.23
	pos |= (LPC_GPIO1->FIOPIN & (1 << 24)) ? (1 << 6) : 0;  // S6 -> P1.24
	pos |= (LPC_GPIO1->FIOPIN & (1 << 25)) ? (1 << 7) : 0;  // S7 -> P1.25
	
	return pos;	
} 

extern void Button_Init(void){
	//switch on GPIO-Power
	LPC_SC->PCONP |= (1 << 15);
	
	//PinConnect Block GPIO-Function (PINSELx-Reg. (Reset-Value))
	LPC_PINCON->PINSEL3 &= ~(3 << 20); 
	LPC_PINCON->PINSEL3 &= ~(3 << 22); 
	LPC_PINCON->PINSEL4 &= ~(3 << 22); 
	
	//Selection neither PullUp nor pull down */
	LPC_PINCON->PINMODE3 &= ~( 3 << 20);LPC_PINCON->PINMODE3 |= ( 2 << 20); 
	LPC_PINCON->PINMODE3 &= ~( 3 << 22);LPC_PINCON->PINMODE3 |= ( 2 << 22); 
	LPC_PINCON->PINMODE4 &= ~( 3 << 22);LPC_PINCON->PINMODE4 |= ( 2 << 22); 
	
	LPC_GPIO1->FIODIR &= ~(1<<26);
	LPC_GPIO1->FIODIR &= ~(1<<27);
	LPC_GPIO2->FIODIR &= ~(1<<11);
}

extern unsigned int Get_TA10Stat(void){
	return (LPC_GPIO1->FIOPIN & (1 << 26)) ? 1 : 0;
}

extern unsigned int Get_TA11Stat(void){
	return (LPC_GPIO1->FIOPIN & (1 << 27)) ? 1 : 0;
}

extern unsigned int Get_TA12Stat(void){
	return (LPC_GPIO2->FIOPIN & (1 << 11)) ? 1 : 0;
}