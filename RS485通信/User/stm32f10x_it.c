#include "stm32f10x_it.h"
#include <string.h>
u8 RS485_RX_BUF[64]; 
u8 buf[64];
u8 RS485_RX_CNT=0; 
int i = 0,j;
void USART2_IRQHandler(void)
{
	u8 res;
 	if(USART_GetITStatus(USART2, USART_IT_RXNE) == 1) //���յ�����
	{	 
		res =USART_ReceiveData(USART2); 	//��ȡ���յ�������
		if(RS485_RX_CNT<64)
		{
			RS485_RX_BUF[RS485_RX_CNT]=res;		//��¼���յ���ֵ
			RS485_RX_CNT++;						//������������1 
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
		j = USART2->SR;//���IDLE  Ҫ�ȶ�SR  �ٶ�DR �����������
		j = USART2->DR;
		USART_ClearITPendingBit(USART2,USART_IT_IDLE);
		
	}
} 

