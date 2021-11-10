void RTC_Configuration(void)
{ 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
  PWR_BackupAccessCmd(ENABLE);
  BKP_DeInit();     // 可以删掉
#if  defined(LSI_my)
	RCC_LSICmd( ENABLE );
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#elif defined(HSE_my)
  RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
#elif defined(LSE_my)	
  RCC_LSEConfig(RCC_LSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);	
#endif	
  RCC_RTCCLKCmd(ENABLE);
  RTC_WaitForSynchro();
  RTC_WaitForLastTask();
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
  RTC_WaitForLastTask();
#if  defined(LSI_my)		
  RTC_SetPrescaler(39999); 
#elif defined(HSE_my)
	RTC_SetPrescaler(62499);	
#elif defined(LSE_my)	
	RTC_SetPrescaler(32767);	
#endif
  RTC_WaitForLastTask();
}