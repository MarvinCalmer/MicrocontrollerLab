#include "tests.h"

extern void Counter_Init(uint8_t TimerNum, uint8_t CapIn, uint8_t edge);

extern void Timer_Init (uint8_t TimerNum, uint32_t cycle, uint32_t TimerDivid, uint8_t pclksrc , uint8_t ResetMR);