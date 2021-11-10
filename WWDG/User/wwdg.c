#include	"wwdg.h"
void	WWDG_NVIC_Config()	
{
		NVIC_InitTypeDef NVIC_InitStructure;
	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
}
int	WWDG_Config(uint8_t tr, uint8_t wr, uint32_t prv)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
		
	WWDG_SetCounter( tr );
	WWDG_SetPrescaler( prv );
	WWDG_SetWindowValue( wr );
	WWDG_Enable(0x7f);	
	WWDG_ClearFlag();	
	WWDG_NVIC_Config();	
	WWDG_EnableIT();
}
void WWDG_Feed(void)
{
	WWDG_SetCounter( 0x7f );
}
