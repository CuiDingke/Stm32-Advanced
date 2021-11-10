#include "stm32f10x.h"
#include "usart_dma.h"
extern int i;
extern int x;
int main()
{
	USART_1Config();
	DMA1_Channel45_Config();
	while(1)
	{
	if(i==1)
	{
		printf("%d\r\n",x);
		i = 0;
	}
	}
}

