#include "stm32f10x.h"
#include "stdlib.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_USART.h"
#include "IERG3810_GenBlock.h"
#include "IERG3810_Information.h"
#include "Global.h"

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
#define CYAN    0x7FF

#define DS0_ON GPIOB ->BRR |= 1 << 5
#define DS0_OFF GPIOB ->BSRR |= 1 << 5
#define DS1_ON GPIOE ->BRR |= 1 << 5
#define DS1_OFF GPIOE ->BSRR |= 1 << 5
#define BUZZER_ON GPIOB ->BSRR = 1 << 8
#define BUZZER_OFF GPIOB ->BRR = 1 << 8

u32 ps2count;
u32 ps2key;
u32 sheep = 0;
u32 timeout;
u8 task1HeartBeat;
u8 task2HeartBeat;
u8 task3HeartBeat;
u8 task4HeartBeat;
int score[1]={0};

int i=0;
// use to print the information
int showlevel[6]={76, 101, 118, 101, 108, 58}; //"Level:"
int showtime[10]={84, 105, 109, 101, 32, 108, 101, 102, 116, 58}; //Time Left:
int showscore[6]={83, 99, 111, 114, 101, 58 }; //Score:
int congrat[15] = {67, 111, 110, 103, 114, 97, 116, 117, 108, 97, 116, 105, 111, 110, 33}; //Congratulation!
int Win[8] = {89, 111, 117, 32, 87, 105, 110, 33}; // You Win!

int second=180; //Time of second
int start=0; //variable means game start or not
int timer_stop; //variable of controling timer to stop 
int y_axis = 260; //falling down coordinate_y
int level=1; //variable to indicate level
int speed=50; //indicate of falling speed

int x_moving =0; // use for left/right moving
int x_previous; // use to store the previous x-coordinate for update the x-coordinate
int y_previous; // use to store the previous y-coordinate for update the y-coordinate

int blocknum; // different block shape
int arrive; // use to check whether the block reach the bottom
int j, k;

int pressed=0; //indicate the key_up was preesed
int block[16][10]; // use to store the status of the "playground", "playground" means the black rectangle that allow block falling

int c=0; //indicate checktopline 

void Delay(u32 count) //delay function
{
	u32 i;
	for (i=0; i<count; i++);
}

void IERG3810_NVIC_SetPriorityGroup(u8 prigroup)
{
	//Set PRIGROUP AIRCR[10:8]
	u32 temp, temp1;
	temp1 = prigroup & 0x00000007; //only concern 3 bits
	temp1 <<= 8; //'Why?'
	temp = SCB->AIRCR; //ARM DDI0337E page 8-22;
	temp &= 0x0000F8FF; //ARM DDI0337E page 8-22;
	temp |= 0x05FA0000; //ARM DDI0337E page 8-22;
	temp |= temp1;
	SCB->AIRCR=temp;
}

void IERG3810_PS2key_ExtiInit(void) //Initialize ps2 keyboard
{
	//PS2 (CLK)at PC11, EXTI-11, IRQ#40
	//PS2 (DATA)at PC10, EXTI-15_10,
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRH &= 0XFFFF0FFF;
	GPIOC->CRH |= 0X00008000;
	GPIOC->ODR |= 1 << 2;
	RCC->APB2ENR|= 0x01;
	AFIO->EXTICR[2] &= 0xFFFF0FFF;
	AFIO->EXTICR[2] |= 0X00002000;
	EXTI->IMR |= 1 << 11;
	EXTI->FTSR |= 1<<11;//(RM0008 -page203)
	
	NVIC->IP[40] = 0x65;
	NVIC->ISER[1] |= (1<<8);
}

void EXTI15_10_IRQHandler(void) //keyboard handler
{
	if (ps2count > 0 && ps2count < 9) {
				ps2key |= (GPIOC->IDR & 0x00000400) >> (10 - ps2count + 1);
		}
		ps2count ++;
		Delay(10);
		EXTI->PR = 1 << 11;
		// ps2key become like 0b000011100 something like that
}

void IERG3810_SYSTICK_Init10ms(void)
{
	//SYSTICK
	SysTick ->CTRL =0; //Clear Systick>CTRL setting // clear all the value
	SysTick ->LOAD =90000; //Refer to 0337E page 8-10 // cause we are using 10ms. 9MHz/10ms = 90000
	//CLKSOURCE = 0: STCLK (FCLK/8)
	//CLKSOURCE=1: FCLK
	//CLKSOURCE=0 is synchronized and better than CLKSOURCE=1
	//Refer to clock tree on page-93 of RM0008
	SysTick ->CTRL |= (1<<16 | 0x03); //Refer to 033E page8-8. // intialize enable & CLKSOURCE & TICKINT
}

void show_infomation(void)  
{
			for(i=3;i>0;i--) // Exp 3.3 //countdown 3 seconds before start
			{
				IERG3810_TFTLCD_FillRectangle(WHITE, 0, 240, 0, 360);
				IERG3810_TFTLCD_SevenSegment(RED, 93, 215, i);
				Delay(10000000);
			}
			IERG3810_TFTLCD_FillRectangle(WHITE, 0, 240, 0, 320); //cover
			IERG3810_TFTLCD_FillRectangle(BLACK, 10, 160, 20, 260); //print game zone
			for(i=0;i<6;i++)
			{
				IERG3810_TFTLCD_ShowChar(175+i*10, 260, showlevel[i], BLACK, WHITE); //print the words "level:"
			}
			IERG3810_TFTLCD_ShowChar(175, 240, level+48, BLACK, WHITE); //print value of level
			for(i=0;i<5;i++)
			{
				IERG3810_TFTLCD_ShowChar(175+i*10, 220, showtime[i], BLACK, WHITE); //print the words "time"
			}
			for(i=5;i<10;i++)
			{
					IERG3810_TFTLCD_ShowChar(175+(i-5)*10, 200, showtime[i], BLACK, WHITE); //print the words "left"
			}
			for(i=0;i<6;i++)
			{
				IERG3810_TFTLCD_ShowChar(175+i*10, 160, showscore[i], BLACK, WHITE); //print the words "score"
			}
			IERG3810_TFTLCD_ShowChar(195, 180, 58, BLACK, WHITE); //print the words ":"
			draw_Hline(10,260,BLUE,160); //drar the top line
			start =1; //indicate game start
			second = 180; //3 minutes
			timer_stop=0; //indicate the timer start counting down
}

void Print_Time(int sec) { // 3-min countdown
	if(timer_stop == 0)
	{
		int min = sec / 60;
		int tens = sec % 60 / 10; //represent tens digit
		int unit = sec % 60 % 10; //represent tens digit

		IERG3810_TFTLCD_FillRectangle(WHITE, 185, 10, 180, 10);
		IERG3810_TFTLCD_ShowChar(180, 180, 48+min, BLACK, WHITE); //print(min)
	
		IERG3810_TFTLCD_FillRectangle(WHITE, 205, 20, 180, 10); //print second
	
		IERG3810_TFTLCD_ShowChar(205, 180, 48+tens, BLACK, WHITE);
		IERG3810_TFTLCD_ShowChar(215, 180, 48+unit, BLACK, WHITE);
	}
	else
	{
		IERG3810_TFTLCD_FillRectangle(WHITE, 185, 10, 180, 10);
		IERG3810_TFTLCD_ShowChar(180, 180, 48, BLACK, WHITE); //print(min)
		IERG3810_TFTLCD_FillRectangle(WHITE, 205, 20, 180, 10); //print second
		IERG3810_TFTLCD_ShowChar(205, 180, 48, BLACK, WHITE);
		IERG3810_TFTLCD_ShowChar(215, 180, 48, BLACK, WHITE);
	}		
}

void IERG3810_keyup_ExtiInit(void)
{
	//KEYUP at PA0, EXTI-0, IRQ#6
	RCC->APB2ENR |= 1<<2; //Refer to lab-1
	GPIOA->CRL &= 0XFFFFFFF0; //Refer to lab-1 
	GPIOA->CRL |= 0X00000008; //Refer to lab-1 
	GPIOA->ODR |= 0;//Refer to lab-1 
	RCC->APB2ENR|= 0x01; //(RM0008 -page119)
	AFIO->EXTICR[0] &= 0xFFFFFFF0;//(RM0008 -page185) 
	AFIO->EXTICR[0] |= 0X00000000;//(RM0008 -page185) 
	EXTI->IMR |= 1;//(RM0008 -page202)
	//EXTI->FTSR |= 1;//(RM0008 -page203)
	EXTI->RTSR |= 1<<0;//(RM0008 -page203)
	
	NVIC->IP[6] = 0x45; //set priority of this interrupt. (D10337E page 9-4, 8-16) // refer to lab manual page 5
	NVIC->ISER[0] |= (1<<6); // (D10337E page 8-3)
}

void Reset() //used to reset the data and the board
{
	for(j=0; j<16; j++)
	{
		for(k=0; k<10; k++)
		{
			block[j][k] = 0;
		}
	}
	start=0;
	timer_stop=1;
	y_axis=260;
	x_moving=0;
	blocknum = rand()%15+1;
	show_infomation();
	DS0_OFF;
	DS1_OFF;
	c=0;
}


void EXTI0_IRQHandler(void) //keyup 
{
	// use to reset the game
	Reset();
	pressed=1;
	level=1;
	score[0]=0;
	speed=50;
	EXTI->PR = 1<<0; //Clear this exception pending bit
}

int loop;
int neloop;
int printing = 0x30;
int main (void)
{
	IERG3810_clock_tree_init();
	IERG3810_KEY_Init();	
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	IERG3810_NVIC_SetPriorityGroup(5);
	IERG3810_PS2key_ExtiInit();
	IERG3810_TFTLCD_Init();
	IERG3810_SYSTICK_Init10ms();
	IERG3810_keyup_ExtiInit();
	IERG3810_USART2_init(36 ,9600);
  IERG3810_USART1_init(72 ,9600);

	DS0_OFF;
	DS1_OFF;
	BUZZER_OFF;
	IERG3810_USART2_init(36,9600); //for debug
	IERG3810_USART1_init(72,9600);
	
	IERG3810_TFTLCD_FillRectangle(WHITE, 0, 240, 0, 320); //refresh 
	IERG3810_TFTLCD_FillRectangle(WHITE, 0, 240, 0, 320);
	
	PrintStartPage(); 
	Delay(30000000);
	IERG3810_TFTLCD_FillRectangle(WHITE, 0, 240, 0, 320);
	PrintInstruction();
	
	blocknum = rand()%15 +1; //generate random block number
	for(j=0; j<16; j++)
	{
		for(k=0; k<10; k++)
		{
			block[j][k] = 0; //initilize the 2-d array 
		}
	}
	
	while(1)
	{
		if(!(GPIOE ->IDR & GPIO_Pin_3) && start==0) //key1 was pressed
		{
			show_infomation();
		}
		if(second <= 0)
		{
			timer_stop = 1; //indicate the timer stop 
		}
		if(task1HeartBeat >= 100 ) 
		{
				task1HeartBeat = 0;
				second--;
		}
		if(start==1 && timer_stop ==0 && c == 1) //check game_over within the game
		{
			timer_stop=1;
			start=0;
			GameOver();
			level=1;
			DS0_ON;
		}	
		else if (timer_stop ==1 && start == 1 && c == 1) //another way to game over once the time uses up
		{
			GameOver();
			DS1_ON;
		}
		
		if(timer_stop==1 && c==0 && level<=3 && pressed==0) //way to promote to next level
		{
			level++;
			Reset();
			speed-=10;
		}
		else if(level>3) //finish the game
		{
			timer_stop=1;
			start=0;
			pressed=0;
			speed=50;
			for(i=0; i<15; i++)
			{
				IERG3810_TFTLCD_ShowChar(20+i*8, 140, congrat[i], RED, WHITE); //print congrat message
			}
			for(i=0; i<8; i++)
			{
				IERG3810_TFTLCD_ShowChar(20+i*8, 120, Win[i], RED, WHITE); //print congrat message
			}
		}
		
		if(start == 1 && timer_stop ==0) // game start
		{
			Print_Time(second);
			IERG3810_DrawLine();
			pressed=0;			
			if(task2HeartBeat >= speed) //
			{
				IERG3810_TFTLCD_FillRectangle(WHITE, 10, 160, 280, 48);				
				 // that function is written in the GenBlock 
				Delay(5000);
				if(y_axis <16 || (CheckNextRow(blocknum,90+x_moving,y_axis,block)) == 1)
				{
					// only allow the y-coordinates are within the border of the black rectangle and next row no block
					Marking(blocknum,90+x_moving,y_axis,block);
					for(loop =15;loop>=0;loop--)
					{
						for(neloop=9;neloop>=0;neloop--)
						{
							USART2->DR= printing + (u32) block[loop][neloop];
							Delay(10000);
						}
						USART2->DR = 0x26;
						Delay(10000);
						USART2->DR = 0xA;
						Delay(10000);
					}
					USART2->DR = 0x25;
					Delay(10000);
					USART2->DR = 0xA;
					Delay(10000);
					c = CheckTopLine(block); 
					CheckLine(block, score);
					blocknum = rand()%15 +1;			
					arrive = 0;
					x_moving = 0;	
					y_axis = 260;					
				}
				else
				{
					x_previous = 90+x_moving; 
					IERG3810_DelBlock(90+x_moving, y_axis+16, blocknum);
					IERG3810_DrawBlock(90+x_moving, y_axis, blocknum);
					IERG3810_TFTLCD_FillRectangle(WHITE, 10, 160, 280, 48);
					y_previous=y_axis;
					y_axis -= 16;					
				}				
				draw_Hline(10,260,BLUE,160);
				task2HeartBeat =0;
			}
				
		sheep++;
		if(ps2count >=11)
		{
			if(ps2key == 0x72) //num2 in keyboard (spped up the block, jump one more line)
			{
				if(y_axis>=36)
				{
					if((CheckNextRow(blocknum,90+x_moving,y_axis,block)==0) && (CheckNextRow(blocknum,90+x_moving,y_axis+16,block)==0))
					{
						IERG3810_DelBlock(x_previous, y_previous, blocknum);
						y_axis-=16;
						DisplayArray(block);
					}	
				}
			}
			if(ps2key == 0x6B ) //num4 in keyboard (shift to left)
			{
				if(blocknum >= 3)
				{
					if(90+x_moving>10 && y_axis >=36)
					{
						if((CheckLeftCollision(blocknum,90+x_moving,y_axis,block))==0)
						{
							IERG3810_DelBlock(x_previous, y_axis+16, blocknum);
							x_moving-=16;							
						}
					}
					DisplayArray(block);
				}
				else 
				{
					if(90+x_moving>10 && y_axis >=36 )
					{
						if((CheckLeftCollision(blocknum,90+x_moving,y_axis,block))==0)
						{
							IERG3810_DelBlock(x_previous, y_axis+16, blocknum);
							x_moving-=16;							
						}
						DisplayArray(block);
					}
				}
			}
			if(ps2key == 0x74) //num6 in keyboard (shift to right)
			{
				if (blocknum == 4 || blocknum == 6 || blocknum == 8 || blocknum == 10 || blocknum == 12 || blocknum == 14)
				{
						if(90+x_moving<122 && y_axis >=36 )
						{
							if((CheckRightCollision(blocknum,90+x_moving,y_axis,block))==0)
							{
								IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
								x_moving+=16;								
							}
						}
						DisplayArray(block);
				}
				else if (blocknum == 1 || blocknum == 3)
				{
					if(90+x_moving<154 && y_axis >=36 )
					{
						if((CheckRightCollision(blocknum,90+x_moving,y_axis,block))==0)
						{
							IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
							x_moving+=16;							
						}
					}
					DisplayArray(block);
				}
				else if(blocknum == 2)
				{
					if(90+x_moving<106 && y_axis >=36 )
					{
						if((CheckRightCollision(blocknum,90+x_moving,y_axis,block))==0)
						{
							IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
							x_moving+=16;							
						}
					}
					DisplayArray(block);
				}
				else
				{
					if(90+x_moving<138 && y_axis >=36)
					{
						if((CheckRightCollision(blocknum,90+x_moving,y_axis,block)==0))
						{
							IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
							x_moving+=16;							
						}
					}
					DisplayArray(block);
				}
			}
			if(ps2key == 0x75) //num8 in keyboard (twist the block)
			{
				if(y_axis <=240)
				{
					if(blocknum ==3)
					{
						if(90+ x_moving<106)
						{
							IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
							blocknum = IERG3810_TwistBlock(blocknum);
						}
					}
					else if (blocknum == 5 || blocknum == 7|| blocknum == 9 || blocknum == 11 || blocknum == 13 || blocknum == 15)
					{
						if(90+x_moving <138)
						{
							IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
							blocknum = IERG3810_TwistBlock(blocknum);
						}
					}
					else 
					{
						IERG3810_DelBlock(x_previous, y_axis+16,blocknum);
						blocknum = IERG3810_TwistBlock(blocknum);
					}
					DisplayArray(block);
				}
			}
			ps2key=0;
			ps2count = 0;
			EXTI->PR = 1<<11;
		}
		
		timeout--;		
		if(timeout == 0) 
		{
			timeout = 20000;
			ps2key = 0;
			ps2count = 0;
		} 
	}
	}		
}
