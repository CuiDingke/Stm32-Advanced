#include "stm32f10x.h"
#include "bsp_adc.h"
#include "bsp_usart1.h"

float ADC_ConvertedValuetel[6];
extern __IO u32 ADC1_ConvertedValue[3];
extern __IO u16 ADC3_ConvertedValue;
int main(void)
{
	USART1_Config();
	ADC1_Config();
    while (1)
    {
			
			ADC_ConvertedValuetel[0] = (float)((u16)ADC1_ConvertedValue[0]);
			ADC_ConvertedValuetel[1] = (float)(ADC1_ConvertedValue[0]>>16);
			ADC_ConvertedValuetel[2] = (float)(u16)ADC1_ConvertedValue[1];
			ADC_ConvertedValuetel[3] = (float)(ADC1_ConvertedValue[1]>>16);
			ADC_ConvertedValuetel[4] = (float)(u16)ADC1_ConvertedValue[2];
			ADC_ConvertedValuetel[5] = (float)(ADC1_ConvertedValue[2]>>16);
			printf("通道0---%.2f v\r\n",(float)ADC3_ConvertedValue);
			printf("通道1---%.2f v\r\n",ADC_ConvertedValuetel[0]);
			printf("通道2---%.2f v\r\n",ADC_ConvertedValuetel[2]);
			printf("通道3---%.2f v\r\n",ADC_ConvertedValuetel[4]);		
			printf("通道4---%.2f v\r\n",ADC_ConvertedValuetel[1]);
			printf("通道5---%.2f v\r\n",ADC_ConvertedValuetel[3]);
			printf("通道6---%.2f v\r\n",ADC_ConvertedValuetel[5]);
			
			
		}
}

