#include "stm32f10x.h"
#include "DMA1_ART.h"
void Delay(__IO u32 nCount);
int main(void)
{
  RCC_Configuration();
	NVIC_Configuration();
  GPIO_Configuration();
  DMA_Configuration();
  USAT1_Conf();
  while (1)
  { GPIOC->BRR|=1<<2;
		Delay(0x3FFFFF);
		GPIOC->BSRR|=1<<2;
		Delay(0x3FFFFF);
	}
}
void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}
