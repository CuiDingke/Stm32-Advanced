#include "stm32f10x.h"
#include	"wwdg.h"
#include "led.h"
int	delay(int	time);
int main(void)
{
	led_config();
	delay(0xffffff);
	WWDG_Config(0x7f, 0x50, WWDG_Prescaler_8);
	while(1)
	{
		GPIOC->BRR=1<<0;
	}
}
int	delay(int	time)
{
	int	i;
	for(i=0;i<time;i++);
	return	0;
}


