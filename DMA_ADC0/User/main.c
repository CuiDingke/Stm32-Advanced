#include "stm32f10x.h"
#include "stdio.h"
#include "bsp_usart1.h"
uint16_t ADCConvertedValue[20];
float Sum_Dianya,Sum_Wendu;
float pingjun(uint16_t aa[20]);
int main ()
{
	USART1_Config();
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

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
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);

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
//	printf(" 这是一个ADC_DMA实验 \r\n");
//	for(int j=0;j<20;j++)
//	{
//		if(j%4==0)
//		{
//			printf("\r\n");
//		}
//	printf("%d  ,",ADCConvertedValue[j]);   	
//	}
//	printf("\r\n\r\n");
//	Sum_Wendu = (1.43 - pingjun(ADCConvertedValue))*1000/4.3+25;
//	printf("电压%5.2fV\r\n",Sum_Dianya);
//	printf("温度%5.2f℃\r\n",Sum_Wendu);	
	while(1)
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
//	ADC_Cmd(ADC1, DISABLE);	
		
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

