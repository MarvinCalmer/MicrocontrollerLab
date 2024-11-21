#include <LPC17xx.h>
void DMA_DAC_func (uint32_t* sdata, uint32_t anz)
{
static struct {uint32_t source;
				uint32_t destination;
				uint32_t next;
				uint32_t control;
				} LLI;

LLI.source= (uint32_t) sdata;
LLI.destination= (uint32_t) &LPC_DAC->DACR;
LLI.next= (uint32_t) &LLI.source;
LLI.control=	(anz&0xFFF)//transfer size
							|(0<<12) //Sourceburst number 1							
							|(2<<18)//sourcetransfer size 32 bits
							|(2<<21)//destination transfer size 32 bits
							|(1<<26)// source adress is incremented
							|(1UL<<31);// terminal count interrupt is enabled
	
LPC_SC->PCONP|=(1UL<<29);//GPDMA Power On
LPC_GPDMACH7->DMACCSrcAddr=(uint32_t)sdata;
LPC_GPDMACH7->DMACCDestAddr=(uint32_t)&LPC_DAC->DACR;
LPC_GPDMACH7->DMACCLLI=(uint32_t)&LLI.source;
LPC_GPDMACH7->DMACCControl=
	(anz&0xFFF)//transfer size
	|(0<<12) //sourceburst number 1 
	|(2<<18)//sourcetransfer size 32 bits
	|(2<<21)//destination transfer size 32 bits
	|(1<<26)// source adress is incremented
	|(1UL<<31);// terminal count interrupt is enabled

LPC_GPDMACH7->DMACCConfig 
   =(1UL<<0)//channel enabled
   |(1<<15)// int. dont't mask out
   |(7UL<<6)//DAC peripheral
   |(1UL<<11);//Memory to peripheral

LPC_GPDMA->DMACConfig=(1<<0);//DMA Unit 7 is enabled	
}

//additional for use of terminal interrupts every period:
//uint32_t DMA_Counter=0;
//NVIC_SetPriority (DMA_IRQn,31);
//NVIC_EnableIRQ (DMA_IRQn);
//void DMA_IRQHandler (void) {
//if (LPC_GPDMA->DMACIntTCStat&(1<<7)){
//LPC_GPDMA->DMACIntTCClear=(1<<7);
//DMA_Counter++;//counter of periods of the wave
//}}// not to use in the lab
