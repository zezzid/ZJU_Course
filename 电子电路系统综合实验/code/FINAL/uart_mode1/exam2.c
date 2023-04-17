#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

#define LCD1602_DB P2            //数据端口  D0~D7

sfr AUXR      = 0x8e;
sfr ADC_CONTR = 0xC5;
sfr ADC_DATA  = 0xC6;
sfr ADC_LOW2  = 0xBE;
sfr P1M0      = 0x91;
sfr P1M1      = 0x92;

sbit RED = P1^0;
sbit GREEN = P1^1;
sbit BLUE = P1^2;
sbit BEEP = P1^7;
sbit D3 = P1^4;
sbit LCD1602_RS = P3^2;         //1602的数据/指令选择控制线
sbit LCD1602_RW = P3^3;
sbit LCD1602_E  = P3^4;         //1602的使能控制线

uint pwm_out_flag = 0;
uint pwm_renew_flag = 0;
uint clock_flag = 0;
uchar order = 0;
uchar R_OUT = 0, G_OUT = 0, B_OUT = 0; //定义占空比计数变量
uint MAX=200,MIN=1;           //定义变色起始级数，范围最大可以0-200
uint mod = 9;
uint MODEL = 0;
uint info;
uint light_data;
uchar index = 0;
uint clock;

void ConfigUART(unsigned int baud)
{
 	SCON = 0X50;   //串口方式1
	TMOD &= 0X0F; //定时器T1 ，工作方式 2 
	TMOD |= 0X20;
	TH1 = 256 - (11059200/12/32)/baud;
	TL1 = TH1;

	ET1 = 0;   //  使用T1做波特率发生器，就要关了T1的定时中断
	ES = 1;	   // 串口中断打开
	TR1 = 1;   //  T1开始定时
}

void timer0init()//1ms中断
{
	TMOD &= 0XF0;  //定时器T0，工作方式16位定时
	TMOD |= 0X01;
	TH0 = 0XFC;
	TL0 = 0X67;
	TR0 = 1;
	ET0 = 1;
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

void InitADC()
{
        ADC_DATA = 0;
        ADC_LOW2 = 0;
        ADC_CONTR = 0x60 | 3;   //设置在check口，转换速度最高
        delay(10);
}

void InterruptUART() interrupt 4
{
	if (RI)
	{
		RI = 0;
		order = SBUF;
	}
	if (TI)
	{
	 	//SBUF = order;
		TI = 0;
	}
}
void timer0routine() interrupt 1
{
	static uint time_count;
	TH0 = 0XFC;
	TL0 = 0X67;
	time_count = (time_count + 1) % 1000;
	if (time_count % 2)
	{
		pwm_out_flag = 1;
	}
	if(time_count % 10 == 9)
	{
		pwm_renew_flag = 1;
	}
	if(time_count == 999)
	{
		clock_flag = 1;//1s
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

//输出占空比
void POUT() 
{
    unsigned char cnt;  
    for(cnt=0;cnt<MAX;cnt++)
    {
        if(cnt<R_OUT)
                RED=1;        //红色占空比大于计数值时红灯亮
        else
                RED=0;        //否则就关闭红色
               
        if(cnt<G_OUT)               
                GREEN=1;                //绿色占空比大于计数值时绿灯亮
        else
                GREEN=0;                //否则就关闭绿色
               
        if(cnt<B_OUT)
                BLUE=1;                //蓝色占空比大于计数值时蓝灯亮
        else
                BLUE=0;                //否则就关闭蓝色
    }
}

void ConfigPWM(unsigned char t)  //PWM占空比处理函数
{
        static unsigned char dir=0;    //定义变亮或变暗方向
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
                                        if(mod == 1)
                                        {
                                                index = 0;
                                        }
                                        else if(mod == 9)
                                        {
                                                index = 1;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
                                }
                        }
                        break;
                                       
                case 1:            
                        if(dir==0)                //橙色由暗变亮
                        {
                                time+=t;
                                R_OUT=time;
								G_OUT=time/4;
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
								G_OUT=time/4;
                                B_OUT=0;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        if(mod == 2)
                                        {
                                                index = 1;
                                        }
                                        else if(mod == 9)
                                        {
												index = 2;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
                                }
                        }
                        break;
                                       
                case 2:            
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
                                        if(mod == 3)
                                        {
                                                index = 2;
                                        }
                                        else if(mod == 9)
                                        {
                                                index = 3;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
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
                                        if(mod == 4)
                                        {
                                                index = 3;
                                        }
                                        else if(mod == 9)
                                        {
                                                index = 4;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
                                }
                        }
                        break;
                                       
                case 4:           
                        if(dir==0)                //青色由暗变亮
                        {
                                time+=t;
                                R_OUT=0;
                                G_OUT=time;
                                B_OUT=time/2;
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
                                B_OUT=time/2;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        if(mod == 5)
                                        {
                                                index = 4;
                                        }
                                        else if(mod == 9)
                                        {
                                                index = 5;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
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
                                        if(mod == 6)
                                        {
                                                index = 5;
                                        }
                                        else if(mod == 9)
                                        {
                                                index = 6;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
                                }
                        }
                        break;
                                       
                case 6:            
                        if(dir==0)                //紫色由暗变亮
                        {
                                time+=t;
                                R_OUT=time/3;
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
                                R_OUT=time/3;
                                G_OUT=0;
                                B_OUT=time;
                                if(time<=MIN)
                                {
                                        dir=0;
                                        time=0;
                                        if(mod == 7)
                                        {
                                                index = 6;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
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
                                        if(mod == 8)
                                        {
                                                index = 7;
                                        }
                                        else if(mod == 9)
                                        {
												index = 0;
                                        }
                                        else
                                        {
                                                index = 7;
                                        }
                                }
                        }
                        break;
			           
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
    _nop_();_nop_();
    LCD1602_E  = 0;
}

void LCD1602_Init()    //1602初始化函数 
{
    LCD1602_write_cmd(0x01);    //显示清屏
    LCD1602_write_cmd(0x38);    //显示模式设置
    LCD1602_write_cmd(0x0C);    //显示开及光标设置
    LCD1602_write_cmd(0x06);    //显示光标移动位置
}

void LCD1602_write_data(unsigned char date)    //写数据函数 
{
    LcdWaitReady();
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DB = date;
    LCD1602_E  = 1;
    _nop_();_nop_();
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

void check(uint data1)
{
    if(data1 < 15)
    {
        EA = 0;//关闭全局中断
        //蓝牙发送报警
        while(1)
        {
            LCD1602_ShowStr(15,1,"!");  //LCD显示感叹号
            D3 = 1;                     //灯闪烁，蜂鸣器间歇性报警
            BEEP = 1;
            delay(40000);
            D3 = 0;
            BEEP = 0;
            delay(40000);
        }
    }
    else EA = 1;
}

/******************故障检测****************/
void LED_check()
{
		//判断蓝灯通断
        RED = 0;
        GREEN = 0;
        BLUE = 1;
        Delay_ms(500);
        check(Adc(3));

        //判断红灯通断
        RED = 1;
        GREEN = 0;
        BLUE = 0;
        Delay_ms(500);
        check(Adc(3));
        
        //判断绿灯通断
        RED = 0;
        GREEN = 1;
        BLUE = 0;
        Delay_ms(500);
        check(Adc(3));
}

void main()
{
	static uint clock_count; 
	static uint MODEL_OLD;
	static uint info_old;
	static uint clock_enable;
	static uint change_enable;
	static uint light_count;

	P1M0 = 0x48;
	P1M1 = 0x4F;
	EA = 1;
	ConfigUART(9600);
	timer0init();
    LCD1602_Init();//LCD初始化
	InitADC();//ADC端口模式初始化

	RED = 0;
	GREEN = 0;
	BLUE = 0;
	D3 = 0;
	light_count = 200;

	LCD1602_Clear();

        LED_check();//故障检测

	do
	{	
		LCD1602_ShowStr(0,1,"order:");
		MODEL = (order & 0xF0) >> 4;
		LCD1602_ShowNum(6,1,MODEL);	
		info = order & 0x0F;
		LCD1602_ShowNum(7,1,info);	

		light_data = Adc(6);

		if(MODEL != MODEL_OLD || info != info_old)
		{
			LCD1602_Clear();
			MODEL_OLD = MODEL;
			info_old = info;
			if(MODEL == 4 || MODEL == 5)
			{
				clock_enable = 1;
			}
			if(MODEL == 0)
			{
				change_enable = 1;
			}
		}

		switch(MODEL)
		{
			case 0:
				if(change_enable)
				{
					change_enable = 0;
					mod = info;
					index = (mod == 9)? 1: (mod - 1);
				}
				LCD1602_ShowStr(0,0,"mod:");
				LCD1602_ShowNum(5,0,mod);
				_nop_();_nop_();
				if(pwm_out_flag)
				{
					pwm_out_flag = 0;
					POUT();
				}
				if(pwm_renew_flag)
				{
					pwm_renew_flag = 0;
					ConfigPWM(1);
				}
				break;
			case 1:
				R_OUT = info*20;
				LCD1602_ShowStr(0,0,"R:");
				LCD1602_ShowNum(2,0,R_OUT/2);
				LCD1602_ShowStr(5,0,"G:");
				LCD1602_ShowNum(7,0,G_OUT/2);
				LCD1602_ShowStr(10,0,"B:");
				LCD1602_ShowNum(12,0,B_OUT/2);
				_nop_();_nop_();
				if(pwm_out_flag)
				{
					pwm_out_flag = 0;
					POUT();
				}
				break;
			case 2:
				G_OUT = info*20;
				LCD1602_ShowStr(0,0,"R:");
				LCD1602_ShowNum(2,0,R_OUT/2);
				LCD1602_ShowStr(5,0,"G:");
				LCD1602_ShowNum(7,0,G_OUT/2);
				LCD1602_ShowStr(10,0,"B:");
				LCD1602_ShowNum(12,0,B_OUT/2);
				_nop_();_nop_();
				if(pwm_out_flag)
				{
					pwm_out_flag = 0;
					POUT();
				}
				break;
			case 3:
				B_OUT = info*20;
				LCD1602_ShowStr(0,0,"R:");
				LCD1602_ShowNum(2,0,R_OUT/2);
				LCD1602_ShowStr(5,0,"G:");
				LCD1602_ShowNum(7,0,G_OUT/2);
				LCD1602_ShowStr(10,0,"B:");
				LCD1602_ShowNum(12,0,B_OUT/2);
				_nop_();_nop_();
				if(pwm_out_flag)
				{
					pwm_out_flag = 0;
					POUT();
				}
				break;
			case 4:
				if(clock_enable)//第一次做MODEL = 4
				{
					clock_enable = 0;
					clock = info;
					clock_count = 0;
					//灭
					RED = 0;
					GREEN = 0;
					BLUE = 0;
				}

				LCD1602_ShowStr(0,0,"clock:");
				_nop_();_nop_();

				if(clock_flag)
				{
					clock_flag = 0;
					clock_count++;
				}
				if(clock_count >= clock * 60)
				{
					LCD1602_ShowNum(6,0,0);
					_nop_();_nop_();
					if(pwm_out_flag)
					{
						pwm_out_flag = 0;
						POUT();
					}
					if(pwm_renew_flag)
					{
						pwm_renew_flag = 0;
						ConfigPWM(1);
					}
				}
				else{
					if(clock*60 - clock_count < 10) LCD1602_ShowStr(7,0," ");
					else if(clock*60 - clock_count < 100) LCD1602_ShowStr(8,0," ");
					LCD1602_ShowNum(6,0,clock*60 - clock_count);
					_nop_();_nop_();
				}
				break;
			case 5:
				if(clock_enable)//第一次做MODEL = 5
				{
					clock_enable = 0;
					clock = info;
					clock_count = 0;
				}

				LCD1602_ShowStr(0,0,"clock:");
				_nop_();_nop_();
				
				if(clock_flag)
				{
					clock_flag = 0;
					clock_count++;
				}
				if(clock_count <= clock * 60)
				{
					if(clock*60 - clock_count < 10) LCD1602_ShowStr(7,0," ");
					else if(clock*60 - clock_count < 100) LCD1602_ShowStr(8,0," ");
					LCD1602_ShowNum(6,0,clock*60 - clock_count);
					_nop_();_nop_();
					if(pwm_out_flag)
					{
						pwm_out_flag = 0;
						POUT();
					}
					if(pwm_renew_flag)
					{
						pwm_renew_flag = 0;
						ConfigPWM(1);
					}
				}
				else
				{
					LCD1602_ShowNum(6,0,0);
					_nop_();_nop_();
					RED = 0;
					GREEN = 0;
					BLUE = 0;
				}
				break;
			case 6:
				light_count++;
				if(light_count >= 200)
				{
					light_count = 0;
					LCD1602_ShowStr(0,0,"light:");
					LCD1602_ShowNum(6,0,light_data);
					_nop_();_nop_();
				}
				
				if(light_data > 400)
				{
					RED = 0;
					GREEN = 0;
					BLUE = 0;
				}
				else
				{
					if(pwm_out_flag)
					{
						pwm_out_flag = 0;
						POUT();
					}
					if(pwm_renew_flag)
					{
						pwm_renew_flag = 0;
						ConfigPWM(1);
					}
				}
		}
		
	}while(1);
}