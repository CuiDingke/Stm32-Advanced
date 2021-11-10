#include "stm32f10x.h"
#include "Tim_conf.h"
int main(void)
{
  RCC_Configuration();
  NVIC_Configuration();
  GPIO_Configuration();
  tim3_conf();
  while (1)
  {}
}

