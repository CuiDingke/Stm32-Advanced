#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_adc.h"
#include "ADC_filter.h"
float  adc_average(uint16_t temp[]);
extern __IO uint16_t ADC_ConvertedValue; 
float ADC_ConvertedValueLocal;        
float tempe_value;   //�����¶Ȳ���ֵ
uint16_t  ADC_Sample[20];  //����ֵ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

int main(void)
{	
	USART1_Config();
	ADC1_Init();
	printf("\r\n ����һ��ADC��DMA��������----\r\n");
	for(int m =0; m<20;m++)
	{if (m%4==0) printf("\r\n");
	printf("%d ,  ", ADC_Sample[m]);
	}
	printf("\r\n\r\n");
	ADC_ConvertedValueLocal=adc_average(ADC_Sample);
	tempe_value=(1.43-tempe_value)/4.3+25;
	printf("ADת��ֵ��%5.2f V\r\n\r\n", ADC_ConvertedValueLocal); 
		printf("Ŀǰ�¶ȣ�%5.2f ��\r\n",tempe_value); 
	while (1)
	{
		Delay(0xffffee);  
	}
}

