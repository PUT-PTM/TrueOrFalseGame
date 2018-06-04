/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/




#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "sdmodule.h"
#include "tm_stm32f4_hd44780.h"
#include "stm32f4xx_tim.h"
#include <stdlib.h>
#include <time.h>

//MODIFIED:
int NUMBEROFQUESTIONS = 25;
int already[50];
char dane[48];
char dane2[48];

int true_or_false=0;
int up=0;


UINT loadedBytes;
UINT loadedBytes2;
char* filename;
char* filename2;
int counter_of_already=0;

void init_counter ()
{
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
}

void init_random()
{
	srand(0);

}
void Get_Question()
{
	int true_or_false=rand()%2;
	int random=rand()%NUMBEROFQUESTIONS+1;
	if(true_or_false==0)
	{
		char fn[14];
		sprintf(fn, "TRUE\\%d.txt", random);
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, fn);
}

}

/*void Get_from_SD(char nameoffile)
{
	char* filename = nameoffile;

	SDmodule_ReadFile(filename, &dane, &loadedBytes);
}
*/
int eight_seconds()
{	unsigned int i=1;
	unsigned int dzialaj=1;
	int skonczylem=0;
	TIM_SetCounter(TIM3, 0);
for(;;)
{ if(dzialaj==1)
{	if(TIM_GetCounter(TIM3)==2000 )
	{
		TIM_SetCounter(TIM3, 0);
if(i==1){GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);}
if(i==2){GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);}
if(i==3){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0  | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);}
if(i==4){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 |  GPIO_Pin_5 | GPIO_Pin_6);}
if(i==5){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_1 | GPIO_Pin_2 |  GPIO_Pin_5 | GPIO_Pin_6);}
if(i==6){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_6);}
if(i==7){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_6);}
if(i==8){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_1 | GPIO_Pin_2);}
if(i==9){ GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5); dzialaj=0;}
i++;
	}
}
else {break;}
}
skonczylem = 1;
return skonczylem;
}


int main(void)
{



RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

// tworzenie strutkury
GPIO_InitTypeDef  GPIO_InitStructure;

// wypelnianie struktury nanymi
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOD, &GPIO_InitStructure);

GPIO_InitTypeDef Przyciski;
Przyciski.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
Przyciski.GPIO_Mode = GPIO_Mode_IN;
Przyciski.GPIO_OType = GPIO_OType_PP;
Przyciski.GPIO_Speed = GPIO_Speed_100MHz;
Przyciski.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &Przyciski);

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 101 - 1;
		TIM_TimeBaseStructure.TIM_Prescaler = 420 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


TIM_TimeBaseStructure.TIM_Prescaler = 42000;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period = 2000 ;
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
TIM_Cmd(TIM3, ENABLE);


/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOE, &GPIO_InitStructure);



SDmodule_Configuration();
init_counter();
char fn[14];
int random=0;
true_or_false=rand()%2;
random=rand()%NUMBEROFQUESTIONS+1;

int pos=0;
do{
	if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
	{

if(pos==0) {

	sprintf(fn, "FALSE\\%d.txt", random);
						filename2 = fn;
						SDmodule_ReadFile(filename2, &dane2, &loadedBytes2);
						TM_HD44780_Init(24,4);
						TM_HD44780_Clear();
						TM_HD44780_Puts(0, 0, dane2);


}
if(pos==1){

					sprintf(fn, "TRUE\\%d.txt", random);
					filename = fn;
					SDmodule_ReadFile(filename, &dane, &loadedBytes);
					TM_HD44780_Init(24,4);
					TM_HD44780_Clear();
					TM_HD44780_Puts(0, 0, "TEST");

}
pos++;
			Delayms(150);
	}

}while(1);
/*	int true_or_false=rand()%2;
	int random;
	random=rand()%NUMBEROFQUESTIONS+1;
	if(true_or_false==0)
	{
		char fn[14];
		sprintf(fn, "TRUE\\%d.txt", random);
		filename = fn;
		SDmodule_ReadFile(filename, &dane, &loadedBytes);
		TM_HD44780_Init(24,4);
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, dane);
}
	if(true_or_false==1)
		{
			char fn[14];
			sprintf(fn, "FALSE\\%d.txt", random);
			filename = fn;
			SDmodule_ReadFile(filename, &dane, &loadedBytes);
			TM_HD44780_Init(24,4);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, dane);
	}

	/*
int i=9;
char fn[14];
sprintf(fn, "TRUE\\%d.txt", i);
char* filename = fn;
UINT loadedBytes;
char dane[48];
SDmodule_ReadFile(filename, &dane, &loadedBytes);
TM_HD44780_Init(24,4);
TM_HD44780_Clear();
TM_HD44780_Puts(0, 0, dane);
*/





do{
		if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
		{
			int pomoc=eight_seconds();
					if(pomoc==1)
				{	GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
					//module_ReadFile(filename, &dane, &loadedBytes);
					TM_HD44780_Clear();
					TM_HD44780_Puts(0, 0, "witaj");
				}
		}
		if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
		{
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, "2");
		}
		Delayms(150);

	}while(1);


}

