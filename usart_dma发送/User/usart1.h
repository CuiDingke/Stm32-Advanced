#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#define USART1_DR_Base  0x40013804

void USART1_Config(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void DMA_Config(void);
static void NVIC_Config(void);
void DMA_SConfig(void);
uint8_t array_num(void);
#endif /* __USART1_H */
