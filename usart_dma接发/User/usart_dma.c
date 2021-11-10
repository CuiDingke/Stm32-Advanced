#include "usart_dma.h"
#include "string.h"
uint8_t res[50],sen[50];
int x = 0;
void  DMA1_Channel45_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
//	NVIC_InitTypeDef  NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	DMA_DeInit(DMA1_Channel4);  
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) &(USART1->DR);
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&res;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = strlen(sen);
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); 
	DMA_Cmd(DMA1_Channel4, DISABLE);
		
		
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &(USART1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)res;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = sizeof(res);      
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;      
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;            
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
	DMA_Init(DMA1_Channel5,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel5,ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}

void USART_1Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
		NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef  USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_Init(USART1,&USART_InitStructure);
		
		USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
		
    USART_Cmd(USART1, ENABLE);

}

int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (uint8_t) ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);			
		return (ch);
}
int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		return (int)USART_ReceiveData(USART1);
}

