#ifndef _STC_H
#define _STC_H

/* Watchdog Timer Register */
sfr  WDT_CONTR = 0xE1; 

/*-----PCA_PWM------*/
sfr CCON   = 0xD8;
sfr CMOD   = 0xD9;
sfr CCAPM0 = 0xDA;
sfr CCAPM1 = 0xDB;
sfr CCAPM2 = 0xDC;
sfr CCAPM3 = 0xDD;
sfr CL     = 0xE9;
sfr CH     = 0xF9;
sfr CCAP0L = 0xEA;
sfr CCAP0H = 0xFA;
sfr CCAP1L = 0xEB;
sfr CCAP1H = 0xFB;
sfr CCAP2L = 0xEC;
sfr CCAP2H = 0xFC;
sfr CCAP3L = 0xED;
sfr CCAP3H = 0xFD;
sfr PCA_PWM0 = 0xF2;
sfr PCA_PWM1 = 0xF3;
sfr PCA_PWM2 = 0xF4;
sfr PCA_PWM3 = 0xF5;

/*----ADC Register -=-*/
sfr ADC_CONTR = 0xC5;
sfr ADC_DATA = 0xC6;
sfr ADC_LOW2 = 0xBE;

/*-----I/O----------*/
//sfr P0M0  = 0x93;
//sfr P0M1  = 0x94;
sfr P1M0  = 0x91;
sfr P1M1  = 0x92;
sfr P2M0  = 0x95;
sfr P2M1  = 0x96;
sfr P3M0  = 0xB1;
sfr P3M1  = 0xB2;

/* ISP_IAP_EEPROM Register */
sfr ISP_DATA  = 0xe2;
sfr ISP_ADDRH = 0xe3;
sfr ISP_ADDRL = 0xe4;
sfr ISP_CMD   = 0xe5;
sfr ISP_TRIG  = 0xe6;
sfr ISP_CONTR = 0xe7;

/* SPI Register */
sfr SPSTAT  = 0x84;
sfr SPCTL   = 0x85;
sfr SPDAT   = 0x86;

/*-----Timer--------*/
sfr AUXR   = 0x8E;

/* IDLE, Clock Divider */
sfr CLK_DIV= 0xC7;

/*  CCON  */
sbit CF    = CCON^7;
sbit CR    = CCON^6;
//sbit CCF5  = CCON^5;
//sbit CCF4  = CCON^4;
//sbit CCF3  = CCON^3;
//sbit CCF2  = CCON^2;
sbit CCF1  = CCON^1;
sbit CCF0  = CCON^0;

#endif

