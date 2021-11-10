#include "stm32f10x.h"
#include "pwm_input.h"
#include "misc.h" 
//u32 res;
extern u16 buffer[1];
extern int j;
int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		MYDMA_Config();
	  Pwm_Input();
    USART_1_Config();
    while (1)
    {

//			while(DMA_GetFlagStatus(DMA1_FLAG_TC7) == 1)
//			{
//				DMA_ClearFlag(DMA1_FLAG_TC7);
			printf("ÆµÂÊ:%d\r\n",72000000/buffer[0]);
//				if(j == 1)
//				{
//					j = 0;
//					printf("ÆµÂÊ:%d\r\n",72000000/buffer[0]);
//				}
				
//				DMA_Cmd(DMA1_Channel7,DISABLE);
//				TIM_Cmd(TIM2,DISABLE);
//				for(int i=0;i<10;i++)
//				{
//					res+=buffer[i];
//					buffer[i]=0;
//				}
//				printf("counts:%d\r\n",72000000/(res/10));
//				res=0;
//        TIM_Cmd(TIM2,ENABLE);
//				DMA1_Channel7->CNDTR =10;
//				DMA_Cmd(DMA1_Channel7,ENABLE);
				
//	    }
 }
		
}
