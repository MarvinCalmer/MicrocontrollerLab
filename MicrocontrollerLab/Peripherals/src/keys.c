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

extern void Joystick_Init(void)
{
	//GPIO Power Control
	LPC_SC->PCONP |=(1<<15);
	
	//Pin Function Selection P0.28 P0.3 P0.21 P0.25
	LPC_PINCON->PINSEL1 &=~(3<<22); // P0.27
	LPC_PINCON->PINSEL1 &=~(3<<24); // P0.28
	LPC_PINCON->PINSEL0 &=~(3<<6); // P0.3Stat()
	LPC_PINCON->PINSEL1 &=~(3<<10); // P0.21
	LPC_PINCON->PINSEL1 &=~(3<<18); // P0.25
	
	//Direction Set
	LPC_GPIO0->FIODIR &=~(1<<27);
	LPC_GPIO0->FIODIR &=~(1<<28);
	LPC_GPIO0->FIODIR &=~(1<<3);
	LPC_GPIO0->FIODIR &=~(1<<21);
	LPC_GPIO0->FIODIR &=~(1<<25);
	
	//PinMode Select
	LPC_PINCON->PINMODE1 &=~(3<<22); //Functionality 0, 2Bits selected
	LPC_PINCON->PINMODE1 |=(2<<22); //Functionality Set: 10: No Pullup/Pulldown.
	LPC_PINCON->PINMODE1 &=~(3<<24); //Functionality 0, 2Bits selected
	LPC_PINCON->PINMODE1 |=(2<<24); //Functionality Set: 10: No Pullup/Pulldown.
  LPC_PINCON->PINMODE0 &=~(3<<6); //Functionality 0, 2Bits selected
	LPC_PINCON->PINMODE0 |=(2<<6); //Functionality Set: 10: No Pullup/Pulldown.
  LPC_PINCON->PINMODE1 &=~(3<<10); //Functionality 0, 2Bits selected
	LPC_PINCON->PINMODE1 |=(2<<10); //Functionality Set: 10: No Pullup/Pulldown.
  LPC_PINCON->PINMODE1 &=~(3<<18); //Functionality 0, 2Bits selected
	LPC_PINCON->PINMODE1 |=(2<<18); //Functionality Set: 10: No Pullup/Pulldown.
}
// Function to get the status of the left direction (P0.27)
extern unsigned int Get_LeftStat(void) {
    // Read the state of the P0.27 pin
    return !(LPC_GPIO0->FIOPIN & (1 << 25)) ? 0 : 1;
}

// Function to get the status of the right direction (P0.28)
extern unsigned int Get_RightStat(void) {
    // Read the state of the P0.28 pin
    return !(LPC_GPIO0->FIOPIN & (1 << 28)) ? 0 : 1;
}

// Function to get the status of the up direction (P0.3)
extern unsigned int Get_UpStat(void) {
    // Read the state of the P0.3 pin
    return !(LPC_GPIO0->FIOPIN & (1 << 21)) ? 0 : 1;
}

// Function to get the status of the down direction (P0.21)
extern unsigned int Get_DownStat(void) {
    // Read the state of the P0.21 pin
    return !(LPC_GPIO0->FIOPIN & (1 << 27)) ? 0 : 1;
}

// Function to get the status of the center button (P0.25)
extern unsigned int Get_CenterStat(void) {
    // Read the state of the P0.25 pin
    return !(LPC_GPIO0->FIOPIN & (1 << 3)) ? 0 : 1;
}

extern void Matrix_Init(void){
	//switch on GPIO-Power
	LPC_SC->PCONP |= (1 << 15);
	
	//PinConnect Block GPIO-Function (PINSELx-Reg. (Reset-Value))
	LPC_PINCON->PINSEL4&=~(3<<6);//P2.3
	LPC_PINCON->PINSEL4&=~(3<<8);//P2.4
	LPC_PINCON->PINSEL4&=~(3<<10);//P2.5
	LPC_PINCON->PINSEL0&=~(3<<8);//P0.4
	LPC_PINCON->PINSEL0&=~(3<<10);//P0.5
	LPC_PINCON->PINSEL7&=~(3<<20);//P3.26
	
	//Selection neither PullUp nor pull down */
	LPC_PINCON->PINMODE4 &= ~( 3 << 6);LPC_PINCON->PINMODE4 |= ( 2 << 6); //P2.3
	LPC_PINCON->PINMODE4 &= ~( 3 << 8);LPC_PINCON->PINMODE4 |= ( 2 << 8); //P2.4
	LPC_PINCON->PINMODE4 &= ~( 3 << 10);LPC_PINCON->PINMODE4 |= ( 2 << 10); //P2.5
	LPC_PINCON->PINMODE0 &= ~( 3 << 8);LPC_PINCON->PINMODE0 |= ( 2 << 8); //P0.4
	LPC_PINCON->PINMODE0 &= ~( 3 << 10);LPC_PINCON->PINMODE0 |= ( 2 << 10); //P0.5
	LPC_PINCON->PINMODE7 &= ~( 3 << 20);LPC_PINCON->PINMODE7 |= ( 2 << 20); //P3.26
	
	LPC_GPIO2->FIODIR &= ~(1<<3);
	LPC_GPIO2->FIODIR &= ~(1<<4);
	LPC_GPIO2->FIODIR &= ~(1<<5);
	LPC_GPIO0->FIODIR &= ~(1<<4);
	LPC_GPIO0->FIODIR &= ~(1<<5);
	LPC_GPIO3->FIODIR &= ~(1<<26);
}

extern unsigned char Get_Mkey(void){
	
	 for (int row = 0; row < 3; row++) {
        // Set all rows to 0
        LPC_GPIO2->FIOCLR = (1 << 3); // Clear P2.3 (Row 1)
        LPC_GPIO2->FIOCLR = (1 << 4); // Clear P2.4 (Row 2)
        LPC_GPIO2->FIOCLR = (1 << 5); // Clear P2.5 (Row 3)

		unsigned char key = 
				(LPC_GPIO0->FIOPIN & (1 << 4)) ? (row == 0 ? '1' : (row == 1 ? '4' : '7')) :
				(LPC_GPIO0->FIOPIN & (1 << 5)) ? (row == 0 ? '2' : (row == 1 ? '5' : '8')) :
				(LPC_GPIO3->FIOPIN & (1 << 26)) ? (row == 0 ? '3' : (row == 1 ? '6' : '9')) : 0x20;
				
	
		return key;
		}
	 return 0x20;
}