#include "stm32f10x.h"
#include "DMA1_ART.h"
void Delay(__IO u32 nCount);
int main(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  DMA_Configuration();
  USAT1_Conf();
  while (DMA_GetFlagStatus(DMA1_FLAG_TC4 ) == RESET)
  {   } 
  while (1)
  { GPIOC->BRR|=1<<0;
		Delay(0x0FFFFF);
		GPIOC->BSRR|=1<<0;
		Delay(0x0FFFFF);
	}
}
void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}
