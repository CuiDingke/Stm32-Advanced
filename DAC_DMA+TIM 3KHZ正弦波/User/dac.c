#include "dac.h"
uint16_t OUTPUT_BUFFER[32]={ 2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909, 599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};
//uint16_t OUTPUT_BUFFER[1]={4095};
void Dac1_Init(void)
{
	DAC_InitTypeDef DAC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
  TIM_TimeBaseStructure.TIM_Period = 10-1; 
  TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
  TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
  TIM_Cmd(TIM2, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	
	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(DAC->DHR12R1);
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&OUTPUT_BUFFER;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize =32;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel3, &DMA_InitStructure); 
//	DMA_ITConfig(DMA2_Channel3,DMA_IT_TC,ENABLE);//为什么不进中断
	DAC_DMACmd(DAC_Channel_1,ENABLE);
  DMA_Cmd(DMA2_Channel3, ENABLE);
  
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_T2_TRGO;	//触发功能
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//DAC1输出缓存关闭 BOFF1=1 
	DAC_SetChannel1Data(DAC_Align_12b_R,0);  //12位右对齐数据格式设置DAC值
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);	 //初始化DAC通道1
	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
//	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	
//	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
//	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
//	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
//	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//DAC1输出缓存关闭 BOFF1=1
//  DAC_Init(DAC_Channel_2,&DAC_InitStructure);	 //初始化DAC通道1
//	DAC_Cmd(DAC_Channel_2, ENABLE);  //使能DAC1
//  DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值

}

//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}

void DAC_TRIGTIM_Config(void)
{
  
}



















































