#include "My_include.h"


// 
extern bool MANUAL_FLAG;

void key_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置PB3&PB4为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	
	
	// 配置AFIO复用和EXTI线
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 映射 PA3-EXTI3,PA4-EXTI4
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3); // PA3   EXTI3
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4); // PA4   EXTI4

    // 配置EXTI3&EXTI4为下降沿触发
    EXTI_InitStructure.EXTI_Line = EXTI_Line3 | EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置NVIC(中断优先级根据实际需求设置)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStructure);	
	
	
}

// 中断服务函数
extern char Rx_scanner_temp[rx_buffer_scanner_MAX]; 
extern uchar rx_buffer_scanner[rx_buffer_scanner_MAX];  
extern uint16_t scanner_rx_index;
extern bool key1;
extern int blink_cnt;


uint8_t calculate_xor_checksum(uint8_t *data,uint8_t len){
	uint8_t checksum = 0;
	for(int i = 0; i < len;i++){
		checksum ^= data[i];
	}
	return checksum;
}

static unsigned  is_pressing = 0;
int SerOrSwitch = 0;
int cnt = 0;
void EXTI3_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {					// 下降沿触发and上升沿触发

		
		// 在上升沿触发状态		要结束了
		if(is_pressing == 2){				// 这里进入if就是触发了上升沿判断
			cnt = blink_cnt;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 					// 关闭计时
			if(cnt >= 3){				// >=3s 如果按下时间大于3s 则进入if操作
				SerOrSwitch = 2;
				blink_cnt = 0;
				cnt = 0;
//			    EXTI->RTSR &= ~PB3;      // 关闭上升沿触发
//				EXTI->FTSR |= PB3;       // 开启下降沿触发
			// 改为下降沿触发	
				EXTI_InitTypeDef EXTI_InitStructure;
				EXTI_InitStructure.EXTI_Line = EXTI_Line3;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
				EXTI_Init(&EXTI_InitStructure);	
				EXTI_ClearITPendingBit(EXTI_Line3); // 清除中断标志
				is_pressing = 0;
			}else{					// <3s	若按下时间小于3s,则进入else
				SerOrSwitch = 1;
				blink_cnt = 0;
				cnt = 0;
				blink_cnt = 0;
			// 改为下降沿触发
				EXTI_InitTypeDef EXTI_InitStructure;
				EXTI_InitStructure.EXTI_Line = EXTI_Line3;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
				EXTI_Init(&EXTI_InitStructure);
				EXTI_ClearITPendingBit(EXTI_Line3); // 清除中断标志
				is_pressing = 0;
			}
			// EXTI_InitTypeDef EXTI_InitStructure;							

			return;
		}
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 					// 开始计时
		blink_cnt = 0;
//    	EXTI->FTSR &= ~PB3;			// 关闭下降沿触发
//		EXTI->RTSR |= PB3;   		// 开启上升沿触发
		
		// 初始化上升沿触发
		EXTI_InitTypeDef EXTI_InitStructure;		
		EXTI_InitStructure.EXTI_Line = EXTI_Line3;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		// is_pressing=2表示按下按下的意思
		is_pressing = 2;
		
	
		
        EXTI_ClearITPendingBit(EXTI_Line3); // 清除中断标志
		}
		
//		memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
//		memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
//		scanner_rx_index = 0;
		// USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//??????

 }

// EXTI4??????
void EXTI4_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//??????

		// Send_Continuous_Cmd();
#ifdef DEBUG_PRINT
		uint8_t frame[5];
		frame[0] = 0xAA;    // 帧头
		frame[1] = 0x01;	// 按键类型
		frame[2] = 0x01;	// 按键值
		frame[3] = calculate_xor_checksum(frame,3);		// 异或校验
		frame[4] = 0x0D;	// CR
		for(uint8_t i= 0;i < 5;i++){
		USART_SendData(CH340_UART1,frame[i]);
			while(USART_GetFlagStatus(CH340_UART1, USART_FLAG_TXE) == RESET){
	#ifdef DEBUG_PRINT_2 			
				// printf("Send_Cmd_trig_Cmd_flag_wait...\r\n");
	#endif
			} // 等待发送完成;
		}			

		
		// printf("QC\r");
#endif
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//??????

        // 处理PB4下降沿中断
        EXTI_ClearITPendingBit(EXTI_Line4); // ??????
    }
}

