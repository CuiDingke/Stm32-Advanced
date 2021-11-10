#include "stm32f10x.h"
#include "tim_conf.h"
int main(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
  GPIO_Configuration();
	tim3_conf();
  while (1)
  {}
}
