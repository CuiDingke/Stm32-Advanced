#include "usart1.h"
#include <stdarg.h>
uint8_t SendBuff[]="2017 Summer Vacation,Signal LAB ,!!!\r\nA-B-C-D-E-F-G-H-0-1-2-3-4-5-6-7-8-9\r\nwww.hist.edu.cn   \r\n";
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =  USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	USART_Cmd(USART1, ENABLE); 
}
void DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	 
	  NVIC_Config();	   		 
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
    DMA_InitStructure.DMA_BufferSize = sizeof(SendBuff);   
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	   
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
	  DMA_Cmd (DMA1_Channel4,ENABLE);		 
	  DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);  
}
//void DMA_SConfig(void)
//{
//    DMA_InitTypeDef DMA_InitStructure;		 
//    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   
//    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
//    DMA_InitStructure.DMA_BufferSize = sizeof(SendBuff);   
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;	 
//    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	   
//    DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
//	  DMA_Cmd (DMA1_Channel4,ENABLE);	
//    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE); 	
//}
static void NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
uint8_t array_num(void)
{ 
	return sizeof(SendBuff);
}
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while( USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET);	
	return (ch);
}
