#include "My_include.h"

// unsigned rx_buffer_scanner_MAX = 2048;
uchar rx_buffer_scanner[rx_buffer_scanner_MAX];  
char Rx_scanner_temp[rx_buffer_scanner_MAX]; 

uchar rx_buffer_ch340[rx_buffer_scanner_MAX];
char Rx_ch340_temp[rx_buffer_scanner_MAX];


uint16_t scanner_rx_index = 0;
uint16_t ch340_rx_index = 0;
bool data_REC_scanner_Flag;
bool data_REC_ch340_Flag;

extern char *AT_CONTINUOUS_Str;
extern char *AT_MANUAL_Str;
extern char *AT_ReadDeviceID_Str;

volatile uint8_t Manual_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x00,0xD4,0xAB,0xCD};
volatile uint8_t Continuous_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x00,0xD6,0xAB,0xCD};
volatile uint8_t Single_time_25s_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x06,0xFE,0xAB,0xCD};
volatile uint8_t Signle_time_15s_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x06,0x9B,0xAB,0xCD};
// volatile uint8_t Cmd_trig_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x00,0xD5,0xAB,0xCD};
volatile uint8_t Cmd_trig_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x00,0xD5,0xEF,0x41};

// volatile uint8_t Cmd_trig_ON_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};
volatile uint8_t Cmd_trig_ON_Cmd[] = {0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0x02,0xDA};

volatile char *ReadDeviceId = "ReadDeviceID.";

extern bool Scan_Data_Flag;

extern volatile int blink_cnt;
extern bool MANUAL_FLAG;

// 发送命令触发模式指令
void Send_Cmd_trig_ON_Cmd(void){
	for(uint16_t i= 0;i < 9;i++){
		USART_SendData(SCANNER_UART2,Cmd_trig_ON_Cmd[i]);
		while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
#ifdef DEBUG_PRINT_2
			printf("Send_Cmd_trig_ON_flag_wait...\r\n");
#endif			
		} // 等待发送完成;
	}
}


// 发送手动模式指令
void Send_Manual_Cmd(void){
	for(uint16_t i= 0;i < 9;i++){
		USART_SendData(SCANNER_UART2,Manual_Cmd[i]);
		while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
#ifdef DEBUG_PRINT
			printf("Send_Manual_flag_wait...\r\n");
#endif			
		} // 等待发送完成;
	}
}

// 发送连续模式指令
void Send_Continuous_Cmd(void){
	for(uint16_t i= 0;i < 9;i++){
		USART_SendData(SCANNER_UART2,Continuous_Cmd[i]);
		while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
#ifdef DEBUG_PRINT_2 			
			printf("Send_Continuous_flag_wait...\r\n");
#endif
		} // 等待发送完成;
	}
}

// 发送读取scannerID指令   SN MID FID
void Send_ReadDeviceID_Cmd(void){
	for (uint16_t i = 0; ReadDeviceId[i] != '\0'; i ++)
	{
		USART_SendData(SCANNER_UART2,ReadDeviceId[i]);
		while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
#ifdef DEBUG_PRINT 				
			// printf("Send_ReadID_flag_wait...\r\n");
#endif			
		} // 等待发送完成;
	}
	
}

// 发送设置单次试读时长15s
void Send_Single_Cmd(int second){
	
	switch(second){
		case 25:
				for(uint16_t i= 0;i < 9;i++){
					USART_SendData(SCANNER_UART2,Single_time_25s_Cmd[i]);
					while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
			#ifdef DEBUG_PRINT 			
						printf("Send_Single_time_25s_Cmd_flag_wait...\r\n");
			#endif
					} // 等待发送完成;
				}	
				break;
		case 15:
				for(uint16_t i= 0;i < 9;i++){
					USART_SendData(SCANNER_UART2,Signle_time_15s_Cmd[i]);
					while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
			#ifdef DEBUG_PRINT 			
						printf("Send_Single_time_15s_Cmd_flag_wait...\r\n");
			#endif
					} // 等待发送完成;
				}				
			break;
//		case 5:
//				for(uint16_t i= 0;i < 9;i++){
//					// USART_SendData(SCANNER_UART2,Signle_time_5s_Cmd[i]);
//					while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
//			#ifdef DEBUG_PRINT 			
//						printf("Send_Single_time_5s_Cmd_flag_wait...\r\n");
//			#endif
//					} // 等待发送完成;
//				}				
//				break;
		default:
				for(uint16_t i= 0;i < 9;i++){
					USART_SendData(SCANNER_UART2,Signle_time_15s_Cmd[i]);
					while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
			#ifdef DEBUG_PRINT 			
						printf("Send_Single_time_15s_Cmd_flag_wait...\r\n");
			#endif
					} // 等待发送完成;
				}	
	}
}

// 发送设置命令触发模式(可以说是手动触发,按键按下,MCU发送命令触发)
void Send_Cmd_trig_Cmd(void){
	for(uint16_t i= 0;i < 9;i++){
		USART_SendData(SCANNER_UART2,Cmd_trig_Cmd[i]);
		while(USART_GetFlagStatus(SCANNER_UART2, USART_FLAG_TXE) == RESET){
#ifdef DEBUG_PRINT_2 			
			printf("Send_Cmd_trig_Cmd_flag_wait...\r\n");
#endif
		} // 等待发送完成;
	}	
	
	
}


void Handle_RX_Scanner(void){   		// 处理接收到的scanner数据,并将数据传给usart1
			// USART_Cmd(USART2,DISABLE);// 等传输完数据在使能串口
#ifdef DEBUG_PRINT			
			// printf("Identification successful!\r\n");
#endif
	
	
			if(Scan_Data_Flag == true){
				char Scan_Data[1048];
				sprintf(Scan_Data,"CODE_DATA:%s",(char *)Rx_scanner_temp);
				Delay_us(1);
				printf("%s",(char *)Scan_Data);

				memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
				memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
				scanner_rx_index = 0;
				
				data_REC_scanner_Flag = false;		
				Scan_Data_Flag = false;				
				return;
			}
			printf("%s",(char *)Rx_scanner_temp);			// 这种是什么情况
			// 打印完数据后 清除数组数据和索引数据
			memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
			memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
			scanner_rx_index = 0;
			
			data_REC_scanner_Flag = false;
			// USART_Cmd(USART2,ENABLE);// 已处理数据 使能串口	
	
}

void Handle_RX_CH340(void){
	// AT_CONTINUOUS 核对是否正确
	if(strcmp(Rx_ch340_temp,AT_CONTINUOUS_Str) == 0){			// AT_CONTINUOUS如果核对正确,则发送指令
		// 发送指令
		Send_Continuous_Cmd();
		MANUAL_FLAG = false;				// 当收到连续模式的指令后, 手动模式即失能, 按键恢复发送NG指令
#ifdef	DEBUG_PRINT
		printf("CONTINUOUS_MATCH!\r\n");
#endif
//		PAout(15) = 0;
//		PBout(9) = 1;
		
		Delay_ms(100);
			memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
			memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
			scanner_rx_index = 0;
			
			data_REC_scanner_Flag = false;
	}
	// AT_MANUAL 核对是否正确
	else if(strcmp(Rx_ch340_temp,AT_MANUAL_Str) == 0){
		// 发送指令
		// Send_Manual_Cmd();
		Send_Cmd_trig_Cmd();
		for(int i  = 0; i <= 5555;i++){
			;
		}
		MANUAL_FLAG = true;				// 当收到手动模式的指令后, 手动模式即使能, 按键恢复点控功能
		
		// Send_Cmd_trig_ON_Cmd();
#ifdef	DEBUG_PRINT
		printf("MANUAL_MATCH!\r\n");
#endif
//		PBout(9) = 0;
//		PAout(15) = 1;
				Delay_ms(100);
			memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
			memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
			scanner_rx_index = 0;
			
			data_REC_scanner_Flag = false;
	}
	
	// AT_ReadDeviceID_Str 核对是否正确
	else if(strcmp(Rx_ch340_temp,AT_ReadDeviceID_Str) == 0){
		Send_ReadDeviceID_Cmd();
		// printf("ID_MATCH!\r\n");		
		for(int i = 0;i <= 5555;i++){
			;
		}
		Delay_ms(100);
				Delay_ms(100);

	}
	else{	
	
	
		printf(":%s.",rx_buffer_ch340);
#ifdef DEBUG_PRINT
	// printf("NOT_MATCH\r\n");
#endif
	}
	memset(rx_buffer_ch340, 0, sizeof(rx_buffer_ch340));	
	memset(Rx_ch340_temp, 0, sizeof(Rx_ch340_temp));
	ch340_rx_index = 0;
	data_REC_ch340_Flag = false;
}

extern bool key1;

void USART1_IRQHandler(void){
	if(USART_GetITStatus(CH340_UART1,USART_IT_RXNE) != RESET){
		uint8_t Rx_temp = USART_ReceiveData(CH340_UART1);
		
		
		

		
		
		if(ch340_rx_index >= sizeof(rx_buffer_ch340)){
            ch340_rx_index = 0; //防止串口被刷爆			
		}
		rx_buffer_ch340[ch340_rx_index++] = Rx_temp;		
		if(ch340_rx_index >= 2 && (rx_buffer_ch340[ch340_rx_index-1] == '\r')/* && rx_buffer_scanner[scanner_rx_index-1] == '\n'*/ ){			// 收集到的字符结束
			strcpy(Rx_ch340_temp,(char *)rx_buffer_ch340); // 将结果复制到中间变量
			data_REC_ch340_Flag = true;
		}

		USART_ClearITPendingBit(CH340_UART1, USART_IT_RXNE);
	}
	
}


void USART2_IRQHandler(void) {
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
        uint8_t Rx_temp = USART_ReceiveData(USART2);
//		if(key1 == true){
//			printf("\r\n%c\r\n:",Rx_temp);
//			
//		}
		if(scanner_rx_index >= sizeof(rx_buffer_scanner))
            scanner_rx_index = 0; //防止串口被刷爆
		
		rx_buffer_scanner[scanner_rx_index++] = Rx_temp;
		// 返回指令
		if(rx_buffer_scanner[scanner_rx_index-7] == 0x02 \
			&&rx_buffer_scanner[scanner_rx_index-6] == 0x00 &&rx_buffer_scanner[scanner_rx_index-5] == 0x00 \
			&& rx_buffer_scanner[scanner_rx_index-4] == 0x01 &&rx_buffer_scanner[scanner_rx_index-3] == 0x00 \
			&&rx_buffer_scanner[scanner_rx_index-2] == 0x33 && rx_buffer_scanner[scanner_rx_index-1] == 0x31){
			// 若返回指令正确,则删除该缓存的指令,避免影响后续接收数据
			memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
			memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
			scanner_rx_index = 0;
		}
		// 正常数据
		else if(scanner_rx_index >= 2 && ((rx_buffer_scanner[scanner_rx_index-1] == '\r') || (rx_buffer_scanner[scanner_rx_index-1] == '.'))/* && rx_buffer_scanner[scanner_rx_index-1] == '\n'*/ ){			// 收集到的字符结束
			strcpy(Rx_scanner_temp,(char *)rx_buffer_scanner); // 将结果复制到中间变量
			if((rx_buffer_scanner[scanner_rx_index-1] == '\r') == true){
				Scan_Data_Flag = true;
			}
			
			data_REC_scanner_Flag = true;

#ifdef   DEBUG_PRINT			
			PBout(9) = 1;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 
			blink_cnt = 0;
			key1 = false;
#endif			
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

//void USART2_IRQHandler(void) {
//    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
//        char Rx_c = USART_ReceiveData(USART2);
//		if(scanner_rx_index >= sizeof(rx_buffer_scanner))
//            scanner_rx_index = 0; //防止串口被刷爆
//		
//		rx_buffer_scanner[scanner_rx_index++] = Rx_c;
//		if(rx_buffer_scanner[scanner_rx_index-1] == '\r'){			// 收集到的字符结束
//			strcpy(Rx_scanner_temp,(char *)rx_buffer_scanner); // 将结果复制到中间变量
//			data_REC_scanner_Flag = true;
//		}
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	}
//}
