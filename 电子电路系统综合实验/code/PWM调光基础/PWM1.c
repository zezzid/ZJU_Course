/*******************************************************************************
* 版  权 	: 红梅科技工作室
* 论  坛	：https://blog.csdn.net/Qingzhusshuiyun
* Q Q	    ：2369099714
* 版权所有，盗版必究。
* 工  程   : PWM调光
* 文件名   : PWM调光.c
* 处理器   : STC89C52RC
* 编译环境 : Keil 5
* 系统时钟 : 12MHZ
* 版    本	: V1.0 
* 生成日期	: 2018-05-14	   					
* 修改日期	:  
* 简单描述 : 通过PWM（脉宽调制）调节LED的亮度
*******************************************************************************/

#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

//sbit LED0=P1^0;// 用sbit 关键字 定义 LED到P1.0端口，LED是自己任意定义且容易记忆的符号
sbit P20=P1^3;
sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^2;

void Delay(unsigned int t); //函数声明
/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
    //unsigned int kk;                  
    unsigned int CYCLE=100,PWM_LOW=0;//定义周期并赋值		//	 
    while (1)         //主循环
    {
        if(P20==0)
        {
            Delay(3);
            if(P20==0)
            {
                CYCLE=CYCLE+100;
                if(CYCLE==600)
                {
                    CYCLE=100;
                }
                while(P20==0);
            }
        }
        //P1=0XFF;// LED0=1;
        LED1 = 1;
        //Delay(60000);        //特意加延时，可以看到熄灭的过程
        for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
        { //PWM_LOW表示低
        //电平时间，这个循环中低电平时长从1累加到CYCLE（周期）的值，即600次

            //P1=0X00;   	//	LED0=0;        //点亮LED  
            LED1 = 0;
            Delay(PWM_LOW);//延时长度，600次循环中从1加至599
            //P1=0XFF;   	//	LED0=1;        //熄灭LED
            LED1 = 1;
            Delay(CYCLE-PWM_LOW);//延时长度，600次循环中从599减至1
                
        }
        //P1=0X00;// LED0=0;
        LED1 = 0;
        for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
        { //与逐渐变亮相反的过程

            //P1=0X00;   	//	LED0=0;
            LED1 = 0;
            Delay(PWM_LOW);
            //P1=0XFF;   	//	LED0=1;
            LED1 = 1;
            Delay(CYCLE-PWM_LOW);
            
        }
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