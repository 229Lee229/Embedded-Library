#ifndef __MY_INCLUDE_H
#define __MY_INCLUDE_H

#define rx_buffer_scanner_MAX  2048

#define STATUS_LED_GREEN_ON()			PAout(15) = 0
#define STATUS_LED_GREEN_OFF()			PAout(15) = 1


#define CH340_UART1					USART1
#define SCANNER_UART2				USART2
#define CH340_UART1_Init(n) 		Usart1_Init(n);
#define SCANNER_UART2_Init(n)		Usart2_Init(n);

#define  uchar unsigned char
#include "stm32f10x.h"                  // Device header


#include "OLED.h"
#include "Delay.h"
#include "Matrix_Key2.h"
#include "MyGPIO.h"
#include "usart.h"
#include "SysBitBand.h"


#include "stdbool.h"
#include "scanner.h"
#include "scanner_cmd.h"
#include "Debug_cmd.h"
#include "key.h"
#include "LED_State.h"
#endif
