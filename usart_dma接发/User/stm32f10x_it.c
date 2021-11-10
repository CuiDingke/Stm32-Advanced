#include "stm32f10x_it.h"
#include "usart_dma.h"
#include "string.h"
int j;
extern int x;
extern uint8_t res[50],sen[50];
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_IDLE) != 0)
	{
		/*��ý����ַ��ĳ���---����һ*/
		x=sizeof(res)-DMA_GetCurrDataCounter(DMA1_Channel5);
		/*��ý����ַ��ĳ���---������*/
		memset(sen,0,strlen(sen));
		memcpy(sen,res,strlen(res));
		
		DMA_Cmd(DMA1_Channel5,DISABLE);
		DMA1_Channel5->CNDTR = sizeof(res);
		DMA_Cmd(DMA1_Channel5,ENABLE);
		
		DMA_Cmd(DMA1_Channel4,DISABLE);
  	DMA1_Channel4->CNDTR = strlen(sen+1);//���л��з�ʱ����һ���ֽ��൱����ʱ��Ҳ���Լ���ʱ�����ü��ֽ�
		DMA_Cmd(DMA1_Channel4,ENABLE);
		/*��������������жϱ�־λ*/
    j = USART1->SR;
		j = USART1->DR;
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);		
	}
}
