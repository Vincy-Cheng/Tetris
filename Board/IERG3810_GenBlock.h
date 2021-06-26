#ifndef __IERG3810_GENBLOCK_H
#define __IERG3810_GENBLOCK_H
#include "stm32f10x.h"
#include "IERG3810_TFTLCD.h"

// put procedure header here

void IERG3810_DrawBlock(int x, int y, int shape);
void IERG3810_DelBlock(int x, int y, int shape);
int IERG3810_TwistBlock(int blocknum);
void Marking(int blocknum,int x,int y,int block[16][10]);
int CheckNextRow(int blocknum,int x,int y,int block[16][10]);
int CheckLeftCollision(int blocknum,int x,int y,int block[16][10]);
int CheckRightCollision(int blocknum,int x,int y,int block[16][10]);
void Earase(int y_axis, int block[16][10]);
void CheckLine(int block[16][10], int score[1]);
void DisplayArray(int block[16][10]);
void MoveLine(int y,int block[16][10]);
int CheckTopLine(int block[16][10]);

#endif
