#ifndef __MYIIC_H
#define __MYIIC_H
#include  "stdint.h"
//IO��������
#define   Port_IIC    GPIOB
#define   IIC_SCL_Pin GPIO_Pin_6
#define   IIC_SDA_Pin GPIO_Pin_7
#define   PORT_CLK  RCC_APB2Periph_GPIOB
//IO��������	 
//#define IIC_SCL    PBout(6) //SCL
#define IIC_SCL_1    GPIO_SetBits(Port_IIC,IIC_SCL_Pin ) 
#define IIC_SCL_0    GPIO_ResetBits(Port_IIC,IIC_SCL_Pin ) 
#define IIC_SDA_1    GPIO_SetBits(Port_IIC,IIC_SDA_Pin )  //SDA	
#define IIC_SDA_0    GPIO_ResetBits(Port_IIC,IIC_SDA_Pin )  //SDA	
//#define READ_SDA   PBin(7)  //����SDA 
#define READ_SDA   GPIO_ReadInputDataBit(Port_IIC,IIC_SDA_Pin )

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















