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


int WHAT_NOW=0;
int question_to_display;
int NUMBEROFQUESTIONS = 25;
int already_TRUE[25];
int already_FALSE[25];
int order_TRUE[25];
int order_FALSE[25];
int true_or_false=0;
int end=0;
int after=0;
int ANSWER = 0;
unsigned int counter_work=1;
int clicked=0;
int game_on=1;
int lost=0;
int control =1;
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

void generate_order()
{
	for (int i = 0; i < NUMBEROFQUESTIONS; i++)
		{     // fill array
			order_TRUE[i] = i;
			order_FALSE[i] = i;
		}

/*	for (int i = 0; i < NUMBEROFQUESTIONS; i++)
		{    // shuffle array

		int temp_FALSE = order_FALSE[i];
		int temp_TRUE = order_TRUE[i];

		int randomIndex = rand() % NUMBEROFQUESTIONS;

		order_TRUE[i] = order_TRUE[randomIndex];
		order_TRUE[randomIndex] = temp_TRUE;

		order_FALSE[i] = FALSE[randomIndex];
		order_FALSE[randomIndex] = temp_FALSE;

		}
*/

		}


int Question_Control_TRUE()
{		WHAT_NOW=1;
		counter_of_already_TRUE++;
		return order_TRUE[counter_of_already_TRUE-1];

}

int Question_Control_FALSE()
{
	WHAT_NOW=0;
	counter_of_already_FALSE++;
	return order_FALSE[counter_of_already_FALSE-1];

}

void Get_Question()
{

	if(counter_of_already_FALSE==NUMBEROFQUESTIONS&&counter_of_already_TRUE==NUMBEROFQUESTIONS)
		{
			TM_HD44780_Init(24,4);
						TM_HD44780_Clear();
						TM_HD44780_Puts(0, 0, "KONIEC PYTAN. WYGRALES/AS!!!");
						end=1;
		}

if(end!=1){
	if(counter_of_already_TRUE>=NUMBEROFQUESTIONS)
	{
		question_to_display = Question_Control_FALSE();
			TM_HD44780_Init(24,4);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, FALSE[question_to_display]);
	}

	if(counter_of_already_FALSE>=NUMBEROFQUESTIONS)
	{
		question_to_display = Question_Control_TRUE();
			TM_HD44780_Init(24,4);
			TM_HD44780_Clear();
			TM_HD44780_Puts(0, 0, TRUE[question_to_display]);
	}


	else {

		true_or_false=rand()%2;

	if(true_or_false==0)
	{
	question_to_display = Question_Control_FALSE();
	TM_HD44780_Init(24,4);
	TM_HD44780_Clear();
	TM_HD44780_Puts(0, 0, FALSE[question_to_display]);
	}

	if(true_or_false==1)
	{
	question_to_display = Question_Control_TRUE();
	TM_HD44780_Init(24,4);
	TM_HD44780_Clear();
	TM_HD44780_Puts(0, 0, TRUE[question_to_display]);}
	}
}
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
	counter_work=1;
	int fin=0;
	TIM_SetCounter(TIM3, 0);
ANSWER=-1;
for(;;)
{;
	if(counter_work==1)
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
GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |  GPIO_Pin_5); counter_work=0;}
i++;
	}
}
else {break;}
}
fin = 1;
return fin;
}



void EXTI1_IRQHandler(void)
{
             if(EXTI_GetITStatus(EXTI_Line1) != RESET)
             {
            	 ANSWER=1;


// wyzerowanie flagi wyzwolonego przerwania
            	 EXTI_ClearITPendingBit(EXTI_Line1);
              }
}

void EXTI2_IRQHandler(void)
{
             if(EXTI_GetITStatus(EXTI_Line2) != RESET)
             {
            	 ANSWER=0;



// wyzerowanie flagi wyzwolonego przerwania
            	 EXTI_ClearITPendingBit(EXTI_Line2);
              }
}

void GAME_LOST()
{
	TM_HD44780_Init(24,4);
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "PRZEGRALES/AS! SPROBUJ  PONOWNIE.");
		do{
			if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
			{game_on=0;break;}
		}
			while(1);

}
void GAME_CONTINUE()
{
	TM_HD44780_Init(24,4);
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0, "POPRAWNA ODPOWIEDZ! NACISNIJ TRUE.");

}

int main(void)
{

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);






NVIC_InitTypeDef NVIC_InitStructure;
// numer przerwania
NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
// priorytet główny
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
// subpriorytet
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
// uruchom dany kanał
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// zapisz wypełnioną strukturę do rejestrów
NVIC_Init(&NVIC_InitStructure);

EXTI_InitTypeDef EXTI_InitStructure;
// wybór numeru aktualnie konfigurowanej linii przerwań
EXTI_InitStructure.EXTI_Line = EXTI_Line1;
// wybór trybu - przerwanie bądź zdarzenie
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
// wybór zbocza, na które zareaguje przerwanie
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
// uruchom daną linię przerwań
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
// zapisz strukturę konfiguracyjną przerwań zewnętrznych do rejestrów
EXTI_Init(&EXTI_InitStructure);
SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

NVIC_InitTypeDef NVIC_InitStructure2;
// numer przerwania
NVIC_InitStructure2.NVIC_IRQChannel = EXTI2_IRQn;
// priorytet główny
NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
// subpriorytet
NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
// uruchom dany kanał
NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
// zapisz wypełnioną strukturę do rejestrów
NVIC_Init(&NVIC_InitStructure2);

EXTI_InitTypeDef EXTI_InitStructure2;
// wybór numeru aktualnie konfigurowanej linii przerwań
EXTI_InitStructure2.EXTI_Line = EXTI_Line2;
// wybór trybu - przerwanie bądź zdarzenie
EXTI_InitStructure2.EXTI_Mode = EXTI_Mode_Interrupt;
// wybór zbocza, na które zareaguje przerwanie
EXTI_InitStructure2.EXTI_Trigger = EXTI_Trigger_Rising;
// uruchom daną linię przerwań
EXTI_InitStructure2.EXTI_LineCmd = ENABLE;
// zapisz strukturę konfiguracyjną przerwań zewnętrznych do rejestrów
EXTI_Init(&EXTI_InitStructure2);
SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);



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


srand(3);
init_counter();

SDmodule_Configuration();


char dane[48];
UINT loadedBytes;
char* filename="WELCOME.TXT";

SDmodule_ReadFile(filename, &dane, &loadedBytes);


//GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
//GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

do{
TM_HD44780_Init(24,4);
TM_HD44780_Clear();
TM_HD44780_Puts(0, 0, dane);
counter_of_already_TRUE=0;
counter_of_already_FALSE=0;
generate_order();
game_on=1;
do{
	if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
	{	ANSWER=-1;
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			Get_Question();

			eight_seconds();
			Delayms(150);
			if(ANSWER==-1){GPIO_SetBits(GPIOD, GPIO_Pin_14); GAME_LOST();}
			else{
			if(WHAT_NOW==1&&ANSWER==1){GPIO_SetBits(GPIOD, GPIO_Pin_12); GAME_CONTINUE();}
			if(WHAT_NOW==0&&ANSWER==0){GPIO_SetBits(GPIOD, GPIO_Pin_12); GAME_CONTINUE();}
			if(WHAT_NOW==1&&ANSWER==0){GPIO_SetBits(GPIOD, GPIO_Pin_14); GAME_LOST();}
			if(WHAT_NOW==0&&ANSWER==1){GPIO_SetBits(GPIOD, GPIO_Pin_14); GAME_LOST();}
			}
control=1;
	}



}while(game_on!=0);
}while(1);


}

