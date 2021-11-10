#include "rs485.h"	 
void RS485_Init(void)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOA,D时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //PD7端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	USART_InitStructure.USART_BaudRate = 115200;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据长度
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;///奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
  USART_Init(USART2, &USART_InitStructure); ; //初始化串口
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//开启中断
  USART_Cmd(USART2, ENABLE);                    //使能串口 

  RS485_RX_EN;			//默认为接收模式
 
}


void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN;
  for(t=0;t<len;t++)
	{		   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  //切记 如果初始化串口,串口TC位为1 
		USART_SendData(USART2,buf[t]);                                //如果开TC中断  先进TC中断 一定要清楚标志位 否则一直在中断里
	}	 
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		 
	RS485_RX_EN;
}

