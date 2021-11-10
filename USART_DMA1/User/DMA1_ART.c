#include "DMA1_ART.h"
uint8_t TxBuffer1[] = "河南科技学院机电学院欢迎您！信号实验室！\r\n";
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel4);  
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) &(USART1->DR);
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = TxBufferSize1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular ;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
}
void USAT1_Conf(void )
{ 
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl =0;
  USART_InitStructure.USART_Mode =  USART_Mode_Tx;  
  USART_Init(USART1, &USART_InitStructure);
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  DMA_Cmd(DMA1_Channel4, ENABLE);
  USART_Cmd(USART1, ENABLE);
}
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIOC->ODR|=1<<0;
}
void RCC_Configuration(void)
{  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
}

