#include "BSP_RTC.h"
#include  "BSP_USART.h"
extern __IO uint32_t TimeDisplay ;
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void RTC_Configuration(void)
{ 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  PWR_BackupAccessCmd(ENABLE);
  BKP_DeInit();     //可根据情况选删掉
#if  defined(LSI_my)
	RCC_LSICmd( ENABLE );
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#elif defined(HSE_my)
  RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
#elif defined(LSE_my)	
  RCC_LSEConfig(RCC_LSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);	
#endif	
  RCC_RTCCLKCmd(ENABLE);
  RTC_WaitForSynchro();
  RTC_WaitForLastTask();
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
  RTC_WaitForLastTask();
#if  defined(LSI_my)		
  RTC_SetPrescaler(39999); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#elif defined(HSE_my)
	RTC_SetPrescaler(62499);	
#elif defined(LSE_my)	
	RTC_SetPrescaler(32767);	
#endif
  RTC_WaitForLastTask();
}

uint32_t Time_Regulate(void)
{
  uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;
  printf("\r\n==============Time Settings=====================================");
  printf("\r\n  Please Set Hours");
  while (Tmp_HH == 0xFF)
  {
    Tmp_HH = USART_Scanf(23);
  }
  printf(":  %d", Tmp_HH);
  printf("\r\n  Please Set Minutes");
  while (Tmp_MM == 0xFF)
  {
    Tmp_MM = USART_Scanf(59);
  }
  printf(":  %d", Tmp_MM);
  printf("\r\n  Please Set Seconds");
  while (Tmp_SS == 0xFF)
  {
    Tmp_SS = USART_Scanf(59);
  }
  printf(":\r\n  %d", Tmp_SS);
  return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}
void Time_Adjust(void)
{
  RTC_WaitForLastTask();
  RTC_SetCounter(Time_Regulate());
  RTC_WaitForLastTask();
}
void Time_Display(uint32_t TimeVar)
{
  uint32_t THH = 0, TMM = 0, TSS = 0; 
  if (RTC_GetCounter() == 0x0001517F)
  {
     RTC_SetCounter(0x0);
     RTC_WaitForLastTask();
  }
  THH = TimeVar / 3600;
  TMM = (TimeVar % 3600) / 60;
  TSS = (TimeVar % 3600) % 60;

  printf("  Time: %0.2d:%0.2d:%0.2d\r\n", THH, TMM, TSS);
}

void Time_Show(void)
{
  printf("\n\r");
  while (1)
  {
    if (TimeDisplay == 1)
    {
      Time_Display(RTC_GetCounter());
      TimeDisplay = 0;
    }
  }
}
