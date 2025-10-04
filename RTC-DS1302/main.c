#include "stm32f10x.h"                  // Device header
#include "My_include.h"
/****/
uchar time_data[6]={0};//读取DS1302当前时间缓存矩阵

int main(void) {
	OLED_Init();
	Usart1_Init(115200);
	uchar init_time[6]={24,7,7,14,40,00};//初始化时间参数
	DS1302_init(init_time);
	DS1302_SetTime(init_time);
		  // OLED_ShowNum(1,1,init_time[0],2);		// year
	printf("hello!\r\n");
  while (1) {
    /* USER CODE END WHILE */
	  DS1302_Readtime();
	  printf("20%d-%d-%d  %d:%d:%d\r\n",time_data[0],time_data[1],time_data[2],time_data[3],time_data[4],time_data[5]);
//	  OLED_ShowNum(2,1,(u32)time_data[0],2);		// year
//		OLED_ShowChar(2,3,'-');
//	  OLED_ShowNum(2,4,(u8)time_data[1],2);		// month
//	  	OLED_ShowChar(2,6,'-');
//	  OLED_ShowNum(2,7,(u8)time_data[2],2);		// day
////		OLED_ShowChar(2,9,' ');
//	  OLED_ShowNum(2,10,time_data[3],2);	 	// hour 	 
//		OLED_ShowChar(2,12,':');
//	  OLED_ShowNum(2,13,time_data[4],2);		// minute
//		OLED_ShowChar(2,15,':');
//	  OLED_ShowNum(2,16,time_data[5],2);		// second

	  Delay_ms(1000);
	  
  }
  /* USER CODE END 3 */
}
