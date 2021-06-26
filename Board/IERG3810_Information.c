#include "stm32f10x.h"
#include "IERG3810_Information.h"

// put your procedure and code here

//define color
#define BLACK 	0x0000
#define WHITE  	0xFFFF
#define BLUE 		0x001F
#define GREEN  	0x7E0
#define RED  		0xF800
#define YELLOW  0xFFE0//0x07FF
#define ORANGE	0xFBE0
#define PINK 		0xF81F
#define GREY    0xBDF7

int i2=0;
int CUID1[10] = {49, 49, 53, 53, 49, 50, 55, 48, 50, 52}; //1155127024
int CUID2[10] = {49, 49, 53, 53, 49, 50, 53, 51, 49, 51}; //1155125313
int Name1[15] = {67, 104, 101, 117, 110, 103, 32, 70, 97, 105, 32, 84, 117, 110, 103}; //Cheung Fai Tung 
int Name2[14] = {67, 104, 101, 110, 103, 32, 87, 105, 110, 103, 32, 76, 97, 109}; //Cheng Wing Lam

int instruction1[86] = {89, 111, 117, 32, //You 
											99, 97, 110, 32,     //can 
											116, 119, 105, 115, 116, 32, //twist  
											97, 110, 100, 32, //and
											99, 104, 97, 110, 103, 101, 32,  //change
											116, 104, 101, 32, //the 
											115, 112, 101, 101, 100, 32, //speed
											111, 102, 32,  //of
											102, 97, 108, 108, 105, 110, 103, 32, //falling 
											98, 108, 111, 99, 107, 32,  //block
											98, 121, 32,  //by
											117, 115, 105, 110, 103, 32, //using
											116, 104, 101, 32, //the
											107, 101, 121, 98, 111, 97, 114, 100, 32, //keyboard
											50, 44, 52, 44, 54, 44, 56 //2, 4, 6, 8
};
int instruction2[19] = {80, 114, 101, 115, 115, 32, //Press
										107, 101, 121, //key
										49, 32, //1
										116, 111, 32, //to
										115, 116, 97, 114, 116 //start
};

void PrintStartPage(void) //print our name and sid and game title
{
	//Print T
	IERG3810_TFTLCD_FillRectangle(RED, 20, 40, 280,8);
	IERG3810_TFTLCD_FillRectangle(RED, 36, 8, 240,40);
	
	//print E
	IERG3810_TFTLCD_FillRectangle(ORANGE, 60, 40, 280,8);
	IERG3810_TFTLCD_FillRectangle(ORANGE, 60, 40, 260,8);
	IERG3810_TFTLCD_FillRectangle(ORANGE, 60, 40, 240,8);
	IERG3810_TFTLCD_FillRectangle(ORANGE, 60, 8, 240,40);
	
	//Print T
	IERG3810_TFTLCD_FillRectangle(YELLOW, 100, 40, 280,8);
	IERG3810_TFTLCD_FillRectangle(YELLOW, 116, 8, 240,40);
	
	//Print R
	IERG3810_TFTLCD_FillRectangle(GREEN, 140, 32, 280,8);
	IERG3810_TFTLCD_FillRectangle(GREEN, 140, 32, 260,8);
	IERG3810_TFTLCD_FillRectangle(GREEN, 140, 8, 240,40);
	IERG3810_TFTLCD_FillRectangle(GREEN, 164, 8, 260,20);
	IERG3810_TFTLCD_FillRectangle(GREEN, 156, 8, 250,10);
	IERG3810_TFTLCD_FillRectangle(GREEN, 164, 8, 240,10);
	
	//Print I
	IERG3810_TFTLCD_FillRectangle(BLUE, 180, 8, 240,48);
	
	//Print S
	IERG3810_TFTLCD_FillRectangle(BLACK, 200, 32, 280,8);
	IERG3810_TFTLCD_FillRectangle(BLACK, 200, 32, 260,8);
	IERG3810_TFTLCD_FillRectangle(BLACK, 200, 32, 240,8);
	IERG3810_TFTLCD_FillRectangle(BLACK, 200, 8, 260,20);
	IERG3810_TFTLCD_FillRectangle(BLACK, 224, 8, 240,20);
	
	for(i2=0; i2<15; i2++) //Print Name1
	{
		IERG3810_TFTLCD_ShowChar(50+i2*10, 150, Name1[i2], BLACK, WHITE);
	}
		
	for(i2 =0 ;i2<14; i2++) //Print Name2
	{
		IERG3810_TFTLCD_ShowChar(50+i2*10, 110, Name2[i2], BLACK, WHITE);
	}
		
	for(i2=0; i2<10; i2++) //Print CUID
	{
		IERG3810_TFTLCD_ShowChar(70+i2*10, 170, CUID1[i2], BLACK, WHITE);
		IERG3810_TFTLCD_ShowChar(70+i2*10, 130, CUID2[i2], BLACK, WHITE);
	}
}

void PrintInstruction(void) //printing the instruction of the game
{
		for(i2=0;i2<25; i2++)
		{
			IERG3810_TFTLCD_ShowChar(0+i2*10, 200, instruction1[i2], RED, WHITE);
		}
		for(i2=0; i2<20; i2++)
		{
			IERG3810_TFTLCD_ShowChar(20+i2*10, 180, instruction1[25+i2], RED, WHITE);
		}
		for(i2=0; i2<18; i2++)
		{
			IERG3810_TFTLCD_ShowChar(30+i2*10, 160, instruction1[46+i2], RED, WHITE);
		}
		for(i2=0; i2<16; i2++)
		{
			IERG3810_TFTLCD_ShowChar(31+i2*10, 140, instruction1[65+i2], RED, WHITE);
		}
		for(i2=0; i2<19; i2++)
		{
			IERG3810_TFTLCD_ShowChar(25+i2*10, 80, instruction2[i2], BLACK, WHITE);
		}
}

void draw_Hline(u16 x, u16 y, u16 color,u16 length) //draw horizontal line 
{
	for(i2=0;i2<length;i2++)
	{
		IERG3810_TFTLCD_DrawDot(x+i2,y,color);
	}
}

void draw_Vline(u16 x, u16 y, u16 color,u16 length) //draw vertical line
{
	for(i2=0;i2<length;i2++)
	{
		IERG3810_TFTLCD_DrawDot(x,y+i2,color);
	}
}

void IERG3810_DrawLine(void) //draw the line inside the game zone
{
	int i=20;
	while(i<260)
	{
		draw_Hline(10,i,WHITE,160);
		i+= 16;
	}
	i = 10;	
	while(i<160)
	{
	 draw_Vline(i, 20, WHITE, 260);
		i+=16;
	}
}

void GameOver(void) //words to print when game over
{
	//Print G
	IERG3810_TFTLCD_FillRectangle(RED, 30, 30,189 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 30, 6, 165 ,30);
	IERG3810_TFTLCD_FillRectangle(RED, 30, 30,165 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 54, 6, 165 ,18);
	IERG3810_TFTLCD_FillRectangle(RED, 42, 18,177 ,6);
	
	//Print A
	IERG3810_TFTLCD_FillRectangle(BLUE, 65, 30,189 ,6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 65, 6, 165 ,30);
	IERG3810_TFTLCD_FillRectangle(BLUE, 65, 30,177 ,6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 89, 6,165 ,30);
	
	//Print M
	IERG3810_TFTLCD_FillRectangle(RED, 100, 30,189 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 100, 6, 165 ,30);
	IERG3810_TFTLCD_FillRectangle(RED, 112, 6, 165 ,30);
	IERG3810_TFTLCD_FillRectangle(RED, 124, 6, 165 ,30);
	
	//Print E
	IERG3810_TFTLCD_FillRectangle(BLUE, 135, 30,189 ,6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 135, 30,177 ,6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 135, 30,165 ,6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 135, 6,165 ,30);
	
	//Print O
	IERG3810_TFTLCD_FillRectangle(BLUE, 30, 30, 125, 6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 30, 6, 131, 24);
	IERG3810_TFTLCD_FillRectangle(BLUE, 36, 24, 149, 6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 54, 6, 131, 24);

	//Print V
	IERG3810_TFTLCD_FillRectangle(RED, 65, 6,137 ,18);
	IERG3810_TFTLCD_FillRectangle(RED, 71, 6,131 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 77, 6,125 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 83, 6,131 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 89, 6,137 ,18);
	
	//Print E
	IERG3810_TFTLCD_FillRectangle(BLUE, 100, 6, 125, 30);
	IERG3810_TFTLCD_FillRectangle(BLUE, 100, 30, 125, 6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 100, 30, 137, 6);
	IERG3810_TFTLCD_FillRectangle(BLUE, 100, 30, 149, 6);

	//Print R
	IERG3810_TFTLCD_FillRectangle(RED, 135, 30,149 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 135, 30,137 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 135, 6,125 ,30);
	IERG3810_TFTLCD_FillRectangle(RED, 159, 6,137 ,18);
	IERG3810_TFTLCD_FillRectangle(RED, 153, 6,131 ,6);
	IERG3810_TFTLCD_FillRectangle(RED, 159, 6,125 ,6);
}
