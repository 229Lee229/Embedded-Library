#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "string.h"


#define USART1_REC_LEN			200				/* Define the maximum number of received bytes  */
#define EN_USART1_RX			1				/* ENABLE(1)  |  DISENABLE(0) Serial Port 1 */
extern u8 USART1_RX_BUF[USART1_REC_LEN];		/* 接收缓冲 最大usart_rec_len个字节, 末字节为换行符 */
extern u16 USART1_RX_STA;						/* 接收状态标记 */
void Usart1_Init(u32 bound);


#define USART2_REC_LEN			200				/* Define the maximum number of received bytes  */
#define EN_USART2_RX			1				/* ENABLE(1)  |  DISENABLE(0) Serial Port 1 */
extern u8 USART2_RX_BUF[USART2_REC_LEN];		/* 接收缓冲 最大usart_rec_len个字节, 末字节为换行符 */
extern u16 USART2_RX_STA;						/* 接收状态标记 */
void Usart2_Init(u32 bound);

#define USART3_REC_LEN			200				/* Define the maximum number of received bytes  */
#define EN_USART3_RX			1				/* ENABLE(1)  |  DISENABLE(0) Serial Port 1 */
extern u8 USART3_RX_BUF[USART3_REC_LEN];		/* 接收缓冲 最大usart_rec_len个字节, 末字节为换行符 */
extern u16 USART3_RX_STA;						/* 接收状态标记 */
void Usart3_Init(u32 bound);



void USART_SendString(USART_TypeDef* USARTx, char *DataString);
#endif
