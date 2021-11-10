#ifndef  __IWDG_H
#define  __IWDG_H


#include"stm32f10x.h"


int	IWDG_Config(uint8_t x, uint16_t y);
void	IWDG_Feed(void);

#endif
