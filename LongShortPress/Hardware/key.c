#include "My_include.h"


// 
extern bool MANUAL_FLAG;

void key_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // ����PB3&PB4Ϊ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	
	
	// ����AFIO���ú�EXTI��
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // ʹ��AFIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // ӳ�� PA3-EXTI3,PA4-EXTI4
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3); // PA3   EXTI3
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4); // PA4   EXTI4

    // ����EXTI3&EXTI4Ϊ�½��ش���
    EXTI_InitStructure.EXTI_Line = EXTI_Line3 | EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // ����NVIC(�ж����ȼ�����ʵ����������)
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStructure);	
	
	
}

// �жϷ�����
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
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {					// �½��ش���and�����ش���

		
		// �������ش���״̬		Ҫ������
		if(is_pressing == 2){				// �������if���Ǵ������������ж�
			cnt = blink_cnt;
			TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE); 					// �رռ�ʱ
			if(cnt >= 3){				// >=3s �������ʱ�����3s �����if����
				SerOrSwitch = 2;
				blink_cnt = 0;
				cnt = 0;
//			    EXTI->RTSR &= ~PB3;      // �ر������ش���
//				EXTI->FTSR |= PB3;       // �����½��ش���
			// ��Ϊ�½��ش���	
				EXTI_InitTypeDef EXTI_InitStructure;
				EXTI_InitStructure.EXTI_Line = EXTI_Line3;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
				EXTI_Init(&EXTI_InitStructure);	
				EXTI_ClearITPendingBit(EXTI_Line3); // ����жϱ�־
				is_pressing = 0;
			}else{					// <3s	������ʱ��С��3s,�����else
				SerOrSwitch = 1;
				blink_cnt = 0;
				cnt = 0;
				blink_cnt = 0;
			// ��Ϊ�½��ش���
				EXTI_InitTypeDef EXTI_InitStructure;
				EXTI_InitStructure.EXTI_Line = EXTI_Line3;
				EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
				EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
				EXTI_InitStructure.EXTI_LineCmd = ENABLE;
				EXTI_Init(&EXTI_InitStructure);
				EXTI_ClearITPendingBit(EXTI_Line3); // ����жϱ�־
				is_pressing = 0;
			}
			// EXTI_InitTypeDef EXTI_InitStructure;							

			return;
		}
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 					// ��ʼ��ʱ
		blink_cnt = 0;
//    	EXTI->FTSR &= ~PB3;			// �ر��½��ش���
//		EXTI->RTSR |= PB3;   		// ���������ش���
		
		// ��ʼ�������ش���
		EXTI_InitTypeDef EXTI_InitStructure;		
		EXTI_InitStructure.EXTI_Line = EXTI_Line3;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		// is_pressing=2��ʾ���°��µ���˼
		is_pressing = 2;
		
	
		
        EXTI_ClearITPendingBit(EXTI_Line3); // ����жϱ�־
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
		frame[0] = 0xAA;    // ֡ͷ
		frame[1] = 0x01;	// ��������
		frame[2] = 0x01;	// ����ֵ
		frame[3] = calculate_xor_checksum(frame,3);		// ���У��
		frame[4] = 0x0D;	// CR
		for(uint8_t i= 0;i < 5;i++){
		USART_SendData(CH340_UART1,frame[i]);
			while(USART_GetFlagStatus(CH340_UART1, USART_FLAG_TXE) == RESET){
	#ifdef DEBUG_PRINT_2 			
				// printf("Send_Cmd_trig_Cmd_flag_wait...\r\n");
	#endif
			} // �ȴ��������;
		}			

		
		// printf("QC\r");
#endif
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//??????

        // ����PB4�½����ж�
        EXTI_ClearITPendingBit(EXTI_Line4); // ??????
    }
}

