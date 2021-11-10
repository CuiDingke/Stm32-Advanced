/**
  *****************************************************************************
  * @�ļ���: main.c
  * @���ߣ�  4406������
  * @�汾��  V1.1.0
  * @���ڣ�  2016��3��14��
  * @˵����  lcd19264���г���
  * @ע�⣺δ����ɲ������������κ���;����Ȩ���У�����ؾ�
  *****************************************************************************
	**/
#include "RSI19264-02.h"


////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
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
//	print_string_xy(0,0,"  ����20  /minϸ  ����");
//	print_string_xy(0,2,"  ʵ��   .   ����");
//	print_string_xy(0,4,"  ƿ��  ��ƿ��  ״̬  ");
//	print_string_xy(0,6,"  �Ƕ�");
	
}
void send(U8 data)
{
	USART_SendData(USART3,data);
  while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==0);
}

//-----------------------��ʾ��Ʒ��Ϣ--------------------------
void display_ID()      
{
    send(0xaa);
    send(0x00);
}
//---------------------------��λ------------------------------
void reset()
{
    send(0xaa);
    send(0x01);
}

//------------------------��ʾ����-----------------------------
void clear_display()
{
    send(0xaa);
    send(0x10);
}
//------------------------����ʾ-----------------------------
void display_on()
{
    send(0xaa);
    send(0x11);
}
//------------------------�ر���ʾ-----------------------------
void display_off()
{
    send(0xaa);
    send(0x12);
}
//------------------------���ñ�������-------------------------
void brightness(U8 n)
{
    send(0xaa);
    send(0x13);
    send(n);
}
//------------------------��������Ϊ9600------------------------
void baud_9600()
{
    send(0xaa);
    send(0x14);
}
//------------------------��������Ϊ19200------------------------
void baud_19200()
{
    send(0xaa);
    send(0x15);
}
//------------------------��������Ϊ38400------------------------
void baud_38400()
{
    send(0xaa);
    send(0x16);
}

//-------------------�������------------------------------------
void cusor_xy(U8 x,U8 y)
{
    send(0xaa);
    send(0x20);
    send(x);
    send(y);
}
//----------------�ַ�������ʾ���ܴ�------------------------
void inversely_on()
{
    send(0xaa);
    send(0x21);
}
//----------------�ַ�������ʾ���ܹر�------------------------
void inversely_off()
{
    send(0xaa);
    send(0x22);
}


//-------------------�ڵ�ǰ��괦��ʾ�ַ���-------------------
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
//-------------------��ָ��λ����ʾ�ַ���---------------------
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
//-----------------�ڵ�ǰ��괦��ʾ�����ͱ���-----------------
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
//-----------------��ָ����괦��ʾ�����ͱ���-----------------
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
//-------------------�ڵ�ǰ��괦��ʾ�ַ�����ʹ��5*7����-------------------
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
//-------------------��ָ��λ����ʾ�ַ�����ʹ��5*7����---------------------
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
//-----------------�ڵ�ǰ��괦��ʾ�����ͱ�����ʹ��5*7����-----------------
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
//-----------------��ָ����괦��ʾ�����ͱ�����ʹ��5*7����-----------------
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

//---------------ָ�����򷴰���ʾ--------------------
void inversely_area(U8 x1,U8 y1,U8 x2,U8 y2)
{
    send(0xaa);
    send(0x30);
    send(x1);
    send(y1);
    send(x2);
    send(y2);
}
//--------------�����к���ʾͼƬ-------------------
void display_bmp(U16 n)
{
    send(0xaa);
    send(0x31);
    send(n>>8);
    send(n);
}
//-------------�鷽ʽ��ʾͼƬ-------------------------
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
//------------ʹ�ܰ���ɨ�蹦��-------------------------
void keyscan_enable()
{
    send(0xaa);
    send(0x50);
}
//------------��ֹ����ɨ�蹦��-------------------------
void keyscan_disable()
{
    send(0xaa);
    send(0x51);
}
//------------���δ���ģʽ-------------------------
void kescan_single()
{
    send(0xaa);
    send(0x52);
}
//------------��������ģʽ-------------------------
void kescan_continuous()
{
    send(0xaa);
    send(0x53);
}
//------------������������-------------------------
void kescan_continuous_cycle(U8 n)
{
    send(0xaa);
    send(0x54);
    send(n);
}


