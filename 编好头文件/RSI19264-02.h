

#ifndef __RSI19264_H__
#define __RSI19264_H__

#include "stm32f10x.h"
#include "stdio.h"	




typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32; 
extern void lcd_init(void);
extern void send(U8 data);
extern void display_ID(void);
extern void reset(void);
extern void clear_display(void);
extern void display_on(void);
extern void display_off(void);
extern void brightness(U8 n);
extern void baud_9600(void);
extern void baud_19200(void);
extern void baud_38400(void);
extern void cusor_xy(U8 x,U8 y);
extern void inversely_on(void);
extern void inversely_off(void);
extern void print_string(U8 *ptr);
extern void print_string_xy(U8 x,U8 y,U8 *ptr);
extern void print_U32(U32 n);
extern void print_U32_xy(U8 x,U8 y,U32 n,U8 clear_num);
extern void print_string_5_7(U8 *ptr);
extern void print_string_xy_5_7(U8 x,U8 y,U8 *ptr);
extern void print_U32_5_7(U32 n);
extern void print_U32_xy_5_7(U8 x,U8 y,U32 n);
extern void inversely_area(U8 x1,U8 y1,U8 x2,U8 y2);
extern void display_bmp(U16 n);
extern void display_bmp_block(U16 n,U8 px,U8 py,U8 x,U8 y,U8 w,U8 h);
extern void keyscan_enable(void);
extern void keyscan_disable(void);
extern void kescan_single(void);
extern void kescan_continuous(void);
extern void kescan_continuous_cycle(U8 n);
#endif


