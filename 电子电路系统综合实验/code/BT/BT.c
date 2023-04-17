/**************************************************
*串口通信实验：收发（数据转发功能：单片机收到了电脑发送的数据后又转发回给电脑）
**************************************************/
#include<reg51.h>
#define uchar unsigned char 
#define uint unsigned int
sbit D3 = P1^4;
uchar order;
uint MODEL;
uint mod;
uint R_OUT;
uint G_OUT;
uint B_OUT;
uint clock;
uint enable_clock = 0;
uint enable_light = 0;
bit r_flag;				//设置全局变量

void judge_order();

void main()
{
	D3 = 0;
    SCON=0X50;	//REN=1允许接收状态 串口方式1
	TMOD=0X20;	//定时器1定时方式2
	TH1=0XFD;	//11.0592M	9600波特率 数据位8 停止位1
	TL1=0xFD;
	TI=1;		//串口发送标志
	TR1=1;		//启动定时器
	EA=1;		//开总中断
	ES=1;		//开串中断
	while(1)
	{
		if(r_flag==1)		//如果有数据则进入这个语句
		{
			judge_order();
            r_flag=0;
		}
	}
}

void judge_order()
{
    MODEL = (order & 0xF0) >> 4;
    switch(MODEL)
    {
        case 0://固定灯效
            mod = order & 0x0F;
            break;
        case 1://调节红色占空比
            R_OUT = order & 0x0F;
            break;
        case 2://调节绿色占空比
            G_OUT = order & 0x0F;
            break;
        case 3://调节蓝色占空比
            B_PUT = order & 0x0F;
            break;
        case 4://定时开
            clock = order & 0x0F;
            enable_clock = 1;
            break;
        case 5://
            clock = order & 0x0F;
            enable_clock = 0;
            break;
        case 6://
            enable_light = 1;
            break;
    }

}
void serial() interrupt 4//串行中断函数
{
	order=SBUF;				//将收取的数据存到a
	r_flag=1;				//标志置位——表示单片机收到数据
	RI=0;				//接收标志清零
}
