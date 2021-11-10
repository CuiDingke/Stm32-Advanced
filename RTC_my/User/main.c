#include "stm32f10x.h"
#include  <stdio.h>
#include  "BSP_USART.h"
#include "BSP_RTC.h"
__IO uint32_t TimeDisplay = 0;
int main(void)
{
  USART1_conf();
	NVIC_Configuration();
  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    printf("\r\n\n RTC not yet configured....");
    RTC_Configuration();
    printf("\r\n RTC configured....");
    Time_Adjust();
    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
  else
  {
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("\r\n\n Power On Reset occurred....");
    }
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("\r\n\n External Reset occurred....");
    }
    printf("\r\n No need to configure RTC...."); 
		RCC_APB1PeriphClockCmd( RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
		PWR_BackupAccessCmd(ENABLE);		
#if  defined(LSI_my)
//   RTC_WaitForSynchro();
	RCC_LSICmd( ENABLE );		
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
  RTC_SetPrescaler(39999); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#elif defined(HSE_my)
	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
	RTC_SetPrescaler(62499);	
#elif defined(LSE_my)	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RTC_SetPrescaler(32767);	
	RCC_LSEConfig(RCC_LSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
#endif
//   RTC_WaitForSynchro();
//		RCC_LSICmd( ENABLE );
	  RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    RTC_WaitForLastTask();
  }
  RCC_ClearFlag();
  Time_Show();
}







