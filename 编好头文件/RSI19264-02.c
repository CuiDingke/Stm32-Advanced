/**
  *****************************************************************************
  * @文件名: main.c
  * @编者：  4406工作室
  * @版本：  V1.1.0
  * @日期：  2016年3月14日
  * @说明：  lcd19264运行程序
  * @注意：未经许可不得用于其它任何用途，版权所有，盗版必究
  *****************************************************************************
	**/
#include "RSI19264-02.h"


////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
u32 lcd_i;
void lcd_init(void)
{

	reset();
	for(lcd_i = 0;lcd_i < 0xfffff;lcd_i++);	
	display_on();
	for(lcd_i = 0;lcd_i < 0xfff;lcd_i++);	
	brightness(0xff);
	for(lcd_i = 0;lcd_i < 0xfff;lcd_i++);
	clear_display();
	for(lcd_i = 0;lcd_i < 0xfff;lcd_i++);
//	print_string_xy(0,0,"  滴速20  /min细  按键");
//	print_string_xy(0,2,"  实速   .   滴数");
//	print_string_xy(0,4,"  瓶数  总瓶数  状态  ");
//	print_string_xy(0,6,"  角度");
	
}
void send(U8 data)
{
	USART_SendData(USART3,data);
  while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==0);
}

//-----------------------显示产品信息--------------------------
void display_ID()      
{
    send(0xaa);
    send(0x00);
}
//---------------------------复位------------------------------
void reset()
{
    send(0xaa);
    send(0x01);
}

//------------------------显示清屏-----------------------------
void clear_display()
{
    send(0xaa);
    send(0x10);
}
//------------------------打开显示-----------------------------
void display_on()
{
    send(0xaa);
    send(0x11);
}
//------------------------关闭显示-----------------------------
void display_off()
{
    send(0xaa);
    send(0x12);
}
//------------------------设置背光亮度-------------------------
void brightness(U8 n)
{
    send(0xaa);
    send(0x13);
    send(n);
}
//------------------------波特率设为9600------------------------
void baud_9600()
{
    send(0xaa);
    send(0x14);
}
//------------------------波特率设为19200------------------------
void baud_19200()
{
    send(0xaa);
    send(0x15);
}
//------------------------波特率设为38400------------------------
void baud_38400()
{
    send(0xaa);
    send(0x16);
}

//-------------------光标设置------------------------------------
void cusor_xy(U8 x,U8 y)
{
    send(0xaa);
    send(0x20);
    send(x);
    send(y);
}
//----------------字符反白显示功能打开------------------------
void inversely_on()
{
    send(0xaa);
    send(0x21);
}
//----------------字符反白显示功能关闭------------------------
void inversely_off()
{
    send(0xaa);
    send(0x22);
}


//-------------------在当前光标处显示字符串-------------------
void print_string(U8 *ptr)
{
    send(0xaa);
    send(0x23);
    while(*ptr!='\0')
    {
        send(*ptr++);             
    }
    send(0X0d);
}
//-------------------在指定位置显示字符串---------------------
void print_string_xy(U8 x,U8 y,U8 *ptr)
{
    send(0xaa);	
    send(0x20);
    send(x);
    send(y);
    send(0xaa);
    send(0x23);
    while(*ptr!='\0')
    {
        send(*ptr++);             
    }
    send(0X0d);
}
//-----------------在当前光标处显示长整型变量-----------------
void print_U32(U32 n)
{
    U32 i,temp;
    U8 t=0;
    send(0xaa);
    send(0x23);
	if(n==0)
	{
        send(0x30);
	}
	else
	{
        for(i=1000000000;i>=1;i=i/10)
        {
            temp=n/i;
            if(t==0&&temp)
            {
                send(temp%10+0x30);
                t=1;
            }
            else if(t==1)
            {
                send(temp%10+0x30);
            }
		}
    }
    send(0x0d);
}
//-----------------在指定光标处显示长整型变量-----------------
void print_U32_xy(U8 x,U8 y,U32 n,U8 clear_num)
{
    U32 i,temp;
    U8 t=0;
		while(clear_num--)
		{
			print_string_xy(x+(clear_num-1)*16+16,y,"  ");
		}	
    send(0xaa);
    send(0x20);
    send(x);
    send(y);

    send(0xaa);
    send(0x23);
    if(n==0)
	{
        send(0x30);
	}
	else
	{
        for(i=1000000000;i>=1;i=i/10)
        {
            temp=n/i;
            if(t==0&&temp)
            {
                send(temp%10+0x30);
                t=1;
            }
            else if(t==1)
            {
                send(temp%10+0x30);
            }
		}
    }
    send(0x0d);
}
//-------------------在当前光标处显示字符串，使用5*7字体-------------------
void print_string_5_7(U8 *ptr)
{
    send(0xaa);
    send(0x24);
    while(*ptr!='\0')
    {
        send(*ptr++);             
    }
    send(0X0d);
}
//-------------------在指定位置显示字符串，使用5*7字体---------------------
void print_string_xy_5_7(U8 x,U8 y,U8 *ptr)
{
    send(0xaa);	
    send(0x20);
    send(x);
    send(y);
    send(0xaa);
    send(0x24);
    while(*ptr!='\0')
    {
        send(*ptr++);             
    }
    send(0X0d);
}
//-----------------在当前光标处显示长整型变量，使用5*7字体-----------------
void print_U32_5_7(U32 n)
{
    U32 i,temp;
    U8 t=0;
    send(0xaa);
    send(0x24);
	if(n==0)
	{
        send(0x30);
	}
	else
	{
        for(i=1000000000;i>=1;i=i/10)
        {
            temp=n/i;
            if(t==0&&temp)
            {
                send(temp%10+0x30);
                t=1;
            }
            else if(t==1)
            {
                send(temp%10+0x30);
            }
		}
    }
    send(0x0d);
}
//-----------------在指定光标处显示长整型变量，使用5*7字体-----------------
void print_U32_xy_5_7(U8 x,U8 y,U32 n)
{
    U32 i,temp;
    U8 t=0;
    send(0xaa);
    send(0x20);
    send(x);
    send(y);

    send(0xaa);
    send(0x24);
    if(n==0)
	{
        send(0x30);
	}
	else
	{
        for(i=1000000000;i>=1;i=i/10)
        {
            temp=n/i;
            if(t==0&&temp)
            {
                send(temp%10+0x30);
                t=1;
            }
            else if(t==1)
            {
                send(temp%10+0x30);
            }
		}
    }
    send(0x0d);
}

//---------------指定区域反白显示--------------------
void inversely_area(U8 x1,U8 y1,U8 x2,U8 y2)
{
    send(0xaa);
    send(0x30);
    send(x1);
    send(y1);
    send(x2);
    send(y2);
}
//--------------按序列号显示图片-------------------
void display_bmp(U16 n)
{
    send(0xaa);
    send(0x31);
    send(n>>8);
    send(n);
}
//-------------块方式显示图片-------------------------
void display_bmp_block(U16 n,U8 px,U8 py,U8 x,U8 y,U8 w,U8 h)
{
    send(0xaa);
    send(0x32);
    send(n>>8);
    send(n);
    send(x);
    send(y);
		send(px);
    send(py);
    send(w);
    send(h);
}
//------------使能按键扫描功能-------------------------
void keyscan_enable()
{
    send(0xaa);
    send(0x50);
}
//------------禁止按键扫描功能-------------------------
void keyscan_disable()
{
    send(0xaa);
    send(0x51);
}
//------------单次触发模式-------------------------
void kescan_single()
{
    send(0xaa);
    send(0x52);
}
//------------连续触发模式-------------------------
void kescan_continuous()
{
    send(0xaa);
    send(0x53);
}
//------------连续触发周期-------------------------
void kescan_continuous_cycle(U8 n)
{
    send(0xaa);
    send(0x54);
    send(n);
}


