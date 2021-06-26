#include "stm32f10x.h"
#include "IERG3810_Buzzer.h"

// put your procedure and code here
void IERG3810_Buzzer_Init(void)
{
	GPIOB ->CRH &= 0xFFFFFFF0; //Buzzer(B8) define 
	GPIOB ->CRH |= 0x00000003;
	GPIOB ->BRR = 1 << 8;
}
