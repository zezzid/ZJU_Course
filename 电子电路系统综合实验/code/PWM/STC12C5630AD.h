#ifndef __STC12C5630AD_H__
#define __STC12C5630AD_H__

/////////////////////////////////////////////////

/* The following is STC additional SFR or change */

/* sfr  AUXR  = 0x8e; */
/* sfr  IPH   = 0xb7; */

/* Watchdog Timer Register */
sfr  WDT_CONTR = 0xe1;    

/* ISP_IAP_EEPROM Register */
sfr ISP_DATA  = 0xe2;
sfr ISP_ADDRH = 0xe3;
sfr ISP_ADDRL = 0xe4;
sfr ISP_CMD   = 0xe5;
sfr ISP_TRIG  = 0xe6;
sfr ISP_CONTR = 0xe7;

/* System Clock Divider */
sfr CLK_DIV  = 0xc7;

/* I_O Port Mode Set Register */
sfr P0M0  = 0x93;
sfr P0M1  = 0x94;
sfr P1M0  = 0x91;
sfr P1M1  = 0x92;
sfr P2M0  = 0x95;
sfr P2M1  = 0x96;
sfr P3M0  = 0xb1;
sfr P3M1  = 0xb2;

/* SPI Register */
sfr SPSTAT  = 0x84;
sfr SPCTL   = 0x85;
sfr SPDAT   = 0x86;

/* ADC Register */
sfr ADC_CONTR  = 0xc5;
sfr ADC_DATA   = 0xc6;
sfr ADC_LOW2   = 0xbe;

/* PCA SFR */
sfr CCON   = 0xD8;
sfr CMOD   = 0xD9;
sfr CCAPM0 = 0xDA;
sfr CCAPM1 = 0xDB;
sfr CCAPM2 = 0xDC;
sfr CCAPM3 = 0xDD;
sfr CCAPM4 = 0xDE;
sfr CCAPM5 = 0xDF;

sfr CL     = 0xE9;
sfr CCAP0L = 0xEA;
sfr CCAP1L = 0xEB;
sfr CCAP2L = 0xEC;
sfr CCAP3L = 0xED;
sfr CCAP4L = 0xEE;
sfr CCAP5L = 0xEF;

sfr CH     = 0xF9;
sfr CCAP0H = 0xFA;
sfr CCAP1H = 0xFB;
sfr CCAP2H = 0xFC;
sfr CCAP3H = 0xFD;
sfr CCAP4H = 0xFE;
sfr CCAP5H = 0xFF;

sfr PCA_PWM0 = 0xF2;
sfr PCA_PWM1 = 0xF3;
sfr PCA_PWM2 = 0xF4;
sfr PCA_PWM3 = 0xF5;
sfr PCA_PWM4 = 0xF6;
sfr PCA_PWM5 = 0xF7;

/*  CCON  */
sbit CF    = CCON^7;
sbit CR    = CCON^6;
sbit CCF5  = CCON^5;
sbit CCF4  = CCON^4;
sbit CCF3  = CCON^3;
sbit CCF2  = CCON^2;
sbit CCF1  = CCON^1;
sbit CCF0  = CCON^0;


/* Above is STC additional SFR or change */

/*--------------------------------------------------------------------------
REG51F.H

Header file for 8xC31/51, 80C51Fx, 80C51Rx+
Copyright (c) 1988-1999 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.

Modification according to DataSheet from April 1999
 - SFR's AUXR and AUXR1 added for 80C51Rx+ derivatives
--------------------------------------------------------------------------*/

/*  BYTE Registers  */
sfr P0   = 0x80;
sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sfr P1   = 0x90;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sfr P2   = 0xA0;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sfr P3   = 0xB0;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;
sfr PSW  = 0xD0;
sfr ACC  = 0xE0;
sfr B    = 0xF0;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr IE   = 0xA8;
sfr IP   = 0xB8;
sfr SCON = 0x98;
sfr SBUF = 0x99;

/*  80C51Fx/Rx Extensions  */
sfr AUXR   = 0x8E;
/* sfr AUXR1  = 0xA2; */
sfr SADDR  = 0xA9;
sfr IPH    = 0xB7;
sfr SADEN  = 0xB9;
sfr T2CON  = 0xC8;
sfr T2MOD  = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;


/*  BIT Registers  */
/*  PSW   */
sbit CY   = PSW^7;
sbit AC   = PSW^6;
sbit F0   = PSW^5;
sbit RS1  = PSW^4;
sbit RS0  = PSW^3;
sbit OV   = PSW^2;
sbit F1   = PSW^1;
sbit P    = PSW^0;

/*  TCON  */
sbit TF1  = TCON^7;
sbit TR1  = TCON^6;
sbit TF0  = TCON^5;
sbit TR0  = TCON^4;
sbit IE1  = TCON^3;
sbit IT1  = TCON^2;
sbit IE0  = TCON^1;
sbit IT0  = TCON^0;

/*  P3  */
sbit RD   = P3^7;
sbit WR   = P3^6;
sbit T1   = P3^5;
sbit T0   = P3^4;
sbit INT1 = P3^3;
sbit INT0 = P3^2;
sbit TXD  = P3^1;
sbit RXD  = P3^0;

/*  SCON  */
sbit SM0  = SCON^7; // alternatively "FE"
sbit FE   = SCON^7;
sbit SM1  = SCON^6;
sbit SM2  = SCON^5;
sbit REN  = SCON^4;
sbit TB8  = SCON^3;
sbit RB8  = SCON^2;
sbit TI   = SCON^1;
sbit RI   = SCON^0;
             

sbit T2EX = P1^1;
sbit T2   = P1^0;

/*  T2CON  */
sbit TF2   = T2CON^7;
sbit EXF2  = T2CON^6;
sbit RCLK  = T2CON^5;
sbit TCLK  = T2CON^4;
sbit EXEN2 = T2CON^3;
sbit TR2   = T2CON^2;
sbit C_T2  = T2CON^1;
sbit CP_RL2= T2CON^0;

/* PCA Pin */

sbit CEX3 = P2^4;
sbit CEX2 = P2^0;
sbit CEX1 = P3^5;
sbit CEX0 = P3^7;
sbit ECI  = P3^4;

/*  IE   */
sbit EA   = IE^7;
sbit EPCA_LVD  = IE^6;
sbit EADC_SPI  = IE^5;
sbit ES   = IE^4;
sbit ET1  = IE^3;
sbit EX1  = IE^2;
sbit ET0  = IE^1;
sbit EX0  = IE^0;

/*  IP   */ 
sbit PPCA_LVD  = IP^6;
sbit PADC_SPI  = IP^5; 
sbit PS   = IP^4;
sbit PT1  = IP^3;
sbit PX1  = IP^2;
sbit PT0  = IP^1;
sbit PX0  = IP^0;

/////////////////////////////////////////////////

#endif

