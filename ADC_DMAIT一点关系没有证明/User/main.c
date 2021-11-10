#include "stm32f10x.h"
#include "stdio.h"
uint16_t ADCConvertedValue[20];
float Sum_Dianya,Sum_Wendu;
float pingjun(uint16_t aa[20]);
uint16_t i=0;
int main ()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl =0;
  USART_InitStructure.USART_Mode =  USART_Mode_Tx;  
  USART_Init(USART1, &USART_InitStructure);
//  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
//  DMA_Cmd(DMA1_Channel4, ENABLE);
  USART_Cmd(USART1, ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 20;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel= DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_TempSensorVrefintCmd(ENABLE);    
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 2, ADC_SampleTime_55Cycles5);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);   
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

  pingjun(ADCConvertedValue);
	while(1)
  {
		
  }
}

float pingjun(uint16_t aa[20])
{
	for(int i=0;i<10;i++)
	{
		Sum_Wendu+=ADCConvertedValue[2*i+1];
		Sum_Dianya+=ADCConvertedValue[2*i];
	}
	Sum_Dianya=(Sum_Dianya/10)*3.3/4096;
	Sum_Wendu=(Sum_Wendu/10)*3.3/4096;
	return Sum_Wendu;
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


void DMA1_Channel1_IRQHandler(void)
{ 
	if(DMA_GetITStatus(DMA1_IT_TC1)==1)
	{ 
		i++;
		if(i<6)
		{
			printf(" 这是一个ADC_DMA实验 \r\n");
			for(int j=0;j<20;j++)
			{
				if(j%4==0)
				{
					printf("\r\n");
				}
			printf("%d  ,",ADCConvertedValue[j]);   	
			}
			printf("\r\n\r\n");
			Sum_Wendu = (1.43 - pingjun(ADCConvertedValue))*1000/4.3+25;
			printf("电压%5.2fV\r\n",Sum_Dianya);
			printf("温度%5.2f℃\r\n",Sum_Wendu);	
	  }		
		if(i>=6)
		  {
//				i=0;
				DMA_Cmd(DMA1_Channel1, DISABLE);
				ADC_DMACmd(ADC1, DISABLE);
			}
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
}
