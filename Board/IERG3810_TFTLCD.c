#include "stm32f10x.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_clock.h"
#include "FONT.h"

typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE	((u32)(0x6C000000) | 0x000007FE)
#define LCD				((LCD_TypeDef *) LCD_BASE)
#define LCD_LIGHT_ON GPIOB->BSRR|=0x000000001; //define light on 

void IERG3810_TFTLCD_Init(void) //set FSMC
{
	RCC ->AHBENR |= 1<<8;  //FSMC
	RCC ->APB2ENR |= 1<<3; //PORTB
	RCC ->APB2ENR |= 1<<5; 	//PORTD
	RCC ->APB2ENR |= 1<<6; //PORTE
	RCC ->APB2ENR |= 1<<8; //PORTG
	GPIOB ->CRL &= 0XFFFFFFF0; //PBO
	GPIOB ->CRL |= 0X00000003;
	
	//PORTD
	GPIOD ->CRH &= 0X00FFF000;
	GPIOD ->CRH |= 0XBB000BBB;
	GPIOD ->CRL &= 0XFF00FF00;
	GPIOD ->CRL |= 0X00BB00BB;
	//PORTE
	GPIOE ->CRH &= 0X00000000;
	GPIOE ->CRH |= 0XBBBBBBBB;
	GPIOE ->CRL &= 0X0FFFFFFF;
	GPIOE ->CRL |= 0XB0000000;
	//PORTG12
	GPIOG ->CRH &= 0XFFF0FFFF;
	GPIOG ->CRH |= 0X000B0000;
	GPIOG ->CRL &= 0XFFFFFFF0; //PG0 ->RS
	GPIOG ->CRL |= 0X0000000B;
	
	//LCD uses FSMC Bank 4 memory bank.
	//Use Mode A
	FSMC_Bank1 ->BTCR[6] = 0X00000000;  //FSMC_BCR4 (reset)
	FSMC_Bank1 ->BTCR[7] = 0X00000000;  //FSMC_BTR4 (reset)
	FSMC_Bank1E ->BWTR[6] = 0X00000000;  //FSMC_BWTR4 (reset)
	FSMC_Bank1 ->BTCR[6] |= 1<<12;  //FSMC_BCR4 -> WREN
	FSMC_Bank1 ->BTCR[6] |= 1<<14;  //FSMC_BCR4 -> EXTMOD
	FSMC_Bank1 ->BTCR[6] |= 1<<4;  //FSMC_BCR4 -> MWID
	FSMC_Bank1 ->BTCR[7] |= 0<<28;  //FSMC_BTR4 -> ACCMOD
	FSMC_Bank1 ->BTCR[7] |= 1<<0;  //FSMC_BTR4 -> ADDSET
	FSMC_Bank1 ->BTCR[7] |= 0XF<<8;  //FSMC_BTR4 -> DATAST
	FSMC_Bank1E ->BWTR[6] |= 0<<28;  //FSMC_BWTR4 -> ACCMOD
	FSMC_Bank1E ->BWTR[6] |= 0<<0;  //FSMC_BWTR4 -> ADDSET
	FSMC_Bank1E ->BWTR[6] |= 3<<8;  //FSMC_BWTR4 -> DATAST
	FSMC_Bank1 ->BTCR[6] |= 1<<0;  //FSMC_BCR4 -> FACCEN
	IERG3810_TFTLCD_SetParameter(); //special setting for LCD modeule
	LCD_LIGHT_ON;
	
}
	
void IERG3810_TFTLCD_SetParameter(void)
{
	IERG3810_TFTLCD_WrReg(0X01); //Software reset
	IERG3810_TFTLCD_WrReg(0X11); //Exit_sleep_mode
	
	IERG3810_TFTLCD_WrReg(0X3A); //Set_pixel_format
	IERG3810_TFTLCD_WrData(0X55); //65536 colors
	
	IERG3810_TFTLCD_WrReg(0X29); //Display ON
	
	IERG3810_TFTLCD_WrReg(0X36); //Memory Access Control (section 8.2.29, page 127)
	IERG3810_TFTLCD_WrData(0XCA);
	
}

void IERG3810_TFTLCD_WrReg(u16 regval)
{
	LCD->LCD_REG=regval;
}

void IERG3810_TFTLCD_WrData(u16 data)
{
	LCD->LCD_RAM=data;
}

void IERG3810_TFTLCD_DrawDot(u16 x, u16 y, u16 color)
{
	IERG3810_TFTLCD_WrReg(0x2A); //set x position
	IERG3810_TFTLCD_WrData(x>>8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData(0x01);
	IERG3810_TFTLCD_WrData(0x3F);
	
	IERG3810_TFTLCD_WrReg(0x2B); //set y position
	IERG3810_TFTLCD_WrData(y>>8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData(0x01);
	IERG3810_TFTLCD_WrData(0xDF);
	
	IERG3810_TFTLCD_WrReg(0X2C); //set point with color
	IERG3810_TFTLCD_WrData(color);
}

void IERG3810_TFTLCD_FillRectangle(u16 color, u16 start_x, u16 length_x, u16 start_y, u16 length_y)
{
	u32 index = 0;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(start_x >>8);
	IERG3810_TFTLCD_WrData(start_x & 0xFF);
	IERG3810_TFTLCD_WrData((length_x + start_x - 1) >> 8);
	IERG3810_TFTLCD_WrData((length_x + start_x - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(start_y >>8);
	IERG3810_TFTLCD_WrData(start_y & 0xFF);
	IERG3810_TFTLCD_WrData((length_y + start_y - 1) >> 8);
	IERG3810_TFTLCD_WrData((length_y + start_y - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2C); //LCD_WriteRam_Prepare();
	for(index=0; index<length_x * length_y; index++)
	{
		IERG3810_TFTLCD_WrData(color);
	}
}

void IERG3810_TFTLCD_SevenSegment(u16 color, u16 start_x, u16 start_y, u16 digit)
{
	
	if(digit == 0)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-120, 55); //segment e
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-55, 55); //segment f
	} else if(digit == 1)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c		
	} else if (digit == 2)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-120, 55); //segment e
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	} else if (digit == 3)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	} else if (digit == 4)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-55, 55); //segment f
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	} else if (digit == 5)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-55, 55); //segment f
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	} else if (digit == 6)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-120, 55); //segment e
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-55, 55); //segment f
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	} else if (digit == 7)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
	} else if (digit == 8)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-120, 55); //segment e
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-55, 55); //segment f
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	} else if (digit == 9)
	{
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y, 10); //segment a
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-55, 55); //segment b
		IERG3810_TFTLCD_FillRectangle(color, start_x+55, 10, start_y-120, 55); //segment c
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-130, 10); //segment d
		IERG3810_TFTLCD_FillRectangle(color, start_x-10, 10, start_y-55, 55); //segment f
		IERG3810_TFTLCD_FillRectangle(color, start_x, 55, start_y-65, 10); //segment g
	}
}

void IERG3810_TFTLCD_ShowChar(u16 x, u16 y, u8 ascii, u16 color,u16 bgcolor)
{
	u8 i,j;
	u8 index;
	u8 height=16,length =8;
	if(ascii<32 || ascii>127) return;
	ascii-=32;
	IERG3810_TFTLCD_WrReg(0x2A);
		IERG3810_TFTLCD_WrData(x>>8);
		IERG3810_TFTLCD_WrData(x & 0xFF);
		IERG3810_TFTLCD_WrData((length + x -1) >> 8);
		IERG3810_TFTLCD_WrData((length + x -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
		IERG3810_TFTLCD_WrData(y>>8);
		IERG3810_TFTLCD_WrData(y & 0xFF);
		IERG3810_TFTLCD_WrData((height + y -1) >> 8);
		IERG3810_TFTLCD_WrData((height + y -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C);// LCD_WriteRam_Prepare()
	
	for(j=0; j<height/8; j++)
	{
		for(i=0; i<height/2; i++)
		{
			for(index=0;index<length ;index++)
			{
				if((asc2_1608[ascii][index*2+1-j]>>i) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
		}
	}
}

