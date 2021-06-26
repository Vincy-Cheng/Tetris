#ifndef __IERG3810_INFORMATION_H
#define __IERG3810_INFORMATION_H
#include "stm32f10x.h"
#include "IERG3810_TFTLCD.h"

// put procedure header here

void PrintStartPage(void);
void PrintInstruction(void);
void draw_Hline(u16 x, u16 y, u16 color,u16 length);
void draw_Vline(u16 x, u16 y, u16 color,u16 length);
void IERG3810_DrawLine(void);
void GameOver(void);

#endif
