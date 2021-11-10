#include "bsp_adc.h"

u32 __IO ADC1_ConvertedValue[3];
u16 __IO ADC3_ConvertedValue;
/*103没有ADC3   用DMA2通道5时会出现硬件错误  切记*/
void ADC1_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC2|RCC_APB2Periph_ADC3,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&ADC1->DR;	 	
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC1_ConvertedValue;	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	DMA_DeInit(DMA2_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&ADC3->DR;	 	
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC3_ConvertedValue;	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel5,&DMA_InitStructure);
	DMA_Cmd(DMA2_Channel5, ENABLE);

	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	
	ADC_InitStructure.ADC_NbrOfChannel = 3;	 							
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_InitStructure.ADC_Mode = ADC_Mode_RegSimult ;	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 3;	 	
	ADC_Init(ADC2,&ADC_InitStructure);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent ;	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	
	ADC_Init(ADC3,&ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_0,1,ADC_SampleTime_239Cycles5); 
	ADC_DMACmd(ADC3,ENABLE);
	ADC_Cmd(ADC3,ENABLE);	
	ADC_ResetCalibration(ADC3);
	while(ADC_GetResetCalibrationStatus(ADC3));
	ADC_StartCalibration(ADC3);
	while(ADC_GetCalibrationStatus(ADC3));
	ADC_SoftwareStartConvCmd(ADC3,ENABLE);

	ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5); 
	ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5); 
	ADC_RegularChannelConfig(ADC2, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5);
	ADC_Cmd(ADC2,ENABLE);
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));
	//ADC_SoftwareStartConvCmd(ADC2,ENABLE); //为什么效果一样
	ADC_ExternalTrigConvCmd(ADC2,ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_239Cycles5); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_239Cycles5);
	ADC_DMACmd(ADC1,ENABLE);	//切记  一定要放在后面开启  不然会错位
	ADC_Cmd(ADC1,ENABLE);	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	

	 
	
}
