#include<reg52.h>
    sbit red = P1^0;
    sbit green = P1^1;
    sbit blue = P1^2;
    sbit BEEP = P1^7;
    unsigned int state;
    unsigned int i;
    unsigned long Timer_Count;
    unsigned int timer_flag;

void Timer0_Init (void)
{
   TR0 = 0;				//停止计数
   ET0 = 1;				//允许中断
   PT0 = 1;				//高优先级中断
   TMOD = 0x01;			//#00000,0001,16位定时模式
   
   TH0 = 0;
   TL0 = 0;
   TR0 = 1;				//开始运行
}

void Init_Device(void)
{
	Timer0_Init();

    EA = 1;					//开启全局中断允许
}

void timer0_int (void) interrupt 1
{
	TH0 = 0xfc;
	TL0 = 0x18;			//1ms定时中断

	++Timer_Count;
	if (Timer_Count > 1000)
	{
		Timer_Count = 0;
		timer_flag = 1;
	}

}

void main(){
    Init_Device();
    state = 0;
    BEEP = 0;
    do{
        if(timer_flag)
        {
            timer_flag = 0;
            state++;
            state = state % 3;

            switch (state)
            {
            case 0:
                red = 1;
                green = 0;
                blue = 0;
                break;
            case 1:
                red = 0;
                green = 1;
                blue = 0;
                break;
            case 2:
                red = 0;
                green = 0;
                blue = 1;
                break;
            default:
                red = 0;
                green = 0;
                blue = 0;
                break;
            }

        }
        
    }while(1);
}