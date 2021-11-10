#include "stm32f10x.h"
#include "USART_conf.h"
#include  "Tim_conf.h"
extern __IO uint32_t TIM3Freq;
extern uint16_t aa[20];
void Delay(__IO uint32_t nCount);
uint32_t sum=0;
uint8_t m=0;
int main(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  NVIC_Configuration();
  GPIO_Configuration();
  Tim3_conf();
	Usart1_conf();
	Delay(0x5fff);
	for(m=0;m<20;m++)
		{ sum+=aa[m];}
	sum=sum/20;
	printf("Freq=%8d\r\n",sum );
	for(m=0;m<20;m++)
	printf("Sample%d=%8d\r\n",m,aa[m] );	
  while (1)
		{ }
}
void Delay(__IO uint32_t nCount)	 
{
	for(; nCount != 0; nCount--);
}

