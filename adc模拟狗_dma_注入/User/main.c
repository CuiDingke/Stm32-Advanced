#include "stm32f10x.h"
#include "bsp_adc.h"
#include "bsp_usart1.h"
#include "key.h" 
#include "tim.h"
#include "led.h"

extern __IO uint16_t ADC_ConvertedValue[2];
float ADC_ConvertedValuetel[2];
float I[2];
int Status;
extern int i;
int main(void)
{
	
	Tim2_Init();
	ADC1_Config();
	USART1_Config();
	Key_GPIO_Config();
	LED_GPIO_Config();
	
    while (1)
    {
			printf("%d\r\n",i);
			ADC_ConvertedValuetel[0]=ADC_ConvertedValue[0]*3.3/4096;
			ADC_ConvertedValuetel[1]=ADC_ConvertedValue[1]*3.3/4096;
			//ADC_ConvertedValuetel[0]=(1.43-ADC_ConvertedValuetel[0])*1000/4.3+25;
			printf("ͨ��2---%.2f v\r\n",ADC_ConvertedValuetel[0]);
			printf("ͨ��3---%.2f v\r\n",ADC_ConvertedValuetel[1]);
			I[0] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1)*3.3/4096;
			I[1] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_2);
			I[0] = (1.43-I[0])*1000/4.3+25;
			printf("ͨ��16---%.2f v\r\n",I[0]);
			printf("ͨ��17---%.2f v\r\n",I[1]*3.3/4096);	
			if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) == 0)
			{
				TIM_Cmd(TIM2, ENABLE);
			}
			else
			{
				TIM_Cmd(TIM2, DISABLE);
			}
			GPIO_SetBits(GPIOC, GPIO_Pin_1);
/*
//			if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) == 0)
//			{
//				
//         //ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);
//					ADC_AutoInjectedConvCmd(ADC1,ENABLE);		
//          I[0] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);
//			    I[1] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_2);
//			    printf("ͨ��0---%.2f v\r\n",I[0]*3.3/4096);
//			    printf("ͨ��1---%.2f v\r\n",I[1]*3.3/4096);				
//			}
//			else
//			{
//				//ADC_SoftwareStartInjectedConvCmd(ADC1,DISABLE);
//				ADC_AutoInjectedConvCmd(ADC1,DISABLE);
//				ADC_ConvertedValuetel[0]=ADC_ConvertedValue[0]*3.3/4096;
//				ADC_ConvertedValuetel[1]=ADC_ConvertedValue[1]*3.3/4096;
//				ADC_ConvertedValuetel[0]=(1.43-ADC_ConvertedValuetel[0])*1000/4.3+25;
//				printf("ͨ��16---%.2f v\r\n",ADC_ConvertedValuetel[0]);
//				printf("ͨ��17---%.2f v\r\n",ADC_ConvertedValuetel[1]);
//				//ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//			}
//		  Status = 	ADC_GetsoftwareStartinjectedConvStatus(ADC1);
//		  printf("״̬---%d\r\n",Status);
				
//			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
//			{
//				printf("���ڽ���ע��ͨ��");
//				ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);
//				while(ADC_GetFlagStatus(ADC1,ADC_FLAG_JEOC) == 1)
//				{
//					ADC_ClearFlag(ADC1,ADC_FLAG_JEOC);
////					printf("�Ѿ�����ע��ͨ��");
//					I[0] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);
//					I[1] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_2);
//					printf("ͨ��0---,%.2f v\r\n",I[0]);
//					printf("ͨ��1---,%.2f v\r\n",I[1]);
//				}
//			}
//			else
//			{
//				ADC_SoftwareStartInjectedConvCmd(ADC1,DISABLE);
//				ADC_ConvertedValuetel[0]=ADC_ConvertedValue[0]*3.3/4096;
//				ADC_ConvertedValuetel[1]=ADC_ConvertedValue[1]*3.3/4096;
//				ADC_ConvertedValuetel[0]=(1.43-ADC_ConvertedValuetel[0])*1000/4.3+25;
//				printf("ͨ��16---,%.2f v\r\n",ADC_ConvertedValuetel[0]);
//				printf("ͨ��17---,%.2f v\r\n",ADC_ConvertedValuetel[1]);
//			}
*/
			}
}

