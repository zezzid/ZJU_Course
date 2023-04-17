#include <reg52.h>
#include <intrins.h>

#define FOSC 18432000L
#define BAUD 9600

typedef unsigned char BYTE;
typedef unsigned int WORD;

//Declare SFR associated with the ADC
sfr AUXR      = 0x8e;
sfr ADC_CONTR = 0xC5;
sfr ADC_DATA  = 0xC6;
sfr ADC_LOW2  = 0xBE;
sfr P1M0      = 0x91;
sfr P1M1      = 0x92;

//Define
sbit RED = P1^0;
sbit GREEN = P1^1;
sbit BLUE = P1^2;
sbit D3 = P1^4;
sbit BEEP = P1^7;



//Define ADC operation const for ADC_CONTR
#define ADC_POWER   0x80
#define ADC_FLAG    0x10
#define ADC_START   0x08
#define ADC_SPEEDLL 0x00
#define ADC_SPEEDL  0x20
#define ADC_SPEEDH  0x40
#define ADC_SPEEDHH 0x60

void InitUart();
void SendData(BYTE dat);
void Delay(WORD n);
void InitADC();
void check(WORD data1);
BYTE ch1 = 6;
BYTE ch2 = 3;
WORD ADC_COUNT = 0;
BYTE check_flag = 0;
WORD x;

void main()
{
    InitUart();
    InitADC();

	P1M0 = 0x48;
	P1M1 = 0x4F;

    RED = 0;
    GREEN = 0;
    BLUE = 1;
    BEEP = 1;
    D3 = 0;

    AUXR |= 0x10;
    IE = 0xa0;
    EA = 1;


    while (1)
    {
        if(check_flag)//电路断开，报警
        {
            EA = 0;//关闭中断
            //蓝牙发送报警
            //LCD显示感叹号
            while(1)
            {
                D3 = 1;
                //BEEP = 1;
                Delay(10);
                D3 = 0;
                //BEEP = 0;
                Delay(10);
            }
        }
    }
}

void adc_isr() interrupt 5 using 1
{
    ADC_CONTR &= ~ADC_FLAG;
    x=(int) ADC_DATA<<2 + (int)ADC_LOW2;
    SendData((x>>8));SendData(x&0xff);
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START |ch2;//ch1是P1.6脚，有输出；这里改成ch2（P1.3），输出全是0
}

void InitADC()
{
    ADC_DATA = 0;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START |ch2;
    Delay(2);
    ADC_CONTR &= !ADC_FLAG;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START |ch2;//先多做一次ADC，第一次的值不稳定
}

void InitUart()
{
    SCON = 0x5a;
    TMOD = 0x20;
    TH1 = TL1 = -(FOSC/12/32/BAUD);//-5 0xFB
    TR1 = 1;
}

void check(WORD data1)
{
    if(data1 == 0)
    {
        check_flag = 1;
    }
}

void SendData(BYTE dat)
{
    while(!TI);
    TI = 0;
    SBUF = dat;
}

void Delay(WORD n)
{
    WORD x;

    while(n--)
    {
        x= 5000;
        while(x--);
    }
}


