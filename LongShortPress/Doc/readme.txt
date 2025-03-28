/* 代码例程 */
	/* 标准库配置 PA0 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	
	
	/* 位带操作 */
	int main(void){
		RCC->APB2ENR = 0x04;
		GPIOA->CRL = 0x03;
		OLED_Init();

		while(1){
			// PAout(0) = 1;
			// WritePin(A,0) = 1;
			TogglePin(A,0);
			OLED_ShowNum(1,1,ReadPin(A,0),4);
			Delay_ms(250);
			
			// PAout(0) = 0;
			// WritePin(A,0) = 1;
			TogglePin(A,0);
			OLED_ShowNum(1,1,ReadPin(A,0),4);
			Delay_ms(250);
		}
	}
	
	/* 配置寄存器 闪烁PC13 */
	int main(void){

		RCC->APB2ENR = 0x10;
		GPIOC->CRH = 0x00300000;
		/* GPIOC->ODR = 0X2000; */

		while(1){
			GPIOC->BSRR = 0X2000;
			Delay_ms(200);
			
			GPIOC->BRR = 0x2000;
			Delay_ms(200);
		}
	}
	
	
	
	
	
	/*	以上为托管代码	*/