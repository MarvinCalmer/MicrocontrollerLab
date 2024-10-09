/******************************************************************************
led.h
******************************************************************************/


//	Autor: 
//	date: 
	       

/********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include "tests.h"

extern void LED_Init(void);
extern void LED_On(uint8_t LedNum);
extern void LED_Off(uint8_t LedNum);
extern void LED_Toggle(uint8_t LedNum);
extern void RGB_On(uint8_t num);
extern void RGB_Off(uint8_t num);
extern void LED_Out(unsigned char value);
