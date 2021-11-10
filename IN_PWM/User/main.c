#include "stm32f10x.h"
#include "tim_conf.h"
#include "USART_conf.h"
extern __IO uint16_t DutyCycle;
extern __IO uint32_t Frequency;
int main(void)
{
  RCC_Configuration();
  NVIC_Configuration();
  GPIO_Configuration();
	tim3_conf();
	Usart1_conf();
  while (1)
  {	printf("ÆµÂÊ=%d\r\n", Frequency );
		printf("Õ¼¿Õ±È=%d\r\n", DutyCycle );
		}	
}




