/******************************************************************************

test_3.c

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
#include "prio.h"
#include "lcd.h"
#include "keys.h"


//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//================================================================================
//  Test T3_1 Task 3.1
//================================================================================
#if (T3_1 == 1)

void SysTick_Handler (void) {
	//GLCD_Simulation();
	static unsigned long ticks=0;
	ticks++;
	
	if(ticks<5)
		LED_On(0);
	else if(ticks<20)
		LED_Off(0);
	else if(ticks<25)
		LED_On(0);
	else if(ticks<100)
		LED_Off(0);
	else
		ticks=0;	
}

int main(void)
{	
	SysTick_Config(SystemCoreClock/100);
	SystemCoreClockUpdate();
	
	GLCD_Init();
	LED_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(DarkGreen);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test2.3 Matrix");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group 11 ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"LED0 Flashes ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"50ms on, 150 ms off,");
  GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"50ms on, 750 ms off");
	GLCD_Simulation();
	
	while(1)
	{
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Main-Funktion Versuchsteil T3_2 Test 3.2
//================================================================================
#if (T3_2 == 1)

uint16_t count_TA12_int;

void EINT1_IRQ_Init(){
	// power 
	LPC_SC->PCONP |= (1<<15);
	//set 22 and 23 to 01
	LPC_PINCON->PINSEL4 |= (1<<22); 
	LPC_PINCON->PINSEL4 &= ~(1<<23); 
	//no Pullup/Pulldown resistor
	LPC_PINCON->PINMODE4 &=~(3 << 22);
	LPC_PINCON->PINMODE4 |= (2 << 22);
	// Set edge sensitivity in the EXTMODE register 
	LPC_SC->EXTMODE |= (1<<1);
	//Set rising edge in the EXTPOLAR register.
	LPC_SC->EXTPOLAR |=(1<<1);// 1:rising edge 0:falling edge
	//Clear the interrupt pending bit in the EXTTINT Register and in NVIC
	LPC_SC->EXTINT |=(1<<1);   // delete interrupt requests
	NVIC_ClearPendingIRQ(EINT1_IRQn);
	//Set Prio
	NVIC_SetPriority (EINT1_IRQn,PRIO_EINT1_IRQN);
	//Enable EINT1 NVIC interrupt
	NVIC_EnableIRQ(EINT1_IRQn);
	count_TA12_int=0;
}

void EINT1_IRQHandler(){
	LPC_SC->EXTINT = (1<<1);

	count_TA12_int++;
}

int main(void)
{	
	EINT1_IRQ_Init();
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test3.2 Button Count");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group 11 ");
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"TA12 count=");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);

	while(1)
	{
		GLCD_DisplayString(4,15,FONT_16x24,(unsigned char*)lcd_dez(count_TA12_int));
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Main-Funktion Versuchsteil T3_3 Task 3.3
//================================================================================
#if (T3_3 == 1)

uint16_t 	count_GPIOINT_left_Int, 
					count_GPIOINT_right_Int, 
					count_GPIOINT_up_Int, 
					count_GPIOINT_down_Int;

void EINT3_IRQHandler(){
	// Clear interrupt
	LPC_SC->EXTINT = (1<<3);
	//check IO0IntEnR for inputs
	if(LPC_GPIOINT->IntStatus&(1<<0)) //Interrupt Port 0
	{
		//Joystick-UP
		if(LPC_GPIOINT->IO0IntStatR&(1<<21)) 
		{	
			count_GPIOINT_up_Int++;
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<21);} 
		
		//Joystick-Down
		if(LPC_GPIOINT->IO0IntStatR&(1<<27)) 
		{	
			count_GPIOINT_down_Int++; 
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<27);} 
		
		//Joystick-left
		if(LPC_GPIOINT->IO0IntStatR&(1<<25)) 
		{	
			count_GPIOINT_left_Int++;
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<25);} 
		
		//Joystick-right
		if(LPC_GPIOINT->IO0IntStatR&(1<<28)) 
		{	
			count_GPIOINT_right_Int++; 
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<28);} 
		
		//Joystick-Center
		if(LPC_GPIOINT->IO0IntStatR&(1UL<<3)) 
		{	
			//Reset all counter values
			count_GPIOINT_up_Int=0;
			count_GPIOINT_down_Int=0; 
			count_GPIOINT_right_Int=0;
			count_GPIOINT_left_Int=0; 
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1UL<<3);} 
	}
}

int main(void)
{		
	JoyStick_IRQ_Init();
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test3.3 Joystick Count");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group 11 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"up:");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"down:");
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"left:");
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"right:");

	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_Simulation();
	
	while(1)
	{
		GLCD_DisplayString(5,8,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_up_Int));
		GLCD_DisplayString(6,8,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_down_Int));
		GLCD_DisplayString(7,8,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_left_Int));
		GLCD_DisplayString(8,8,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_right_Int));
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Main-Funktion Versuchsteil T3_4 running light
//================================================================================
#if (T3_4 == 1)

uint8_t 	direction, pattern=0, delay=5;
#define min_delay 1
#define max_delay 10

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

void SysTick_Handler (void) {
	static unsigned long ticks=0;
	ticks++;
	
	if(ticks==delay){
		rolchar(&pattern,direction);
		LED_Out(pattern);

		
		if(ticks<=min_delay){
				RGB_Off(0); 
				RGB_On(1);  
				RGB_Off(2);
		}
		else if(ticks>=max_delay){
				RGB_Off(1); 
				RGB_On(2);  
				RGB_Off(0);
		}
		else {
				RGB_Off(1); 
				RGB_On(0);  
				RGB_Off(2); 
		}			
	}
	else if (ticks>delay)
		ticks=0;
}

void EINT3_IRQHandler(){
	// Clear interrupt
	LPC_SC->EXTINT = (1<<3);
	//check IO0IntEnR for inputs
	if(LPC_GPIOINT->IntStatus&(1<<0)) //Interrupt Port 0
	{
		//Joystick-UP
		if(LPC_GPIOINT->IO0IntStatR&(1<<21)) 
		{	
			delay--;
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<21);} 
		
		//Joystick-Down
		if(LPC_GPIOINT->IO0IntStatR&(1<<27)) 
		{	
			delay++; 
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<27);} 
		
		//Joystick-left
		if(LPC_GPIOINT->IO0IntStatR&(1<<25)) 
		{	
			direction=0;
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<25);} 
		
		//Joystick-right
		if(LPC_GPIOINT->IO0IntStatR&(1<<28)) 
		{	
			direction=1;
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<28);} 
		
		//Joystick-Center
		if(LPC_GPIOINT->IO0IntStatR&(1UL<<3)) 
		{	
			//Reset all counter values
			pattern=Get_SwitchPos();
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1UL<<3);} 
	}
}

int main(void)
{	
	JoyStick_IRQ_Init();
	SysTick_Config(SystemCoreClock/1000);
	SystemCoreClockUpdate();
	
	Switch_Init();
	RGB_Init();
	LED_Init();
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test3.3 running light");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group 11 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"running light");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"delay(ms):");
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"direction:");
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"pattern:");
	GLCD_Simulation();
	
	while(1)
	{
		GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez(delay*10));
		if(direction)
			GLCD_DisplayString(7,10,FONT_16x24,(unsigned char*)"right");
		else
			GLCD_DisplayString(7,10,FONT_16x24,(unsigned char*)"left");
		GLCD_DisplayString(8,10,FONT_16x24,(unsigned char*)lcd_hex(pattern));
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T3_5 encoder
//================================================================================
#if (T3_5 == 1)
#define Encoder_Max 5
#define Encoder_Min 1

uint8_t count_encoder= Encoder_Min;

void EINT0_IRQHandler(){
	LPC_SC->EXTINT = (1<<0);
	count_encoder=Encoder_Min;
}
void EINT3_IRQHandler(){
	if(LPC_GPIOINT->IntStatus&(1<<0)) //Interrupt Port 0
	{
		if(LPC_GPIOINT->IO0IntStatR&(1<<23)) //Ceck Encoder A -> look at B
		{	
			if((LPC_GPIO0->FIOPIN&(1<<24)) && (count_encoder>Encoder_Min)) // Encoder B Set
			{	
				// COunter Clockwise (CCW)
				count_encoder--;
			}
			else if (!((LPC_GPIO0->FIOPIN&(1<<24))) && (count_encoder<Encoder_Max)){
			//Clockwise (CCW)
			count_encoder++;
			
			//reset IRQ
			
			}
			LPC_GPIOINT->IO0IntClr=(1<<23);
		} 
		
	}
	LPC_SC->EXTINT = (1<<3);
}

int main(void)
{	
	Encoder_Init();
	RGB_Init();
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test3.5 Encoder");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group 11 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Counter:");
	GLCD_Simulation();
	while(1)
	{
			if(count_encoder==1){
				GLCD_SetTextColor(Black);
				RGB_Out(00000010);
				GLCD_Simulation();
			}
			
			else 
				GLCD_SetTextColor(LightGrey);
			GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Red light:");
			
			if(count_encoder==2){
				GLCD_SetTextColor(Black);
				RGB_Out(00000100);
				GLCD_Simulation();
			}
			else 
				GLCD_SetTextColor(LightGrey);
			GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Green light:");
						
			if(count_encoder==3){
				GLCD_SetTextColor(Black);
				RGB_Out(00000001);
				GLCD_Simulation();
			}
			else 
				GLCD_SetTextColor(LightGrey);
			GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Blue light:");
						
			if(count_encoder==4){
				GLCD_SetTextColor(Black);
				RGB_Out(00000001);
				GLCD_Simulation();
			}
			else 
				GLCD_SetTextColor(LightGrey);
			GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Orange light:");
						
			if(count_encoder==5){
				GLCD_SetTextColor(Black);
				RGB_Out(00000101);
				GLCD_Simulation();
			}
			else 
				GLCD_SetTextColor(LightGrey);
			GLCD_DisplayString(10,0,FONT_16x24,(unsigned char*)"No light:");
			RGB_Out(00000000);
			GLCD_Simulation();
			
			GLCD_SetTextColor(Black);
			GLCD_DisplayString(5,10,FONT_16x24,(unsigned char*)lcd_dez(count_encoder));
			GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T3_6 Time of day
//================================================================================
#if (T3_6 == 1)

uint32_t time_sec, time_min, time_h;
uint32_t set_time_sec, set_time_min, set_time_h;
uint16_t digit_pos=0, set_Time=0;


char*lcd_time(uint8_t time_h,uint8_t time_min,uint8_t time_sec)
{
	static char text_string[9];
	unsigned char asc[]= "0123456789";;
	text_string[0]=asc[(time_h/10)]; //10 hours
	text_string[1]=asc[(time_h%10)]; //  1 hours
	text_string[2]=':'; 							// :
	text_string[3]=asc[(time_min/10)]; //10 minutes
	text_string[4]=asc[(time_min%10)]; //1 minutes
	text_string[5]=':';              	 // :
	text_string[6]=asc[(time_sec/10)]; //10 seconds
	text_string[7]=asc[(time_sec%10)]; //  1 seconds
	return (text_string);
}

void SysTick_Handler(void)
{
	time_sec++;
}

void EINT3_IRQHandler(){
	// Clear interrupt
	LPC_SC->EXTINT = (1<<3);
	//check IO0IntEnR for inputs
	if(LPC_GPIOINT->IntStatus&(1<<0)) //Interrupt Port 0
	{
		//Joystick-UP
		if(LPC_GPIOINT->IO0IntStatR&(1<<21)) 
		{	
			// First check for position set by center
			if(set_Time){
				//set first Digit
				if(digit_pos==0 && set_time_h<14){
					set_time_h+=10;
				}
				//Set second Digit
				if(digit_pos==1 && set_time_h<23){
					set_time_h+=1;
				}
				//set third Digit
				if(digit_pos==2 && set_time_min<50){
					set_time_min+=10;
				}
				//Set fourth Digit
				if(digit_pos==3 && set_time_min<59){
					set_time_min+=1;
				}				
				//set third Digit
				if(digit_pos==4 && set_time_sec<50){
					set_time_sec+=10;
				}
				//Set fourth Digit
				if(digit_pos==5 && set_time_sec<59){
					set_time_sec+=1;
				}
				
			}
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<21);} 
		
		//Joystick-Down
		if(LPC_GPIOINT->IO0IntStatR&(1<<27)) 
		{	
			if(set_Time){
				//set first Digit
				if(digit_pos==0 && set_time_h>=10){
					set_time_h-=10;
				}
				//Set second Digit
				if(digit_pos==1 && set_time_h>0){
					set_time_h-=1;
				}
				//set third Digit
				if(digit_pos==2 && set_time_min>=60){
					set_time_min-=10;
				}
				//Set fourth Digit
				if(digit_pos==3 && set_time_min>0){
					set_time_min-=1;
				}				
				//set third Digit
				if(digit_pos==4 && set_time_sec>=60){
					set_time_sec-=10;
				}
				//Set fourth Digit
				if(digit_pos==5 && set_time_sec>0){
					set_time_sec-=1;
				}
			}
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<27);} 
		
		//Joystick-left
		if(LPC_GPIOINT->IO0IntStatR&(1<<25)) 
		{	
			//shift Pos left 
			if(digit_pos>0)
				digit_pos--;
			
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<25);} 
		 
		//Joystick-right
		if(LPC_GPIOINT->IO0IntStatR&(1<<28)) 
		{	
			//shift Pos right 
			if(digit_pos<7)
				digit_pos++;
			
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1<<28);} 
		
		//Joystick-Center
		if(LPC_GPIOINT->IO0IntStatR&(1UL<<3)) 
		{	
			//Check if button is pressed again to save change 
			//set_time:1 -> is set and apply new time
			//set_time:0 -> edit mode is activated
			if(set_Time){
				time_h=set_time_h;
				time_min=set_time_min;
				time_sec=set_time_sec;
				set_Time=0;
			}
				
			else{
				set_Time=1;
			}
			
			//reset IRQ
			LPC_GPIOINT->IO0IntClr=(1UL<<3);} 
	}
}


int main(void)
{	
	JoyStick_IRQ_Init();
	SysTick_Config(SystemCoreClock/100);
	SystemCoreClockUpdate();
	

	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"test3.5 Encoder");
	GLCD_DisplayString(3,0,FONT_16x24,(unsigned char*)"Group 11 ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Actual Time of Day:");
	GLCD_Simulation();
	while(1)
	{	

		time_h=(time_h+time_min/60+time_sec/3600)%24;
		time_min=(time_min+time_sec/60)%60;
		time_sec=(time_sec)%60;

		GLCD_DisplayString(6,6,FONT_16x24,(unsigned char*)lcd_time(time_h,time_min,time_sec));
		if (digit_pos==0)
			{GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"SET   X0:00:00");
		GLCD_DisplayString(8,6,FONT_16x24,(unsigned char*)lcd_time(set_time_h,set_time_min,set_time_sec));}
		else	if (digit_pos==1)
			{GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"SET   0X:00:00");
		GLCD_DisplayString(8,6,FONT_16x24,(unsigned char*)lcd_time(set_time_h,set_time_min,set_time_sec));}
		else	if (digit_pos==2)
			{GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"SET   00:X0:00");
	  GLCD_DisplayString(8,6,FONT_16x24,(unsigned char*)lcd_time(set_time_h,set_time_min,set_time_sec));}
		else	if (digit_pos==3)
			{GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"SET   00:0X:00");
	  GLCD_DisplayString(8,6,FONT_16x24,(unsigned char*)lcd_time(set_time_h,set_time_min,set_time_sec));}
		else	if (digit_pos==4)
			{GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"SET   00:00:X0");
	  GLCD_DisplayString(8,6,FONT_16x24,(unsigned char*)lcd_time(set_time_h,set_time_min,set_time_sec));}
		else	if (digit_pos==5)
			{GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"SET   00:00:0X");
	  GLCD_DisplayString(8,6,FONT_16x24,(unsigned char*)lcd_time(set_time_h,set_time_min,set_time_sec));}
		
		GLCD_Simulation();
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T3_7
//================================================================================

#if (T3_7 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

