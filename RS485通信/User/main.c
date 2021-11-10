#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "rs485.h"	
extern u8 buf[64];
extern int i;
u8 A[4] = {'A','1','2','3'};
u8 B[4] = {'B','1','2','3'};
void Delay(u32 nCount);
int main(void)
{
  RS485_Init();
	LED_Init();
	KEY_Init();
    while (1)
    {
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0)
			{
				Delay(0xffff);
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0);
				RS485_Send_Data(A,4);
				Delay(0xfffff);
			}
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0)
			{
				Delay(0xffff);
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0);
				RS485_Send_Data(B,4);
			}
			if(buf[0] == 'A')
			{
				GPIOE->ODR|= 1<<5;
			}
			else if(buf[0] == 'B')
			{
				GPIOE->ODR&= ~(1<<5);
			}
    }
}

void Delay(u32 nCount)
{
	for(; nCount != 0;nCount--);
}
