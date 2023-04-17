#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

//sbit LED0=P1^0;// 用sbit 关键字 定义 LED到P1.0端口，LED是自己任意定义且容易记忆的符号
sbit P20=P1^3;
sbit LED1 = P2^6;
sbit LED2 = P2^7;
sbit LED3 = P2^1;

void Delay(unsigned int t); //函数声明
/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
    //unsigned int kk;                  
    unsigned int CYCLE=1,PWM_LOW=0;//定义周期并赋值		//	 
    while (1)         //主循环
    {
        if(P20==0)
        {
            Delay(3);
            if(P20==0)
            {
                CYCLE=CYCLE+100;
                if(CYCLE==1101)
                {
                    CYCLE=1;
                }
                while(P20==0);
            }
        }
        //P1=0XFF;// LED0=1;
        LED1 = 1;
        LED2 = 1;
        LED3 = 1; 
        //点亮LED  
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        Delay(CYCLE);//延时长度
        //熄灭LED
        LED1 = 1;
        LED2 = 1;
        LED3 = 1;
        Delay(1200-CYCLE);//延时长度
                        //主循环中添加其他需要一直工作的程序
    }
}
/*------------------------------------------------
 延时函数，含有输入参数 unsigned int t，无返回值
 unsigned int 是定义无符号整形变量，其值的范围是
 0~65535
------------------------------------------------*/
void Delay(unsigned int t)
{
 while(--t);
}