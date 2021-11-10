#ifndef __RS485_H
#define __RS485_H			 
								  
#include "stm32f10x.h"

#define RS485_TX_EN		GPIOD->BSRR=1<<7	//485模式控制.0,接收;1,发送.
#define RS485_RX_EN		GPIOD->BRR=1<<7

void RS485_Init(void);
void RS485_Send_Data(u8 *buf,u8 len);



#endif	   
















