#include "stm32f10x.h"
#include "usart1.h"
#include "led.h"
 extern uint8_t SendBuff[];
 extern  u8 flag;
 uint16_t  m;
int main(void)
{	
	USART1_Config();
	DMA_Config();
	LED_GPIO_Config();
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);	
	LED2(ON);
	while(1)
	{
		if (flag==1)
		{
			DMA_Cmd (DMA1_Channel4,DISABLE);
			DMA1_Channel4->CNDTR= array_num() ;
			DMA_Cmd(DMA1_Channel4, ENABLE);
			flag=0;
	  }
	
	};
}
