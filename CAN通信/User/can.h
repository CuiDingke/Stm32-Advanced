#ifndef __CAN_H
#define __CAN_H	     
#include "stm32f10x.h"
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
 
u8 Can_Send_Msg(u8* msg,u8 len);						//发送数据
u8 CAN_TxMessageInit(uint32_t std_id, uint32_t ext_id, uint8_t ide, uint8_t rtr, uint8_t dlc, uint8_t *pdata);
u8 Can_Receive_Msg(u8 *buf);							//接收数据
#endif

















