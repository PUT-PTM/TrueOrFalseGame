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


int bylo=0;
int question_to_display;
int NUMBEROFQUESTIONS = 25;
int already_TRUE[25];
int already_FALSE[25];
int true_or_false=0;

int counter_of_already_TRUE=0;
int counter_of_already_FALSE=0;

char TRUE[25][48]={
"Powierzchnia Polski wynosi ponad 312000 km^2.",
"Weta to najwiekszy owad swiata.",
"Watykan to najmniejszy kraj na swiecie.",
"Dlugosc rownika wynosi 40 075km.",
"Podczas snu zmysl wechu jest wylaczony.",
"Cialo noworodka w okolo 75% sklada sie z wody.",
"Slonie afrykanskie spia na stojaco.",
"Mastaba to pierwowzor piramidy.",
"Jan Pawel I byl papierzem przez 33 dni.",
"Zaden ptak oprocz strusia nie posiada pecherza.",
"Czomolungma to najwyzszy szczyt na swiecie.",
"Majorka to wyspa hiszpanska.",
"Biedronka to gatunek chrzaszcza.",
"Delfin jest ssakiem.",
"Komodo to wyspa lezaca w Azji.",
"Adam Mickiewicz mial 4 braci.",
"Poznanskie koziolki to Pyrek i Tyrek.",
"Nie wszystkie sowy maja uszy.",
"Ogry sa jak cebula.",
"1117 to liczba pierwsza.",
"Kosc promieniowa znajduje sie w rece.",
"Cis jest drzewem iglastym.",
"Buzuki to strunowy instrument muzyczny.",
"Metan to staly skladnik powietrza.",
"Szczupak ma ponad 600 zebow.",
};

char FALSE[25][48]={
"Dunaj to najdluzsza rzeka w Europie.",
"Chrzest Polski odbyl sie w 996 roku.",
"Rysy to najwyzszy szczyt w tatrach.",
"Jednym z uczniow Arystotelesa byl Platon.",
"Frytki pochodza z USA.",
"Stonka ziemniaczana wystepuje tylko w Europie.",
"Na swiecie zyje ponad 20 gatunkow pingwinow.",
"Pierogi ruskie pochodza z Rosji.",
"Krokodyle to plazy.",
"Foccacia to tradycyjne wloskie pierogi.",
"Glonojad to afrykanska jaszczurka.",
"Cytra to napoj z cytrusow.",
"Szachy wymyslili starozytni egipcjanie.",
"1 galon to dokladnie 4 litry.",
"Brajan to imie slowianskie.",
"Kot z polibudy jest bialy.",
"Calkowita wysokosc Wiezy Eiffla to 342 m.",
"Belona to gatunek motyla.",
"Epifit to gatunek tropikalnego owada.",
"Kat ostry moze miec 100 stopni.",
"Symbol chemiczny cynku to Sn.",
"Rownik kuli ziemskiej ma ponad 45000 km.",
"Najwieksze miasto swiata to Nowy Jork.",
"Boleslaw Krzywy byl jednym z wladcow polski.",
"Dniepr to miasto w Rosji.",
};

int Question_Control_TRUE()
{
		int old_question=0;
		int random_number=0;

		if(counter_of_already_TRUE!=0)
				{
		do{

			random_number=rand()%NUMBEROFQUESTIONS+1;

			for(int i=0;i<counter_of_already_TRUE;i++)
		{
			if(already_TRUE[i]==random_number)
			{old_question=1; }
		}
		}
		while(old_question!=1);
				}
		if(counter_of_already_TRUE==0)
		{random_number=rand()%NUMBEROFQUESTIONS+1;}
		already_TRUE[counter_of_already_TRUE]=random_number;
		return random_number;
		counter_of_already_TRUE++;
}

int Question_Control_FALSE()
{
	int old_question=0;
	int random_number=0;

	if(counter_of_already_FALSE>0)
			{
	do{

		random_number=rand()%NUMBEROFQUESTIONS+1;

		for(int i=0;i<counter_of_already_FALSE;i++)
	{
		if(already_FALSE[i]==random_number)
		{old_question=1; }
	}
	}
	while(old_question!=1);
			}

	if(counter_of_already_FALSE==0)
	{random_number=rand()%NUMBEROFQUESTIONS+1;}

	already_FALSE[counter_of_already_FALSE]=random_number;
	counter_of_already_FALSE++;
	return random_number;
}

void Get_Question()
{


	true_or_false=rand()%2;

	if(true_or_false==0)
	{
	question_to_display = Question_Control_FALSE();
	TM_HD44780_Init(24,4);
	TM_HD44780_Clear();
	TM_HD44780_Puts(0, 0, FALSE[question_to_display]);}

	if(true_or_false==1)
	{
	question_to_display = Question_Control_TRUE();
	TM_HD44780_Init(24,4);
	TM_HD44780_Clear();
	TM_HD44780_Puts(0, 0, TRUE[question_to_display]);}

}



void init_counter ()
{
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6);
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
srand(0);
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


srand(0);

init_counter();
//SDmodule_Configuration();


do{
	if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			Get_Question();
			Delayms(150);
			bylo++;
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

