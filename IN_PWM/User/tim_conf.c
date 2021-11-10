#include "tim_conf.h"
void RCC_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}
void  tim3_conf(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
  TIM_Cmd(TIM3, ENABLE);
  TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
}
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* TIM3 channel 2 pin (PA.07) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
