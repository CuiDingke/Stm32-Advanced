#ifndef DAM1_ART_H
#define DAM1_ART_H
#include "stm32f10x.h"
void DMA_Configuration(void);
void USAT1_Conf(void );
void GPIO_Configuration(void);
void RCC_Configuration(void);
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#endif
