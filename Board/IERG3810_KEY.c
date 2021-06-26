#include "stm32f10x.h"
#include "IERG3810_KEY.h"

// put your procedure and code here

void IERG3810_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //KEY2 Pin2 PE2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOE, & GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_2);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //KEY1 Pin3 PE3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOE, & GPIO_InitStructure);
	GPIO_SetBits(GPIOE, GPIO_Pin_3);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //Define Keyup pin0 PA0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA, & GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	RCC -> APB2ENR |= 1 << 3;
	GPIOA ->CRH &= 0xFFFFFFF0;
	GPIOA ->CRH |= 0x00000003; 
	GPIOA ->BRR |= 0x00000001;
}
