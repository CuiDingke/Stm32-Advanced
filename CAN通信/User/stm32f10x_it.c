#include "stm32f10x_it.h"

CanRxMsg RxMessage;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0) == 1)
	{
		CAN_Receive(CAN1, 0, &RxMessage);
	}
	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
}
