#include "stm32f10x.h"
#include "IERG3810_LED.h"

// put your procedure and code here
void IERG3810_LED_Init(void)
{
	RCC -> APB2ENR |= 1 << 3;  //LED0 PB5
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init (GPIOB, & GPIO_InitStructure);
	//GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIOB ->CRL &= 0xFF0FFFFF; 
	GPIOB ->CRL |= 0x00300000;
	
	RCC -> APB2ENR |= 1 << 3;  //LED1 PE5
	GPIOE ->CRL &= 0xFF0FFFFF;
	GPIOE ->CRL |= 0x00300000;
	GPIOE ->BSRR = 1 << 5;
}
