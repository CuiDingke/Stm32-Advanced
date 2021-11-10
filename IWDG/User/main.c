#include "stm32f10x.h"
#include	"iwdg.h"
#include "led.h"
#include "EXTI.h"
int	delay(int	time);
int main(void)
{
	EXTI1_Config();
	led_config();	
	delay(0xffffff);
	IWDG_Config(IWDG_Prescaler_64	,	625);
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == 1)
  {
    //GPIOC->BRR=0x01;
		GPIOC->ODR^=1<<0;
    RCC_ClearFlag();
  }
  
	
	while(1)
	{
		GPIOC->BSRR=1<<2;
		delay(0xffffff);
		GPIOC->BRR=1<<2;
		delay(0xffffff);
	}
}
int	delay(int	time)
{
	int	i;
	for(i=0;i<time;i++);
	return	0;
}


