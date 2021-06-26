#include "stm32f10x.h"
#include "IERG3810_GenBlock.h"

//define color
#define BLACK 	0x0000
#define WHITE  	0xFFFF
#define BLUE 		0x001F
#define GREEN  	0x7E0
#define RED  		0xF800
#define YELLOW  0xFFE0//0x07FF
#define ORANGE	0xFBE0
#define PINK 		0xF81F
#define CYAN    0x7FF

//Please check the project report for the block number representing what shape

void IERG3810_DrawBlock(int x, int y, int shape) // Draw the block
{
	switch(shape)
	{
		case 1: 
		{
			IERG3810_TFTLCD_FillRectangle(RED, x, 16, y, 16);
		}
		break;
		case 2:
		{
			IERG3810_TFTLCD_FillRectangle(YELLOW, x, 64, y, 16); 
		}
		break;
		case 3: 
		{
			IERG3810_TFTLCD_FillRectangle(YELLOW, x, 16, y, 64);
		}
		break;
		case 4: 
		{
			IERG3810_TFTLCD_FillRectangle(GREEN, x, 48, y+16, 16);
			IERG3810_TFTLCD_FillRectangle(GREEN, x+16, 16, y, 16);
		}
		break;
		case 5: 
		{
			IERG3810_TFTLCD_FillRectangle(GREEN, x, 16, y, 48);
			IERG3810_TFTLCD_FillRectangle(GREEN, x+16, 16, y+16, 16);
		}
		break;
		case 6: 
		{
			IERG3810_TFTLCD_FillRectangle(GREEN, x, 48, y, 16);
			IERG3810_TFTLCD_FillRectangle(GREEN, x+16, 16, y+16, 16);
		}
		break;
		case 7: 
		{
			IERG3810_TFTLCD_FillRectangle(GREEN, x, 16, y+16, 16);
			IERG3810_TFTLCD_FillRectangle(GREEN, x+16, 16, y, 48);
		}
		break;
		case 8: 
		{
			IERG3810_TFTLCD_FillRectangle(PINK, x, 48, y, 16);
			IERG3810_TFTLCD_FillRectangle(PINK, x, 16, y+16, 16);
		}
		break;
		case 9: 
		{
			IERG3810_TFTLCD_FillRectangle(PINK, x, 16, y, 48);
			IERG3810_TFTLCD_FillRectangle(PINK, x+16, 16, y+32, 16);
		}
		break;
		case 10: 
		{
			IERG3810_TFTLCD_FillRectangle(PINK, x, 48, y+16, 16);
			IERG3810_TFTLCD_FillRectangle(PINK, x+32, 16, y, 16);
		}
		break;
		case 11: 
		{
			IERG3810_TFTLCD_FillRectangle(PINK, x, 16, y, 16);
			IERG3810_TFTLCD_FillRectangle(PINK, x+16, 16, y, 48);
		}
		break;
		case 12: 
		{
			IERG3810_TFTLCD_FillRectangle(CYAN, x, 32, y, 16);
			IERG3810_TFTLCD_FillRectangle(CYAN, x+32, 16, y, 32);
		}
		break;
		case 13: 
		{
			IERG3810_TFTLCD_FillRectangle(CYAN, x, 16, y+32, 16);
			IERG3810_TFTLCD_FillRectangle(CYAN, x+16, 16, y, 48);
		}
		break;
		case 14: 
		{
			IERG3810_TFTLCD_FillRectangle(CYAN, x, 16, y, 32);
			IERG3810_TFTLCD_FillRectangle(CYAN, x+16, 32, y+16, 16);
		}
		break;
		case 15: 
		{
			IERG3810_TFTLCD_FillRectangle(CYAN, x, 16, y, 48);
			IERG3810_TFTLCD_FillRectangle(CYAN, x+16, 16, y, 16);
		}
		break;
	}
}

void IERG3810_DelBlock(int x, int y, int shape) // use black rectangle to cover to previous block
{
	switch(shape)
	{
		case 1:
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 16);
		}
		break;
		case 2:
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 64, y, 16); 
		}
		break;
		case 3:
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 64);
		}
		break;
		case 4:
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 48, y+16, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y, 16);
		}
		break;
		case 5: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 48);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y+16, 16);
		}
		break;
		case 6: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 48, y, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y+16, 16);
		}
		break;
		case 7: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y+16, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y, 48);
		}
		break;
		case 8: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 48, y, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y+16, 16);
		}
		break;
		case 9: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 48);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y+32, 16);
		}
		break;
		case 10: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 48, y+16, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+32, 16, y, 16);
		}
		break;
		case 11: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y, 48);
		}
		break;
		case 12: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 32, y, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+32, 16, y, 32);
		}
		break;
		case 13: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y+32, 16);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y, 48);
		}
		break;
		case 14: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 32);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 32, y+16, 16);
		}
		break;
		case 15: 
		{
			IERG3810_TFTLCD_FillRectangle(BLACK, x, 16, y, 48);
			IERG3810_TFTLCD_FillRectangle(BLACK, x+16, 16, y, 16);
		}
		break;
	}
}

int IERG3810_TwistBlock(int blocknum) // twist the block
{
		switch(blocknum)
	{
		case 1: //square
		{
			return 1;
		}
		break;
		case 2: //rectangle (horizontal version)
		{
			return 3;
		}
		break;
		case 3: //rectangle (vertical version)
		{
			return 2;
		}
		break;
		case 4: //t-shape
		{
			return 5;
		}
		break;
		case 5: 
		{
			return 6;
		}
		break;
		case 6: 
		{
			return 7;
		}
		break;
		case 7: 
		{
			return 4;
		}
		break;
		case 8: 
		{
			return 9;
		}
		break;
		case 9: 
		{
			return 10;
		}
		break;
		case 10: 
		{
			return 11;
		}
		break;
		case 11: 
		{
			return 8;
		}
		break;
		case 12: 
		{
			return 13;
		}
		break;
		case 13: 
		{
			return 14;
		}
		break;
		case 14: 
		{
			return 15;
		}
		break;
		case 15: 
		{
			return 12;
		}
		break;
	}
	return 0;
}

void Marking(int blocknum,int x,int y,int block[16][10])  // mark the block into the 2D-array 
{
	int x_axis = (x-10)/16;
	int y_axis = y/16;
	//=1 --> red square
	//=2 --> yellow rectangle
	//=3 --> green t-shape
	//=4 --> pink L-shape
	//=5 --> CYAN L-shape
	switch(blocknum)
	{
		case 1:
		{
			block[y_axis][x_axis]=1;
		}
		break;
		case 2:
		{
			block[y_axis][x_axis]=2;
			block[y_axis][x_axis+1]=2;
			block[y_axis][x_axis+2]=2;
			block[y_axis][x_axis+3]=2;
		}
		break;
		case 3:
		{
			block[y_axis][x_axis]=2;
			block[y_axis+1][x_axis]=2;
			block[y_axis+2][x_axis]=2;
			block[y_axis+3][x_axis]=2;
		}
		break;
		case 4:
		{
			block[y_axis+1][x_axis]=3;
			block[y_axis+1][x_axis+1]=3;
			block[y_axis+1][x_axis+2]=3;
			block[y_axis][x_axis+1]=3;
		}
		break;
		case 5:
		{
			block[y_axis][x_axis]=3;
			block[y_axis+1][x_axis]=3;
			block[y_axis+2][x_axis]=3;
			block[y_axis+1][x_axis+1]=3;
		}
		break;
		case 6:
		{
			block[y_axis][x_axis]=3;
			block[y_axis][x_axis+1]=3;
			block[y_axis][x_axis+2]=3;
			block[y_axis+1][x_axis+1]=3;
		}
		break;
		case 7:
		{
			block[y_axis+1][x_axis]=3;
			block[y_axis][x_axis+1]=3;
			block[y_axis+1][x_axis+1]=3;
			block[y_axis+2][x_axis+1]=3;
		}
		break;
		case 8:
		{
			block[y_axis][x_axis] = 4;
			block[y_axis][x_axis+1] = 4;
			block[y_axis][x_axis+2] = 4;
			block[y_axis+1][x_axis] = 4;
		}
		break;
		case 9:
		{
			block[y_axis][x_axis] = 4;
			block[y_axis+1][x_axis] = 4;
			block[y_axis+2][x_axis] = 4;
			block[y_axis+2][x_axis+1] = 4;
		}
		break;
		case 10:
		{
			block[y_axis+1][x_axis] = 4;
			block[y_axis+1][x_axis+1] = 4;
			block[y_axis+1][x_axis+2] = 4;
			block[y_axis][x_axis+2] = 4;
		}
		break;
		case 11:
		{
			block[y_axis][x_axis] = 4;
			block[y_axis][x_axis+1] = 4;
			block[y_axis+1][x_axis+1] = 4;
			block[y_axis+2][x_axis+1] = 4;
		}
		break;
		case 12:
		{
			block[y_axis][x_axis] = 5;
			block[y_axis][x_axis+1] = 5;
			block[y_axis][x_axis+2] = 5;
			block[y_axis+1][x_axis+2] = 5;
		}
		break;
		case 13:
		{
			block[y_axis+2][x_axis] = 5;
			block[y_axis][x_axis+1] = 5;
			block[y_axis+1][x_axis+1] = 5;
			block[y_axis+2][x_axis+1] = 5;
		}
		break;
		case 14:
		{
			block[y_axis][x_axis] = 5;
			block[y_axis+1][x_axis] = 5;
			block[y_axis+1][x_axis+1] = 5;
			block[y_axis+1][x_axis+2] = 5;
		}
		break;
		case 15:
		{
			block[y_axis][x_axis] = 5;
			block[y_axis+1][x_axis] = 5;
			block[y_axis+2][x_axis] = 5;
			block[y_axis][x_axis+1] = 5;
		}
		break;
	}
}
int CheckNextRow(int blocknum,int x,int y,int block[16][10]) //check nextrow to stop falling through the block
{
	int x_axis = (x-10)/16;
	int y_axis = y/16;
	switch(blocknum)
	{
		case 1:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
		}break;
		case 2:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if (block[y_axis-1][x_axis+1]!=0) return 1;
			else if (block[y_axis-1][x_axis+2]!=0) return 1;
			else if (block[y_axis-1][x_axis+3]!=0) return 1;
		}break;
		case 3:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
		}break;
		case 4:
		{
			if(block[y_axis+1-1][x_axis]!=0) return 1;
			else if (block[y_axis-1][x_axis+1]!=0) return 1;
			else if (block[y_axis+1-1][x_axis+2]!=0) return 1;
		}break;
		case 5:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if (block[y_axis+1-1][x_axis+1]!=0) return 1;
		}break;
		case 6:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
			else if(block[y_axis-1][x_axis+2]!=0) return 1;
		}break;
		case 7:
		{
			if(block[y_axis+1-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
		}break;
		case 8:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
			else if(block[y_axis-1][x_axis+2]!=0) return 1;
		}break;
		case 9:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis+2-1][x_axis+1]!=0) return 1;
		}break;
		case 10:
		{
			if(block[y_axis+1-1][x_axis]!=0) return 1;
			else if(block[y_axis+1-1][x_axis+1]!=0) return 1;
			else if(block[y_axis-1][x_axis+2]!=0) return 1;
		}break;
		case 11:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
		}break;
		case 12:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
			else if(block[y_axis-1][x_axis+2]!=0) return 1;
		}break;
		case 13:
		{
			if(block[y_axis+2-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
		}break;
		case 14:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis+1-1][x_axis+1]!=0) return 1;
			else if(block[y_axis+1-1][x_axis+2]!=0) return 1;
		}break;
		case 15:
		{
			if(block[y_axis-1][x_axis]!=0) return 1;
			else if(block[y_axis-1][x_axis+1]!=0) return 1;
		}break;
	}
	return 0;
}

int CheckLeftCollision(int blocknum,int x,int y,int block[16][10]) // avoid block collide to the left block
{
	int x_axis = (x-10)/16;
	int y_axis = y/16;
	switch(blocknum)
	{
		case 1:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
		}
		break;
		case 2:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
		}
		break;
		case 3:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis+2][x_axis-1]!=0) return 1;
			else if(block[y_axis+3][x_axis-1]!=0) return 1;
		}
		break;
		case 4:
		{
			if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis][x_axis+1-1]!=0) return 1;
		}
		break;
		case 5:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis+2][x_axis-1]!=0) return 1;
		}
		break;
		case 6:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1-1]!=0) return 1;
		}
		break;
		case 7:
		{
			if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis][x_axis+1-1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1-1]!=0) return 1;
		}
		break;
		case 8:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis-1]!=0) return 1;
		}
		break;
		case 9:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis+2][x_axis-1]!=0) return 1;
		}
		break;
		case 10:
		{
			if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis][x_axis+2-1]!=0) return 1;
		}
		break;
		case 11:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1-1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1-1]!=0) return 1;
		}
		break;
		case 12:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis+2-1]!=0) return 1;
		}
		break;
		case 13:
		{
			if(block[y_axis+2][x_axis-1]!=0) return 1;
			else if(block[y_axis][x_axis+1-1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1-1]!=0) return 1;
		}
		break;
		case 14:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis-1]!=0) return 1;
		}
		break;
		case 15:
		{
			if(block[y_axis][x_axis-1]!=0) return 1;
			else if(block[y_axis+1][x_axis-1]!=0) return 1;
			else if(block[y_axis+2][x_axis-1]!=0) return 1;
		}
		break;
		default:
		{
			return 0;
		}
	}
	return 0;
}

int CheckRightCollision(int blocknum,int x,int y,int block[16][10]) // avoid block collide to the right block
{
	int x_axis = (x-10)/16;
	int y_axis = y/16;
	switch(blocknum)
	{
		case 1:
		{
			if(block[y_axis][x_axis+1]!=0) return 1;
		}
		break;
		case 2:
		{
			if(block[y_axis][x_axis+3+1]!=0) return 1;
		}
		break;
		case 3:
		{
			if(block[y_axis][x_axis+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1]!=0) return 1;
			else if(block[y_axis+3][x_axis+1]!=0) return 1;
		}
		break;
		case 4:
		{
			if(block[y_axis][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+2+1]!=0) return 1;
		}
		break;
		case 5:
		{
			if(block[y_axis][x_axis+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1]!=0) return 1;
		}
		break;
		case 6:
		{
			if(block[y_axis][x_axis+2+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1+1]!=0) return 1;
		}
		break;
		case 7:
		{
			if(block[y_axis][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1+1]!=0) return 1;
		}
		break;
		case 8:
		{
			if(block[y_axis][x_axis+2+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1]!=0) return 1;
		}
		break;
		case 9:
		{
			if(block[y_axis][x_axis+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1+1]!=0) return 1;
		}
		break;
		case 10:
		{
			if(block[y_axis][x_axis+2+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+2+1]!=0) return 1;
		}
		break;
		case 11:
		{
			if(block[y_axis][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1+1]!=0) return 1;
		}
		break;
		case 12:
		{
			if(block[y_axis][x_axis+2+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+2+1]!=0) return 1;
		}
		break;
		case 13:
		{
			if(block[y_axis][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1+1]!=0) return 1;
		}
		break;
		case 14:
		{
			if(block[y_axis][x_axis+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+2+1]!=0) return 1;
		}
		break;
		case 15:
		{
			if(block[y_axis][x_axis+1+1]!=0) return 1;
			else if(block[y_axis+1][x_axis+1]!=0) return 1;
			else if(block[y_axis+2][x_axis+1]!=0) return 1;
		}
		break;
		default:
		{
			return 0;
		}
	}
	return 0;
}

void DisplayArray(int block[16][10]) //to refresh the postion of the block
{
	u8 h, k;
	for(h=0; h<16; h++)
	{
		for(k=0; k<10; k++)
		{
			switch(block[h][k])
			{
				case 0:
				{
					IERG3810_TFTLCD_FillRectangle(BLACK, k*16+10, 16, h*16+20, 16);
				}break;
				case 1:
				{
					IERG3810_TFTLCD_FillRectangle(RED, k*16+10, 16, h*16+20, 16);
				}break;
				case 2:
				{
					IERG3810_TFTLCD_FillRectangle(YELLOW, k*16+10, 16, h*16+20, 16);
				}break;
				case 3:
				{
					IERG3810_TFTLCD_FillRectangle(GREEN, k*16+10, 16, h*16+20, 16);
				}break;
				case 4:
				{
					IERG3810_TFTLCD_FillRectangle(PINK, k*16+10, 16, h*16+20, 16);
				}break;
				case 5:
				{
					IERG3810_TFTLCD_FillRectangle(CYAN, k*16+10, 16, h*16+20, 16);
				}break;
			}
		}
	}
}

void MoveLine(int y,int block[16][10]) //update the status of the array block[][]
{
	u8 n, m;
	for(n=y;n<15;n++)
	{
		for(m=0; m<10; m++)
		{
			block[n][m] = block[n+1][m];
		}
	}
	
	for(m=0; m<10; m++)
	{
		block[15][m]=0;
	}
}

void Earase(int y_axis, int block[16][10]) //if the line is full, earase that line
{
	int erase=0;
	IERG3810_TFTLCD_FillRectangle(BLACK, 10, 160, 20+y_axis*16, 16);
	for(erase=0; erase<10; erase++)
	{
		block[y_axis][erase] = 0;
	}
	MoveLine(y_axis, block);
	DisplayArray(block);
}

void CheckLine(int block[16][10], int score[1]) //check whether the line is full or not
{
	int vert=0;
	int hori=0;
	int index=0; 
	
	for(vert=0; vert<16; vert++)
	{
		for(hori=0; hori<10; hori++)
		{
			if(block[vert][hori] !=0 )
			{
				index++;
			}
		}
		if(index==10)
		{
			Earase(vert, block);
			score[0]++;
			index=0;
		}
		else
		{
			index=0;
		}
	}
	IERG3810_TFTLCD_FillRectangle(WHITE, 175, 20, 140, 10);
	IERG3810_TFTLCD_ShowChar(175, 140, score[0]/100+48, RED, WHITE);
	IERG3810_TFTLCD_ShowChar(185, 140, score[0]%100/10+48, RED, WHITE);
	IERG3810_TFTLCD_ShowChar(195, 140, score[0]%10+48, RED, WHITE);
}

int CheckTopLine(int block[16][10]) //check if the block over the top line
{
	u8 n;
	u8 m;
	for(n=0; n<10; n++)
	{
		if(block[15][n] !=0)  return 1;// if(that one is marked)
	}
	return 0;
}
