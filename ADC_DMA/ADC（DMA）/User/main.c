#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_adc.h"

// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[2];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[2];        
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	USART1_Config();
	ADC1_Init();
	printf("\r\n ----����һ��ADCʵ��(DMA����)----\r\n");
	while (1)
	{
		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3; // ��ȡת����ADֵ
	  ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
		printf("\r\n The current AD value[0] = 0x%04X \r\n", ADC_ConvertedValue[0] ); 
		printf("\r\n The current AD value[1] = 0x%04X \r\n", ADC_ConvertedValue[1] ); 
		printf("\r\n The current AD value[0] = %f V \r\n",ADC_ConvertedValueLocal[0]); 
	  printf("\r\n The current AD value[1] = %f V \r\n",ADC_ConvertedValueLocal[1]); 
		Delay(0xffffee);  
	}
}
/*********************************************END OF FILE**********************/
