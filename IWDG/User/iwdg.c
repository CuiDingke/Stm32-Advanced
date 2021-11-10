#include	"iwdg.h"
int	IWDG_Config(uint8_t x,uint16_t  y)
{
	IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
	
	IWDG_SetPrescaler( x );
	IWDG_SetReload(	y );
	IWDG_ReloadCounter();
	
	IWDG_Enable();	
		
	return	0;
}
void	IWDG_Feed(void)
{
	IWDG_ReloadCounter();
}
