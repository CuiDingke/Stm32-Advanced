#include "stm32f10x.h"
#include "dac.h"
#include "bsp_usart1.h"
u16 adcx1,adcx2;
extern int i;
int main(void)
{
	 USART1_Config();
	 Dac1_Init();
//	 Dac1_Set_Vol(0);
	 printf("hahahah");
    while (1)
    {
			printf("DAC1----%d\r\n",i);
//			Dac1_Set_Vol(3000);
//			DAC_SetChannel2Data(DAC_Align_12b_R,4095);
			//adcx1=DAC_GetDataOutputValue(DAC_Channel_1);
//			adcx2=DAC_GetDataOutputValue(DAC_Channel_2);
			//printf("DAC1----%d\r\n",adcx1);
			//printf("DAC2----%d\r\n",adcx2);
			//DAC_SetChannel1Data(DAC_Align_12b_R,4095);
    }
}
