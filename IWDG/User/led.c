#include "led.h"
void led_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin = 0x7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
    GPIO_Init(GPIOC , &GPIO_InitStructure);
	  GPIOC->ODR|=0x7;
}


