#include "stm32f10x.h"
#include "can.h"
#include "led.h"
#include "key.h"
#include "bsp_usart1.h"
#include "string.h"
u8 mode = CAN_Mode_LoopBack;//回环模式  可以自发自收 她收(他-->应为正常模式)  
u8 Num[8] = "01234567";
u8 Sun[8] = "89abcdef";
extern CanRxMsg RxMessage;
void Delay(u32 nCount);
int main(void)
{
   CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,1);
	 LED_Init();
	 KEY_Init();
	 USART1_Config();
    while (1)
    {
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0)
			{
				Delay(0xfffff);
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == 0);
				CAN_TxMessageInit(0x12,0x44,CAN_Id_Standard,CAN_RTR_Data,8,Num);
			}
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0)
			{
				Delay(0xfffff);
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 0);
				CAN_TxMessageInit(0x13,0x44,CAN_Id_Standard,CAN_RTR_Data,8,Sun);
			}
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0)
			{
				Delay(0xfffff);
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == 0);
				mode =! mode;
				CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,mode);
				GPIOB->ODR^= 1<<5;
			}
			if(RxMessage.StdId == 0x12 && RxMessage.DLC == 8)
			{
				GPIOE->ODR|= 1<<5;
				printf("stdID is %x, DIC is %x, receive data is %s \r\n", RxMessage.StdId, RxMessage.DLC,RxMessage.Data);
				memset(&RxMessage, 0, sizeof(RxMessage));
			}
			if(RxMessage.StdId == 0x13 && RxMessage.DLC == 8)
			{
				GPIOE->ODR&= ~(1<<5);
				printf("stdID is %x, DIC is %x, receive data is %s \r\n", RxMessage.StdId, RxMessage.DLC, RxMessage.Data);
				memset(&RxMessage, 0, sizeof(RxMessage));
			}
			
    }
}

void Delay(u32 nCount)
{
	for(; nCount != 0;nCount--);
}
