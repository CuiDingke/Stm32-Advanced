#include  "BSP_USART.h"
void USART1_conf(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

int fputc(int ch, FILE *f)
{
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}
  return ch;
}
uint8_t USART_Scanf(uint32_t value)
{
  uint32_t index = 0;
  uint32_t tmp[2] = {0, 0};

  while (index < 2)
  {
    /* Loop until RXNE = 1 */
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {}
    tmp[index++] = (USART_ReceiveData(USART1));
    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
      printf("\n\rPlease enter valid number between 0 and 9");
      index--;
    }
  }
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
  if (index > value)
  {
    printf("\n\rPlease enter valid number between 0 and %d", value);
    return 0xFF;
  }
  return index;
}
