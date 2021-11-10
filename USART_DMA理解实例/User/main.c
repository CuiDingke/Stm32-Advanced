#include "stm32f10x.h"
#include "DMA1_ART.h"
extern uint8_t aa ;
void Delay(__IO u32 nCount);
int i;
int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  DMA_Configuration();
  USAT1_Conf();
	
  while (1)
  { 
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	{ 
		i++;
		if(i%2==0)
			{
				DMA1_Channel4->CNDTR = aa;
				DMA_Cmd(DMA1_Channel4, ENABLE);	
			}
		if(i%2==1)
		{
			DMA_Cmd(DMA1_Channel4, DISABLE);
		}
	}
		GPIOC->BRR|=1<<3;
		Delay(0x0FFFFF);	
		GPIOC->BSRR|=1<<3;
		Delay(0x0FFFFF);
		GPIOC->BRR|=1<<1;
		Delay(0x0FFFFF);	
		GPIOC->BSRR|=1<<1;
		Delay(0x0FFFFF);
		GPIOC->BRR|=1<<2;
		Delay(0x0FFFFF);	
		GPIOC->BSRR|=1<<2;
		Delay(0x0FFFFF);
		while (DMA_GetFlagStatus(DMA1_FLAG_TC4 ) == SET)
  { 
		GPIOC->BRR|=1<<0;
		Delay(0x0FFFFF);
    GPIOC->BSRR|=1<<0;
		Delay(0x0FFFFF);
		DMA_ClearFlag(DMA1_FLAG_TC4);
	} 
		
	}
	
	
}
void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}
