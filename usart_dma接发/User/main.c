#include "stm32f10x.h"
#include "usart_dma.h"
int main()
{
	USART_1Config();
	DMA1_Channel45_Config();
	while(1)
	{
		if(DMA_GetFlagStatus(DMA1_FLAG_TC4) != 0)
		{
				USART1->DR='\r';
				USART1->DR='\n';
				DMA_Cmd(DMA1_Channel4,DISABLE);
				DMA_ClearFlag(DMA1_FLAG_TC4);
		}
	}
}

