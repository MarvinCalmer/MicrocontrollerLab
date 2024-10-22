#include "tests.h"

extern void ADC_Init (uint8_t chsel, uint8_t intEn);
extern void ADC_StartCnv(uint8_t chsel, uint8_t burst);
extern void ADC_StopCnv();
extern uint32_t ADC_Stat();
extern uint32_t ADC_GetValue(unsigned int channel);