#include "stm32f10x.h"
#include "IERG3810_USART.h"

void IERG3810_USART2_init(u32 pclk1,u32 bound)
{
	//USART
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk1*1000000)/(bound*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
		mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR|=1<<2;  //IOPAEN-->2
	RCC->APB1ENR|=1<<17; //USART2-->17
	GPIOA->CRL&=0XFFFF00FF;
	GPIOA->CRL|=0X00008B00;
	RCC->APB1RSTR|=1<<17;
	RCC->APB1RSTR&=~(1<<17);
	USART2->BRR=mantissa;
	USART2->CR1|=0X2008;
}

void IERG3810_USART1_init(u32 pclk2,u32 bound)
{
	//USART
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk2*1000000)/(bound*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
		mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR|=1<<2;
	RCC->APB2ENR|=1<<14; //
	GPIOA->CRH&=0XFFFFF00F; //PA9
	GPIOA->CRH|=0X000008B0; //PA10
	RCC->APB2RSTR|=1<<14;//
	RCC->APB2RSTR&=~(1<<14);//
	USART1->BRR=mantissa;
	USART1->CR1|=0X2008;
}

void USART_print(u8 USARTport, char *st)
{
		u8 i=0;
		while(st[i] !=0x00)
		{
				if (USARTport == 1 && (USART1->SR &= 0X0FFFFFFF)) 
					{
						USART1->DR = st[i];	
						while(!(USART1->SR &= 0X0FFFFFFF));
					}
				if (USARTport == 2 && (USART2->SR &= 0X0FFFFFFF))
				{
						USART2->DR = st[i];	
						while(!(USART2->SR &= 0X0FFFFFFF));
				}
					
			//Delay(50000);
			
			if	(i == 255 ) break;
			i++;
		}
}
