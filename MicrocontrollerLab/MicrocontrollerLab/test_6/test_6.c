/******************************************************************************

test_6.c

	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//Einbinden v. Header Files:
//================================================================================
#include <LPC17xx.h>
#include "GLCD.h"
#include "tests.h"


//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//================================================================================
//  test T6_1
//================================================================================
#if (T6_1==1)
#include "I2C.h"
//add I2C.C ..\peripherals\source\ to your project
//initialize SSPO with bitrate 1MHZ, 8 Bit, SPI-Mode, CPOL: low level, CPHA: first edge, Normal Master Mode
extern void init_lab6_ssp0 (void);//please prepare/write the code by yourself

  uint32_t secs_over=0,secs=0;
  uint8_t SegChars[10]={0x24,0xAF,0xE0,0xA2,0x2B,0x32,0x30,0xA7,0x20,0x22};//0..9
  uint8_t secCode[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0..9
  uint8_t sbuf [5]; //send buffer with 5 bytes
	int32_t ret=0;

	void SysTick_Handler(void)
	{
		static uint32_t count100ms=0;
		count100ms++;
		if (count100ms>9)
    {
			count100ms=0;secs_over=1;secs++;
			if (secs>9) secs=0;
			#ifdef __TARGET_HW
			LPC_SSP0->DR = SegChars[secs];//output to 7 segment displays
			#endif
			}
	}
	
#define Seg7_I2C_ADDR 0x38
int main(void)
{	
	  SystemCoreClockUpdate();
	  sbuf[0]=0;sbuf[1]=0x17;//initialize I2C device
  	#ifdef __TARGET_HW
//  	  init_lab6_ssp0(); //init SSP0 bus
	    I2C1_Init();
	    ret=I2C1Write(Seg7_I2C_ADDR,sbuf,2);//initialize I2C device
	    SysTick_Config(SystemCoreClock/10); // cycle 100ms 
	  #endif
	  #ifndef __TARGET_HW
			SysTick_Config(SystemCoreClock/10000); // cycle 0,1us for simulation 		
	  #endif

  LPC_GPIO0->FIOCLR = (1 << 1); // activate left segment
	LPC_GPIO3->FIOCLR = (1 << 25); // activate right segment


	while(1)
	{
		  if (secs_over==1)
			{
			secs_over=0;
	  	sbuf[0] = 01; //address of the most left segment (first digit)
			sbuf[1] = secCode[(secs&0xF)]|0x80;
			sbuf[2] = secCode[(secs&0xF)]|0x80;
			sbuf[3] = secCode[(secs&0xF)]|0x80;
			sbuf[4] = secCode[(secs&0xF)]|0x80;

				#ifdef __TARGET_HW			
				ret=I2C1Write(Seg7_I2C_ADDR, sbuf, 5);//output to 4 7 segment displays
			#endif
		  #ifndef __TARGET_HW
		  //printout sbuf[];
		  #endif
			}
	} // end while(1)
}	// end main()


#endif


//
//================================================================================
//  test T6_2
//================================================================================
#if (T6_2==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_3
//================================================================================
#if (T6_3==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_4
//================================================================================
#if (T6_4==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_5
//================================================================================
#if (T6_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


#if (T6_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_7
//================================================================================
#if (T6_7==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

