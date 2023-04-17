#include<reg52.h>

sfr P2M1=0x95;
sfr P2M0=0x96;
sbit R_LED=P2^6;                //红灯引脚，低电平时点亮LED
sbit G_LED=P2^7;                //绿灯引脚，低电平时点亮LED
sbit B_LED=P2^1;                //蓝灯引脚，低电平时点亮LED

unsigned char R_OUT=0,G_OUT=0,B_OUT=0; //定义占空比计数变量
unsigned int MAX=255,MIN=1;           //定义变色起始级数，范围最大可以0-255
unsigned char T0RH=0,T0RL=0;         //定时器中间变量
void configtime0(unsigned int ms);   //定时器0配置
void configtime1();                  //定时器1配置
void ConfigPWM(unsigned char t);     //PWM占空比处理函数

void LedInit(void)
{
        P2M1 &= 0<<1;
        P2M1 &= 0<<6;
        P2M1 &= 0<<7;
        P2M0 |= 1<<1;
        P2M0 |= 1<<6;
        P2M0 |= 1<<7;
}

main()
{        
        LedInit();
        EA=1;
        configtime0(1);
        configtime1();
        while(1);
}

//每调用一次此涵数，PWM占空比加一
void ConfigPWM(unsigned char t)  //PWM占空比处理函数
{
        static unsigned char dir=0;    //定义变亮或变暗方向
        static unsigned char index=0;  //定义变色索引
        static unsigned int time=0;    //中间变量

        switch(index)
        {
				case 0: 
                        if(dir==0)      //红色由暗变亮
                        {
                                time+=t;
                                R_OUT=time;
				G_OUT=0;
                                B_OUT=0;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else         //红色由亮变暗
                        {
                                time-=t;
                                R_OUT=time;
				G_OUT=0;
                                B_OUT=0;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=1;
                                }
                        }
                        break;
                                       
                case 1:            
                        if(dir==0)                //黄色由暗变亮
                        {
                                time+=t;
                                R_OUT=time;
				G_OUT=time/2;
                                B_OUT=0;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //黄色由亮变暗
                        {
                                time-=t;
                                R_OUT=time;
				G_OUT=time/2;
                                B_OUT=0;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=2;
                                }
                        }
                        break;
                                       
                case 2:            
                        if(dir==0)                //橙色由暗变亮
                        {
                                time+=t;
                                R_OUT=time;
                                G_OUT=time;
                                B_OUT=0;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //橙色由亮变暗
                        {
                                time-=t;
                                R_OUT=time;
                                G_OUT=time;
                                B_OUT=0;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=3;
                                }
                        }
                        break;
                                       
                case 3:            
                        if(dir==0)                //绿色由暗变亮
                        {
                                time+=t;
                                R_OUT=0;
                                G_OUT=time;
                                B_OUT=0;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //绿色由亮变暗
                        {
                                time-=t;
                                R_OUT=0;
                                G_OUT=time;
                                B_OUT=0;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=4;
                                }
                        }
                        break;
                                       
                case 4:           
                        if(dir==0)                //青色由暗变亮
                        {
                                time+=t;
                                R_OUT=0;
                                G_OUT=time;
                                B_OUT=time;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //青色由亮变暗
                        {
                                time-=t;
                                R_OUT=0;
                                G_OUT=time;
                                B_OUT=time;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=5;
                                }
                        }
                        break;
                                       
                case 5:            
                        if(dir==0)                //蓝色由暗变亮
                        {
                                time+=t;
                                R_OUT=0;
                                G_OUT=0;
                                B_OUT=time;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //蓝色由亮变暗
                        {
                                time-=t;
                                R_OUT=0;
                                G_OUT=0;
                                B_OUT=time;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=6;
                                }
                        }
                        break;
                                       
                case 6:            
                        if(dir==0)                //紫色由暗变亮
                        {
                                time+=t;
                                R_OUT=time;
                                G_OUT=0;
                                B_OUT=time;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //紫色由亮变暗
                        {
                                time-=t;
                                R_OUT=time;
                                G_OUT=0;
                                B_OUT=time;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=7;
                                }
                        }
                        break;
                                       
                case 7:            
                        if(dir==0)                //白色由暗变亮
                        {
                                time+=t;
                                G_OUT=time;
                                B_OUT=time;
                                R_OUT=time;
                                if(time>=MAX)
                                {
                                        dir=1;
                                }
                        }
                        else                        //白色由亮变暗
                        {
                                time-=t;
                                G_OUT=time;
                                B_OUT=time;
                                R_OUT=time;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        index=0;
                                }
                        }
                        break;
			           
        }
}
//定时器1配置
void configtime1()
{
        TH1=0x80;
        TL1=TH1;
        TMOD&=0x0f;
        TMOD|=0x20;
        TR1=1;    //定时器1开始运行
        ET1=1;    //定时器1的中断
}
//定时器0配置
void configtime0(unsigned int ms)
{
        unsigned long tmp;
        tmp=11059200/12;  // 频率
        tmp=tmp*ms/1000;  //需要多少个机器周期
        tmp=65536-tmp;
        T0RH=(unsigned char)(tmp>>8);
        T0RL=(unsigned char)tmp;
        TH0=T0RH;
        TL0=T0RL;
        TMOD&=0xf0;
        TMOD|=0x01;
        TR0=1;
        ET0=1;
}
//定时器0中断涵数，每5ms刷新一次占空比
void timer0() interrupt 1
{
        static unsigned int tmr;
        TH0=T0RH;
        TL0=T0RL;
        tmr++;
        if(tmr>=5)
        {
                tmr=0;
                ConfigPWM(1);
        }
}
//定时器1中断涵数，输出占空比
void timer1() interrupt 3
{
    unsigned char cnt;
        
    for(cnt=0;cnt<MAX;cnt++)
    {
        if(cnt<R_OUT)
                R_LED=0;        //红色占空比大于计数值时红灯亮
        else
                R_LED=1;        //否则就关闭红色
               
        if(cnt<G_OUT)               
                G_LED=0;                //绿色占空比大于计数值时绿灯亮
        else
                G_LED=1;                //否则就关闭绿色
               
        if(cnt<B_OUT)
                B_LED=0;                //蓝色占空比大于计数值时蓝灯亮
        else
                B_LED=1;                //否则就关闭蓝色
    }
}