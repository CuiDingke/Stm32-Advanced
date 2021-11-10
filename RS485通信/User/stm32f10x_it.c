#include "stm32f10x_it.h"
#include <string.h>
u8 RS485_RX_BUF[64]; 
u8 buf[64];
u8 RS485_RX_CNT=0; 
int i = 0,j;
void USART2_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(USART2, USART_IT_RXNE) == 1) //接收到数据
	{	 
		res =USART_ReceiveData(USART2); 	//读取接收到的数据
		if(RS485_RX_CNT<64)
		{
			RS485_RX_BUF[RS485_RX_CNT]=res;		//记录接收到的值
			RS485_RX_CNT++;						//接收数据增加1 
		} 
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}  	
	if(USART_GetITStatus(USART2,USART_IT_IDLE) == 1)
	{
		GPIOB->ODR^= 1<<5;
		memset(buf,0,strlen(buf));
		for(i=0;i<RS485_RX_CNT;i++)
		{
			buf[i]=RS485_RX_BUF[i];	
		}		
		memset(RS485_RX_BUF,0,strlen(RS485_RX_BUF));
		RS485_RX_CNT = 0;
		j = USART2->SR;//清除IDLE  要先读SR  再读DR 否则清除不了
		j = USART2->DR;
		USART_ClearITPendingBit(USART2,USART_IT_IDLE);
		
	}
} 

