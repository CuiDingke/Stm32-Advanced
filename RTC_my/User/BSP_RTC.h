#ifndef __BSP_RTC_H
#define __BSP_RTC_H
#include "stm32f10x.h"
#define  LSI_my
void NVIC_Configuration(void);
void RTC_Configuration(void);
uint32_t Time_Regulate(void);
void Time_Show(void);
uint32_t Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(uint32_t TimeVar);
#endif
