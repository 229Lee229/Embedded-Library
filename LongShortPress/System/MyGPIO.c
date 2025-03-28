#include "stm32f10x.h"                  // Device header
#include "MyGPIO.h"



void GPIO_Pin_Init(MyPinDef pin,GPIOMode_TypeDef Mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA<<(pin>>4), ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    //**All notes can be deleted and modified**//
    GPIO_InitStructure.GPIO_Pin  = GET_PIN_GPIO(pin); 
    GPIO_InitStructure.GPIO_Mode = Mode;
    GPIO_Init(GET_PORT_GPIO(pin), &GPIO_InitStructure);
}

/* 对GPIO高8位写入数据 */
void GPIO_WriteHigh(GPIO_TypeDef* GPIOx,u8 dat)
{
    GPIOx->BRR = 0xff00;
    GPIOx->BSRR = dat<<8;
}
/* 对GPIO低8位写入数据 */
void GPIO_WriteLow(GPIO_TypeDef* GPIOx,u8 dat)
{
    GPIOx->BRR = 0x00ff;
    GPIOx->BSRR = dat;
}
