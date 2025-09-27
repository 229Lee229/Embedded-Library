#include "stm32f10x.h"                  // Device header
#include "My_include.h"

// ���ջ���
extern char Rx_scanner_temp[rx_buffer_scanner_MAX]; 
extern uchar rx_buffer_scanner[rx_buffer_scanner_MAX];  
extern char Rx_ch340_temp[rx_buffer_scanner_MAX];
extern uchar rx_buffer_ch340[rx_buffer_scanner_MAX];

// �����ַ�������
extern uint16_t scanner_rx_index;
extern uint16_t ch340_rx_index;

// ���ձ�־λ
extern bool data_REC_scanner_Flag;
extern bool data_REC_ch340_Flag;

// �ֶ���־λ(Ĭ�Ͽ���)
bool MANUAL_FLAG = true;

bool key1 = false;
extern int SerOrSwitch;

// ɨ�����ݱ�־λ
bool Scan_Data_Flag = false;
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);			// ȡ��PB3 PB4 PA15��JTAGģʽ ��Ϊ��ͨIO

	SCANNER_UART2_Init(9600);
	CH340_UART1_Init(115200);

	Send_Manual_Cmd();

	// Send_Continuous_Cmd();
	// ������ʼ��
	key_Init();
	LED_State_Init();
	STATUS_LED_GREEN_ON();			// ״̬�� �͵�ƽ����
	// Send_Single_Cmd(15);
	// Send_ReadDeviceID_Cmd();
	Send_Cmd_trig_Cmd();
	// Delay_ms(50);
	// Send_Manual_Cmd();

	Delay_ms(100);
	// ���������
	memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
	memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
	scanner_rx_index = 0;
	data_REC_scanner_Flag = false;
	
#ifdef DEBUG_PRINT	
	printf("Initialization Successful!\r\n");
#endif	
	while(1){
		if(SerOrSwitch == 1){
			printf("Switch universe\r\n");
			SerOrSwitch = 0;
		}else if(SerOrSwitch == 2){
			printf("Set address\r\n");
			SerOrSwitch = 0;

		}
		if(data_REC_scanner_Flag == true){
			Handle_RX_Scanner();
		}
		if(data_REC_ch340_Flag == true){
			Handle_RX_CH340();
		}
//		if(key1 == true && data_REC_scanner_Flag == false){
//			memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
//			memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
//			scanner_rx_index = 0;	
//		}
//		if(	scanner_rx_index != 0){
//			printf("%s",rx_buffer_scanner);
//				memset(rx_buffer_scanner, 0, sizeof(rx_buffer_scanner));	
//	memset(Rx_scanner_temp, 0, sizeof(Rx_scanner_temp));	
//	scanner_rx_index = 0;
//		}
		// printf("%s",rx_buffer_ch340);
	}
	
	
}
