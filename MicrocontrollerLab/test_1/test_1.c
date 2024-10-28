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
#include <stdlib.h>


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
//	LPC_PINCON->PINMODE0 |= (2 << 6); //P0.3
//	LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21
//	LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25
//	LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27
//	LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
//	//init buttons TA10..12
//	LPC_PINCON->PINMODE3 |= (2 << 20);//P1.26
//	LPC_PINCON->PINMODE3 |= (2 << 22);//P1.27
//	LPC_PINCON->PINMODE4 |= (2 << 22);//P2.11

	//init_matrix
	LPC_GPIO2->FIODIR |=(1UL<<3);//P0.3
	LPC_GPIO2->FIODIR |=(1UL<<4);//P0.4
	LPC_GPIO2->FIODIR |=(1UL<<5);//P0.5
	LPC_PINCON->PINMODE0 |= (2 << 8);//P0.4
	LPC_PINCON->PINMODE0 |= (2 << 10);//P0.5
	LPC_PINCON->PINMODE7 |= (2 << 20);//P3.26



		GLCD_Init();
		LED_Init();
		RGB_Init();
		Switch_Init();
		Button_Init();
		Joystick_Init();
		GLCD_Simulation();

	while(1)
	{
//		uint8_t test=Get_SwitchPos();
//		int push= Get_TA12Stat();
//		GLCD_Simulation();
//		if(test){
//			RGB_On(1);
//			GLCD_Simulation();
//		}
//		else{
//			RGB_Off(1);
//			GLCD_Simulation();
//		}
		
//			for (unsigned char value = 0; value < 8; value++) {
//					GLCD_Simulation();
//					RGB_Out(value);    // Output the corresponding RGB combination
//					delayXms(10);  
//					GLCD_Simulation();       // Wait for 1 second before the next combination
//			}
		GLCD_Simulation();
		if (Get_LeftStat()) {
			GLCD_Simulation();
            LED_On(1);
			GLCD_Simulation();
        }
        if (Get_RightStat()) {
            // Joystick moved right
        }
        if (Get_UpStat()) {
            // Joystick moved up
        }
        if (Get_DownStat()) {
            // Joystick moved down
        }
        if (Get_CenterStat()) {
            // Joystick center button pressed
		} }
}	

#endif



//================================================================================
//  Main-Function Test T1_3 Task 1.6 
//================================================================================
#if (T1_3 == 1)

int main(void)
{	
	GLCD_Init();
	Button_Init();
	Switch_Init();
	LED_Init();
	
	uint8_t test= 0;
	
	GLCD_Simulation();
	while(1)
	{
		GLCD_Simulation();
		test=Get_SwitchPos();
		LED_Out(test);
		GLCD_Simulation();
		
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function TestT1_4 Task 1.7
//================================================================================
#if (T1_4 == 1)

int main(void)
{	
	GLCD_Init();
	Button_Init();
	Switch_Init();
	LED_Init();
	RGB_Init();
	
	GLCD_Simulation();
	uint8_t state=0 ;

	while(1)
	{		
		GLCD_Simulation();
		
		if (Get_TA11Stat()&&(state & (1 << 0))==0) {
				state |= (1 << 0);  // Setzt das 3. Bit des state-Bytes (Bit-Position 2)
		} else if((Get_TA11Stat()&&(state & (1 << 0))==1 )) {
				state &= ~(1 << 0); // Löscht das 3. Bit des state-Bytes, wenn TA10 nicht gedrückt
		}
		if (Get_TA12Stat()&&(state & (1 << 1))==0) {
				state |= (1 <<  1);  // Setzt das 3. Bit des state-Bytes (Bit-Position 2)
		} 
		else if((Get_TA12Stat()&&(state & (1 << 1))==2 )) {
				state &= ~(1 << 1); // Löscht das 3. Bit des state-Bytes, wenn TA10 nicht gedrückt
		}
		if (Get_TA10Stat()&&(state & (1 << 2))==0) {
				state |= (1 << 2);  // Setzt das 3. Bit des state-Bytes (Bit-Position 2)
		} else if((Get_TA10Stat()&&(state & (1 << 2))==4 )) {
				state &= ~(1 << 2); // Löscht das 3. Bit des state-Bytes, wenn TA10 nicht gedrückt
		}
		RGB_Out(state);
		GLCD_Simulation();
		
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  Main-Function Test T1_5 Task 1.8
//================================================================================
#if (T1_5 == 1)

void Check_Joystick(void) {
	int state=0;
	
    if (Get_LeftStat()) {
        LED_On(6);  // Turn on LED6 for left direction
    } else {
        LED_Off(6); // Turn off LED6
    }

    if (Get_RightStat()) {
        LED_On(2);  // Turn on LED2 for right direction
    } else {
        LED_Off(2); // Turn off LED2
    }

    if (Get_UpStat()) {
        LED_On(0);  // Turn on LED0 for up direction
    } else {
        LED_Off(0); // Turn off LED0
    }

    if (Get_DownStat()) {
        LED_On(4);  // Turn on LED4 for down direction
    } else {
        LED_Off(4); // Turn off LED4
    }

		if (Get_CenterStat()) {
			state=rand()%4;
      RGB_On(state) ;
			delayXms(1000);
			RGB_Off(state);
    } else {
        //RGB_Off(state); // Turn off LED4
    }

}

int main(void)
{	
	GLCD_Init();
	Button_Init();
	Switch_Init();
	LED_Init();
	RGB_Init();
	Joystick_Init();
	GLCD_Simulation();
	//int state=0;
	
	while(1)
	{
		//state=rand()%4;
		Check_Joystick();
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Function Test T1_6 Task 1.9 & 1.10
//================================================================================
#if (T1_6 == 1)

void rolchar(uint8_t* value, uint8_t dir) {
    if (dir == 1) { // Rotate left
        // Store the leftmost bit (Bit 7)
        uint8_t leftmost_bit = (*value >> 7) & 0x01;
        // Shift left and wrap the leftmost bit to the rightmost position
        *value = (*value << 1) | leftmost_bit;
    } else { // Rotate right
        // Store the rightmost bit (Bit 0)
        uint8_t rightmost_bit = *value & 0x01;
        // Shift right and wrap the rightmost bit to the leftmost position
        *value = (*value >> 1) | (rightmost_bit << 7);
    }
}


int main(void)
{	
	GLCD_Init();
	Button_Init();
	Switch_Init();
	LED_Init();
	RGB_Init();
	Joystick_Init();
	GLCD_Simulation();
	
	#define minimum 100
	#define maximum 300
	#define increment 10
	
	uint8_t value = 0x81;
	uint8_t direction=1;
	uint16_t delay=100;
	
	while(1)
	{
		if( Get_CenterStat()){
			value = Get_SwitchPos();	
		}		
		if (Get_LeftStat()) {
			direction=0;
    } 
    if (Get_RightStat()) {
			direction=1;
    } 
		if (Get_UpStat() && delay>minimum) {
			delay=delay-increment;
    }
    if (Get_DownStat() && delay<maximum) {
			delay=delay+increment;
    }
		if (delay == minimum) {
				RGB_Off(0); 
				RGB_On(1);  
				RGB_Off(2); 
		} else if (delay == maximum) {
				RGB_Off(1); 
				RGB_On(2);  
				RGB_Off(0); 
		} else {
				RGB_Off(1); 
				RGB_On(0);  
				RGB_Off(2); 
		}
		
		rolchar(&value, direction);
		LED_Out(value);
		
		GLCD_Simulation();
		delayXms(delay);
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Funktion Test T1_7 Test 1.11
//================================================================================
#if (T1_7 == 1)


void rolchar(uint8_t* value, uint8_t dir) {
    if (dir == 1) { // Rotate left
        // Store the leftmost bit (Bit 7)
        uint8_t leftmost_bit = (*value >> 7) & 0x01;
        // Shift left and wrap the leftmost bit to the rightmost position
        *value = (*value << 1) | leftmost_bit;
    } else { // Rotate right
        // Store the rightmost bit (Bit 0)
        uint8_t rightmost_bit = *value & 0x01;
        // Shift right and wrap the rightmost bit to the leftmost position
        *value = (*value >> 1) | (rightmost_bit << 7);
    }
}

int main(void)
{	
	#define minimum 100000
	#define maximum 1000000
	
	uint8_t dir=0, value;
	uint32_t DELAY_LED=500000, DELAY_JOYSTICK=10000;
	uint32_t delay_led=0, delay_joystick=0;
	//include the necessary init code here
	GLCD_Init();
	Button_Init();
	Switch_Init();
	LED_Init();
	RGB_Init();
	Joystick_Init();
	GLCD_Simulation();
	//
	LPC_GPIO2->FIODIR|=(1UL<<0)|(1UL<<1);
	
	while(1)
	{
		if (delay_joystick>DELAY_JOYSTICK) {
		 delay_joystick =0;
		 LPC_GPIO2->FIOPIN ^=(1UL<<1); //Toggle, output P2.1 (PWM2.2) to the
		 //logic analyzer/ oscilloscop
		 if (Get_RightStat()) dir=1;
		 if (Get_LeftStat()) dir=0;
		 if(Get_CenterStat())value=Get_SwitchPos();
		 if (Get_UpStat() && DELAY_LED>=minimum	&& DELAY_LED<=maximum) {
			DELAY_LED -=10000;
			}
			if (Get_DownStat() && DELAY_LED<=maximum && DELAY_LED>=minimum) {
				DELAY_LED+=10000;
			}
		}
		
		
		delay_led++; delay_joystick++;
	 if (delay_led>DELAY_LED) {
 		 delay_led=0;
		 LPC_GPIO2->FIOPIN ^=(1UL<<0); //Toggle, output P2.0 (PWM2.1) to the
		 // logic analyzer/ oscilloscop
		 rolchar (&value,dir);
		 LED_Out(value);
		 if (DELAY_LED == minimum) {
				RGB_Off(0); 
				RGB_On(1);  
				RGB_Off(2); 
		} else if (DELAY_LED == maximum) {
				RGB_Off(1); 
				RGB_On(2);  
				RGB_Off(0); 
		} else {
				RGB_Off(1); 
				RGB_On(0);  
				RGB_Off(2); 
		}
		
	 }

	 
	 GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

