
#include <reg52.h>
#include <STC12C.h>
#include <intrins.h>              

sbit LCD_RS=P3^2;    /*LCD寄存器选择信号*/
sbit LCD_R_W=P3^3;   /*LCD读写信号*/
sbit LCD_E=P3^4;     /*LCD片选信号*/

//变量类型标识的宏定义，大家都喜欢这么做
#define Uchar unsigned char
#define Uint unsigned int
#define uchar unsigned char
#define uint unsigned int

/* 定义命令 */
#define ISP_IAP_BYTE_READ				0x01        /*  字节读数据存储区   */
#define ISP_IAP_BYTE_PROGRAM          0x02        /*  字节编程数据存储区 */
#define ISP_IAP_SECTOR_ERASE     0x03        /*  扇区擦除数据存储区 */

/* 定义Flash 操作等待时间 */
#define ENABLE_ISP        0x84
#define DATA_FLASH_START_ADDRESS           0x2800

typedef     unsigned char	INT8U;		/* 8 bit 无符号整型  */
typedef     unsigned int    INT16U;     /* 16 bit 无符号整型 */
#define		DELAY_CONST         60000

/* 定义常量 */
#define ERROR   0
#define OK      1

// 控制引脚定义，不同的连接必须修改的部分
sbit RS=P3^2;
sbit RW=P3^3; 
sbit Elcm=P3^4;  

sbit SelA=P1^1;
sbit SelB=P3^7;

sbit PA=P1^5;
sbit PB=P1^6;
sbit PC=P1^7;



unsigned char lcd_data[5];
unsigned int i,k,j;
unsigned char disp_bool;
unsigned char tempC;
unsigned char overflag;


#define DataPort P2                // 数据端口
#define Busy    0x80
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#define _Nop() _nop_()

char idata word_storeroom[]=
{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 

void Delay400Ms(void);
void Delay5Ms(void);
void WaitForEnable( void );
void LcdWriteData( char dataW );
void LcdWriteCommand( Uchar CMD,Uchar AttribC );
void LcdReset( void );
void Display( Uchar dd );
void DispOneChar(Uchar x,Uchar y,Uchar Wdata);
void ePutstr(Uchar x,Uchar y, Uchar code *ptr);


/*=======================================================
显示字符串
=======================================================*/
void ePutstr(Uchar x,Uchar y, Uchar code *ptr) {
Uchar i,l=0;
    while (ptr[l] >31) {l++;};
    for (i=0;i<16;i++) { DispOneChar(x++,y,ptr[i]);
        if ( x == 16 ){
            x = 0; y ^= 1;
        }
    }
}

/*=======================================================
演示一行连续字符串，配合上位程序演示移动字串
=======================================================*/
void Display( Uchar dd ) {

Uchar i;

    for (i=0;i<16;i++) {
        DispOneChar(i,1,dd++);
        dd &= 0x7f;
        if (dd<32) dd=32;
    }
}

/*=======================================================
显示光标定位
=======================================================*/
void Disp_XY( char posx,char posy) {

uchar temp;

    temp = posx %40;// & 0x07;
    posy &= 0x01;
    if ( posy==1)  {temp |= 0x40;}
    temp |= 0x80;
    LcdWriteCommand(temp,1);
}

/*=======================================================
按指定位置显示数出一个字符
=======================================================*/
void DispOneChar(Uchar x,Uchar y,Uchar Wdata) {

    Disp_XY( x, y );                // 定位显示地址
    LcdWriteData( Wdata );            // 写字符
}

/*=======================================================
初始化程序, 必须按照产品资料介绍的初始化过程进行
=======================================================*/
void LcdReset( void ) {

       LcdWriteCommand( 0x38, 0);            // 显示模式设置(不检测忙信号)
        Delay5Ms();
    LcdWriteCommand( 0x38, 0);            // 共三次
        Delay5Ms();
    LcdWriteCommand( 0x38, 0);
        Delay5Ms();

    LcdWriteCommand( 0x38, 1);            // 显示模式设置(以后均检测忙信号)
    LcdWriteCommand( 0x08, 1);            // 显示关闭
    LcdWriteCommand( 0x01, 1);            // 显示清屏
    LcdWriteCommand( 0x06, 1);            // 显示光标移动设置
    LcdWriteCommand( 0x0c, 1);            // 显示开及光标设置
    LcdWriteCommand( 0x02, 1);            // 显示开及光标设置
}

/*=======================================================
写控制字符子程序: E=1 RS=0 RW=0
=======================================================*/
void LcdWriteCommand( Uchar CMD,Uchar AttribC ) {

    if (AttribC) WaitForEnable();                // 检测忙信号?

    RS = 0;    RW = 0; _nop_();

    DataPort = CMD; _nop_();
    // 送控制字子程序

    Elcm = 1;_nop_();_nop_();Elcm = 0;            // 操作允许脉冲信号
}

/*=======================================================
当前位置写字符子程序: E =1 RS=1 RW=0
=======================================================*/
void LcdWriteData( char dataW ) {

    WaitForEnable();
        // 检测忙信号

    RS = 1; RW = 0; _nop_();

    DataPort = dataW; _nop_();

    Elcm = 1; _nop_(); _nop_(); Elcm = 0;        // 操作允许脉冲信号

}

/*=======================================================
正常读写操作之前必须检测LCD控制器状态:    CS=1 RS=0 RW=1
DB7:    0  LCD控制器空闲; 1  LCD控制器忙
========================================================*/
void WaitForEnable( void ) {

    DataPort = 0xff;

    RS =0; RW = 1; _nop_();    Elcm = 1; _nop_(); _nop_();

    while( DataPort & Busy );

    Elcm = 0;
}


// 短延时
void Delay5Ms(void)
{
    Uint i = 5552;
    while(i--);
}

//长延时
void Delay400Ms(void)
{
    Uchar i = 5;
    Uint j;
    while(i--)
    {
        j=7269;
        while(j--);
    };
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

main()
{ 
    uint tmp=0;
    uint i;
	uint tmp_alarm;
    unsigned long limit;
    char code *number1="www.zju.edu.cn  ";
	char code *number6="edu.cn  ";
    char code *number2="         Ver2.71";
    char code *number3="Voltage: ";
    char code *number4="Thinknes";
    char code *number5="s:      ";


    LcdReset();
	Delay400Ms();


	for(;;) {	

// Display "www.zju.edu.cn"
		for(i=0;i<16;i++)
	    {
	        DispOneChar(i,0,*(number1+i));
	        DispOneChar(i,1,*(number6+i));
	    }
		Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
		Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
		Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
		Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();

		//平移
		for(i=0;i<16;i++)
	    {
	        DispOneChar(i,0,*(number1+i));
	        DispOneChar(i,1,*(number2+i));
	    }
	    for(i=0;i<8;i++)
	    {
	        LcdWriteCommand( 0x18, 1);            //平移
	        Delay400Ms();
	        Delay400Ms();
	        Delay400Ms();
	    }

	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    Delay400Ms();
	    LcdWriteCommand( 0x02, 1);            // 显示开及光标设置

// clear Display

	for(i=0;i<8;i++)
    {
        DispOneChar(i,0,' ');
        DispOneChar(i,1,' ');
    }

 }
} //end_main
