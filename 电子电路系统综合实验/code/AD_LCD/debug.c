#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int
#define LCD1602_DB P2            //数据端口  D0~D7

sbit R_LED=P1^0;                //红灯引脚，高电平时点亮LED
sbit G_LED=P1^1;               //绿灯引脚，高电平时点亮LED
sbit B_LED=P1^2;                //蓝灯引脚，高电平时点亮LED
sbit LCD1602_RS = P3^2;         //1602的数据/指令选择控制线
sbit LCD1602_RW = P3^3;
sbit LCD1602_E  = P3^4;         //1602的使能控制线

//Declare SFR associated with the ADC
sfr AUXR      = 0x8e;
sfr ADC_CONTR = 0xC5;
sfr ADC_DATA  = 0xC6;
sfr ADC_LOW2  = 0xBE;
sfr P1M0      = 0x91;
sfr P1M1      = 0x92;

unsigned char R_OUT=0,G_OUT=0,B_OUT=0; //定义占空比计数变量
unsigned int MAX=200,MIN=1;           //定义变色起始级数，范围最大可以0-255
unsigned char T0RH=0,T0RL=0;         //定时器中间变量
bit time_flag0=0;       //每10ms刷新一次占空比
bit time_flag1=0;       //每2ms输出PWM
uint count;

void LedInit(void);
void configtime0(unsigned int ms);   //定时器0配置
void ConfigPWM(unsigned char t);     //PWM占空比处理函数
void POUT();
void LCD1602_Init();   
void LcdWaitReady();
void LCD1602_write_cmd(unsigned char cmd);
void LCD1602_write_data(unsigned char date);
void LCD1602_Clear();//清屏
void LCD1602_SetCursor(unsigned char x,unsigned char y);  //设置光标初始位置
void LCD1602_ShowChar(unsigned char xpos,unsigned char ypos,unsigned char xsz);
void LCD1602_ShowStr(unsigned char xpos,unsigned char ypos,unsigned char *p);
void LCD1602_ShowNum(char x, char y, unsigned int num);                         //PWM输出函数
void Delay_ms(unsigned int nms);

void LedInit(void)
{
    P1M0 = 0x48;
	P1M1 = 0x4F;
}

main()
{        
        LedInit();
    LCD1602_Init();//LCD初始化
        configtime0(1);
        EA=1;
        count = 0;
        while(1)
        {
            count++;
            LCD1602_ShowNum(7,1,count);
                if(time_flag0 == 1)
                {
                        time_flag0 = 0;
                        ConfigPWM(1);
                }
                if(time_flag1 == 1)
                {
                        time_flag1 = 0;
                        POUT();
                }

        }
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
                        if(dir==0)                //橙色由暗变亮
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
                        else                        //橙色由亮变暗
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
                        if(dir==0)                //黄色由暗变亮
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
                        else                        //黄色由亮变暗
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

//输出占空比
void POUT() 
{
    unsigned char cnt;
        
    for(cnt=0;cnt<MAX;cnt++)
    {
        if(cnt<R_OUT)
                R_LED=1;        //红色占空比大于计数值时红灯亮
        else
                R_LED=0;        //否则就关闭红色
               
        if(cnt<G_OUT)               
                G_LED=1;                //绿色占空比大于计数值时绿灯亮
        else
                G_LED=0;                //否则就关闭绿色
               
        if(cnt<B_OUT)
                B_LED=1;                //蓝色占空比大于计数值时蓝灯亮
        else
                B_LED=0;                //否则就关闭蓝色
    }
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

//定时器0中断涵数
void timer0() interrupt 1   //1ms中断
{
        static unsigned int tmr0;
        static unsigned int tmr1;
        TH0=T0RH;
        TL0=T0RL;
        tmr0++;
        tmr1++;

        if(tmr0>=10)  //每10ms刷新一次占空比
        {
                tmr0=0;
                time_flag0=1;
        }
        if(tmr1>=2)  //2ms输出PWM
        {
                tmr1=0;
                time_flag1=1;
        }
}

void LCD1602_Init()    //1602初始化函数 
{
    LCD1602_write_cmd(0x01);    //显示清屏
    LCD1602_write_cmd(0x38);    //显示模式设置
    LCD1602_write_cmd(0x0C);    //显示开及光标设置
    LCD1602_write_cmd(0x06);    //显示光标移动位置
}

void LcdWaitReady()    /* 等待液晶准备好 */
{
    unsigned char sta;
    
    LCD1602_DB = 0xFF;
    LCD1602_RS = 0;
    LCD1602_RW = 1;       //读状态
    do {
        LCD1602_E = 1;
        sta = LCD1602_DB; //读取状态字
        LCD1602_E = 0;
    } while (sta & 0x80); //bit7等于1表示液晶正忙，重复检测直到其等于0为止
}

void LCD1602_write_cmd(unsigned char cmd)    //写命令函数
{
    LcdWaitReady();
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DB = cmd;
    LCD1602_E  = 1;
    Delay_ms(10);
    LCD1602_E  = 0;
}

void LCD1602_write_data(unsigned char date)    //写数据函数 
{
    LcdWaitReady();
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DB = date;
    LCD1602_E  = 1;
    Delay_ms(10);
    LCD1602_E  = 0;
}

void LCD1602_Clear()    //1602清屏函数
{
    LCD1602_write_cmd(0x01);
}

void LCD1602_SetCursor(unsigned char x,unsigned char y)//设置1602光标位置函数
{
    unsigned char addr;
    if(y==0)     //由输入的屏幕坐标计算显示RAM的地址
        addr=0x00+x;
    else
        addr=0x40+x;
    LCD1602_write_cmd(addr | 0x80);//设置RAM地址
}

void LCD1602_ShowNum(char x, char y, unsigned int num)  //指定位置显示数字函数
{
    unsigned int i,j,k,l,n;
    i=num/10000;
    j=(num-10000*i)/1000;
    k=(num-10000*i-1000*j)/100;
    l=(num-10000*i-1000*j-100*k)/10;
    n=num%10;
    LCD1602_SetCursor(x,y);  //设置起始地址
    if(i!=0)LCD1602_write_data(i+0x30);
    if((i!=0)||(j!=0))LCD1602_write_data(j+0x30);
    if((i!=0)||(j!=0)||(k!=0))LCD1602_write_data(k+0x30);
    if((i!=0)||(j!=0)||(k!=0)||(l!=0))LCD1602_write_data(l+0x30);
    LCD1602_write_data(n+0x30);
}

void LCD1602_ShowChar(unsigned char xpos,unsigned char ypos,char xsz)    //指定位置显示字符函数
{
    ypos%=2;
    if(ypos==0)
    {
        LCD1602_write_cmd(0x80+xpos);
    }
    else
    {
        LCD1602_write_cmd(0x80+0x40+xpos);
    }
    LCD1602_write_data(xsz);
}

void LCD1602_ShowStr(unsigned char xpos,unsigned char ypos,char *p) //指定位置显示字符串函数
{
    if(ypos>1)return;
    while(*p!='\0')
    {
        LCD1602_ShowChar(xpos++,ypos,*p++);
        if(*p=='\n')
        {
            xpos=0;
            ypos++;
            p++;
        }
    }
}

void Delay_ms(unsigned int nms)        //@11.0592MHz   nms为要延时的ms数  
{
    unsigned char i, j;    
    while(nms--)
    {
        i = 15;
        j = 90;
        do
        {
            while (--j);
        } while (--i);
    }
}
