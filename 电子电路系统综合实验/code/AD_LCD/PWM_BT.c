#include <reg52.h>
#include <intrins.h>              

#define Uchar unsigned char
#define Uint unsigned int
#define uchar unsigned char
#define uint unsigned int
#define Ulong unsigned long
#define ulong unsigned long

//Declare SFR associated with the ADC
sfr AUXR      = 0x8e;
sfr ADC_CONTR = 0xC5;
sfr ADC_DATA  = 0xC6;
sfr ADC_LOW2  = 0xBE;
sfr P1M0      = 0x91;
sfr P1M1      = 0x92;

//Define ADC operation const for ADC_CONTR
#define ADC_POWER   0x80
#define ADC_FLAG    0x10    
#define ADC_START   0x08
#define ADC_SPEEDLL 0x00    //00
#define ADC_SPEEDL  0x20    //01
#define ADC_SPEEDH  0x40    //10
#define ADC_SPEEDHH 0x60    //11

//定义引脚
//sbit RED = P1^0;
//sbit GREEN = P1^1;
//sbit BLUE = P1^2;
sbit D3 = P1^2;//改
sbit D1 = P1^0;
sbit D2 = P1^1;
//sbit BEEP = P1^7;
sbit LCD1602_RS = P3^2;         //1602的数据/指令选择控制线
sbit LCD1602_RW = P3^3;
sbit LCD1602_E  = P3^4;         //1602的使能控制线
#define LCD1602_DB P2            //数据端口  D0~D7

//全局变量
uint check_data = 0;
uint light_data = 0;
uint MODEL = 0;   //命令的几种模式，初始为自动转换8色
uint mod = 9;       //1-9
unsigned char R_OUT=0,G_OUT=0,B_OUT=0; //定义占空比计数变量
unsigned int MAX=200,MIN=1;           //定义变色起始级数，范围最大可以0-255
unsigned char T0RH=0,T0RL=0;         //定时器中间变量
bit time_flag0=0;       //每10ms刷新一次占空比
bit time_flag1=0;       //每2ms输出PWM
bit r_flag; 
uchar order;
uint clock;
uint enable_clock = 0;
uint enable_light = 0;
uint count = 0;


void configtime0(unsigned int ms);   //定时器0配置
void ConfigPWM(unsigned char t);     //PWM占空比处理函数
void POUT();                        //PWM输出函数 
void InitADC();
void InitUart();
void LCD1602_Init();
void Delay_ms(unsigned int nms);
void delay(unsigned int t);
void LcdWaitReady();
void LCD1602_write_cmd(unsigned char cmd);
void LCD1602_write_data(unsigned char date);
void LCD1602_Clear();//清屏
void LCD1602_SetCursor(unsigned char x,unsigned char y);  //设置光标初始位置
void LCD1602_ShowChar(unsigned char xpos,unsigned char ypos,unsigned char xsz);
void LCD1602_ShowStr(unsigned char xpos,unsigned char ypos,unsigned char *p);
void LCD1602_ShowNum(char x, char y, unsigned int num);
uint Adc(unsigned char n);
void check(uint data1);
void send(uchar i);
void judge_order();

//定时器0配置
void configtime0(unsigned int ms)
{
        unsigned long tmp;
        // tmp=11059200/12;  // 频率
        // tmp=tmp*ms/1000;  //需要多少个机器周期
        // tmp=65536-tmp;
        // T0RH=(unsigned char)(tmp>>8);
        // T0RL=(unsigned char)tmp;
        TH0=0xFC;
        TL0=0x67;
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
        TH0=0xFC;
        TL0=0x67;
        tmr0++;
        tmr1++;
        D1=tmr0%2;
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

void main()
{
        P1M0 = 0x48;
	P1M1 = 0x4F;
     InitUart();
     //InitADC();
     LCD1602_Init();
     configtime0(1);
//     RED = 0;
//     GREEN = 0;
//     BLUE = 0;
//     BEEP = 1;
    D3 = 0;
    D2 = 0;
    D1 = 0;
    MODEL=0;
    count = 0;
     AUXR |= 0x10;   //AD中断允许
     IE = 0xBA;  
    EA = 1;     //开启全局中断允许
    Delay_ms(500);

    /******************故障检测****************/
    //判断蓝灯通断
//     RED = 0;
//     GREEN = 0;
//     BLUE = 1;
//     Delay_ms(500);
//     check_data=Adc(3);
//     check(check_data);

    //判断红灯通断
//     RED = 1;
//     GREEN = 0;
//     BLUE = 0;
//     Delay_ms(500);
//     check_data=Adc(3);
//     check(check_data);
    
    //判断绿灯通断
//     RED = 0;
//     GREEN = 1;
//     BLUE = 0;
//     Delay_ms(500);
//     check_data=Adc(3);
//     check(check_data);
    /****************************************/
//     RED = 0;
//     GREEN = 0;
//     BLUE = 0;
//     Delay_ms(100);

    while (1)
    {
        //光敏AD检测和LCD输出
        //light_data=Adc(6);
        count ++;
        LCD1602_ShowStr(0,1,"Light:");
        LCD1602_ShowNum(7,1,count);
        //判断蓝牙是否接收到数据
        if(r_flag==1) //如果有数据则进入这个语句
		{
			judge_order();
			r_flag=0;
		 }
        //MOD转换
        switch(MODEL)
        {
            case 0:
                if(time_flag0 == 1)
                {
                        D3 =1;
                        Delay_ms(100);
                        D3 = 0;
                        time_flag0 = 0;
                        // ConfigPWM(1);
                }
                if(time_flag1 == 1)
                {
                        D2 =1;
                        Delay_ms(50);
                        D2 = 0;
                        time_flag1 = 0;
                        // POUT();
                }
                break;
            case 1:
                

                break;
            case 2:

                
                break;
            case 3:
                

                break;
            case 4:

                
                break;
            case 5:
                

                break;
            case 6:

                
                break;
            default:
                MODEL = 0;
                break;
        }

    }
}

void InitADC()
{
    P1M0 = 0x48;
	P1M1 = 0x4F;
    ADC_DATA = 0;
    ADC_LOW2 = 0;
    ADC_CONTR = 0x60 | 3;   //设置在check口，转换速度最高
    delay(10);
}

void InitUart()
{
    SCON = 0x5a;  //设置串口为8位可变波特率  9600
    TMOD = 0x20;
    TH1 = TL1 = 0xFD; 
    TI = 1; 
    TR1 = 1;
    ES = 1;
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

void delay(unsigned int t) //延时
{       
  	unsigned int i, j; 
  	for(i=0;i<t;i++)
	{ 
  		for(j=0;j<10;j++)
		{;} 
    } 
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

uint Adc(unsigned char n)//采集第几通道的数据
{
	unsigned char i;	
	uint result=0;

	ADC_CONTR = ADC_CONTR|0x80;  //10000000 开启转换电源
	delay(10);
	i = 0x01<<n;
    P1M0 = P1M0|i;
   	P1M1 = P1M1|i;   //采样的通道开漏
    delay(10); 
    ADC_CONTR = 0xE0|n;   //打开adc电源,设置转换速率 设置P1.n模拟通道  1110_0000|n
    delay(10);   	//延时一端时间，使输入电压达到稳定
	ADC_DATA = 0;   
	ADC_LOW2 = 0;	//清A/D转换结果寄存器
	ADC_CONTR = ADC_CONTR|0x08;  //ADC_START=1,开始转换   0000_1000
	delay(10);
    ADC_CONTR = ADC_CONTR&0xE7;  //将ADC_FLAG软件清零   1110_0111  
	result = ADC_DATA;
	result<<=2;
	result = result&0x03FC; 	//0000_0011_1111_1100
	result = result|(ADC_LOW2 & 0x03);
	return(result);				//10位的结果
}

// void check(uint data1)
// {
//     if(data1 < 15)
//     {
//         EA = 0;//关闭全局中断
//         //蓝牙发送报警
//         while(1)
//         {
//             LCD1602_ShowStr(15,1,"!");  //LCD显示感叹号
//             D3 = 1;                     //灯闪烁，蜂鸣器间歇性报警
//             BEEP = 1;
//             delay(40000);
//             D3 = 0;
//             BEEP = 0;
//             delay(40000);
//         }
//     }
//     else EA = 1;
// }

void send(uchar i)
{
	TI=0;
	SBUF=i;
	while(TI==0);
	TI=0;
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
// void POUT() 
// {
//     unsigned char cnt;  
//     for(cnt=0;cnt<MAX;cnt++)
//     {
//         if(cnt<R_OUT)
//                 RED=1;        //红色占空比大于计数值时红灯亮
//         else
//                 RED=0;        //否则就关闭红色
               
//         if(cnt<G_OUT)               
//                 GREEN=1;                //绿色占空比大于计数值时绿灯亮
//         else
//                 GREEN=0;                //否则就关闭绿色
               
//         if(cnt<B_OUT)
//                 BLUE=1;                //蓝色占空比大于计数值时蓝灯亮
//         else
//                 BLUE=0;                //否则就关闭蓝色
//     }
// }

// void judge_order()
// {
// 	MODEL = (order & 0xF0) >> 4;
// 	switch(MODEL)
// 	{
// 		case 0://固定灯效
// 			mod = order & 0x0F;
// 			break;
// 		case 1://调节红色占空比
// 			R_OUT = order & 0x0F;
// 			break;
// 		case 2://调节绿色占空比
// 			G_OUT = order & 0x0F;
// 			break;
// 		case 3://调节蓝色占空比
// 			B_OUT = order & 0x0F;
// 			break;
// 		case 4://定时开
// 			clock = order & 0x0F;
// 			enable_clock = 1;
// 			break;
// 		case 5://
// 			clock = order & 0x0F;
// 			enable_clock = 0;
// 			break;
// 		case 6://
// 			enable_light = 1;
// 			break;
// 	}

// }
void serial() interrupt 4//串行中断函数
{
	 order=SBUF; 	//将收取的数据存到a
	 r_flag=1;	//标志置位——表示单片机收到数据
	 RI=0;	 //接收标志清零
}