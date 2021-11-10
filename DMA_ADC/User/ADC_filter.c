#include "ADC_filter.h"
#include "bsp_usart1.h"
extern float tempe_value;
float  adc_average(uint16_t temp[])
{
	uint32_t  tempe_sum=0 ,ADC_sum=0;
	uint8_t  i=0;
	for (i=0;i<10;i++)
	{ADC_sum+=temp[2*i];
	tempe_sum+=temp[2*i+1];}
	tempe_value=0.33*tempe_sum/4096;
	return 0.33*ADC_sum/4096;
}
