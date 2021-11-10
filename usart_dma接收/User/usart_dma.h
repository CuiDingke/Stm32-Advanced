#ifndef  __USART_DMA_H
#define  __USART_DMA_H
 
 
#include "stm32f10x.h"
#include "stdio.h"

void DMA1_Channel45_Config(void);

void USART_1Config(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);


#endif


