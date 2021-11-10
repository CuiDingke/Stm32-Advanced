/*******************************************************************************
** 文件名: 		stm32f10x_it.c
** 版本：  		1.0
** 工作环境: 	RealView MDK-ARM 4.20
** 作者: 		河南科技学院
** 生成日期: 	2012-02-10
** 功能:		中断源文件
** 相关文件:	无
** 修改日志：	2012-02-10   创建文档
*******************************************************************************/
#include "stm32f10x_it.h"
int j=0;
void TIM2_IRQHandler(void)
{
	TIM2->CNT=0;
	TIM2->SR=0;
}


//void DMA1_Channel7_IRQHandler(void)
//{ 
//	if(DMA_GetITStatus(DMA1_IT_TC7)==1)
//	{ 
//		j = 1;
//		DMA_ClearITPendingBit(DMA1_IT_TC7);
//	}
//}

