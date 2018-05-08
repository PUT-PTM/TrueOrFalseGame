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
#include "stm32f4_discovery.h"


int main(void)
{

	//LCD

	// Structures to hold the initialisation data
	    GPIO_InitTypeDef GPIO_InitStruct;
	    USART_InitTypeDef USART_InitStruct;

	    // enable the peripherals we're going to use
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	    // Usart1 Tx is on GPIOB pin 6 as an alternative function
	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	    GPIO_Init(GPIOB, &GPIO_InitStruct);

	    // Connect pin 6 to the USART
	    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

	    // init the USART to 8:N:1 at 9600 baud as specified in the
	    // SerLCD data sheet
	    USART_InitStruct.USART_BaudRate = 9600;
	    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	    USART_InitStruct.USART_StopBits = USART_StopBits_1;
	    USART_InitStruct.USART_Parity = USART_Parity_No;
	    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	    USART_InitStruct.USART_Mode = USART_Mode_Tx;
	    USART_Init(USART1, &USART_InitStruct);

	    // Enable USART1 peripheral
	    USART_Cmd(USART1, ENABLE);

	    // Clear the screen using the commands specified in the SerLCD data sheet.
	    // The while loops test the 'Transmission Complete' flag in the USART
	    // status register to make sure the previous character has gone before
	    // sending the next one.
	    while( !(USART1->SR & USART_SR_TC) );
	    USART_SendData(USART1, 0xfe);

	    while( !(USART1->SR & USART_SR_TC) );
	    USART_SendData(USART1, 0x01);

	    // something to display
	    char* messageText = "Testing 1 2 3";

	    // index into the display string
	    int i = 0;

	    // display the message
	    while (i < strlen(messageText))
	    {
	        while( !(USART1->SR & USART_SR_TC) );
	        USART_SendData(USART1, messageText[i]);
	        i++;
	    }

	    // Infinite loop
	    while (1){}
}
