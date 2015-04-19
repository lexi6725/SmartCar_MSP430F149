/*
 * File Name: System.c
 * Author: Lexi
 * Date: 2015/03/11
 */

#include "config.h"
#include "Timer.h"
#include "motor.h"
#include "irda.h"
#include "rtc.h"
#include "HC-SR04.h"
#include "nRF24L01.h"
#include "System.h"
//#include "spi.h"

uint SystemFlag = 0;      // 系统标志

/****************************************************
 * 函数名：Init_clk
 * 参数＿None
 * 返回值：None
 * 功能：初始化系统时钟
 ****************************************************/
void Init_clk(void)
{
	volatile uchar i;
	
	BCSCTL1	&= ~XT2OFF;			// 打开XT2振荡器
	
	do{
		IFG1 &= ~OFIFG;			// 清除振荡器错误标忿
		for (i = 0xff; i>0; --i);	// 延时等待
	}while(IFG1&OFIFG);	// 如果振荡器标志错误，则继续等徿	
	
	BCSCTL2	= SELM_2 + SELS;	// MCLK and SMCLK Select XT2CLK	8MHz
}

/**********************************************************
 * 函数名：System_Init
 * 参数＿None
 * 功能：初始化系统
 **********************************************************/
void System_Init(void)
{
	Init_clk();               	// 初始化系统时钟
	Motor_Init();             	// 初始化电机
	TimerB7_Init();           	// 初始化定时器TimerB
	TimerA3_Init();           	// 初始化定时器TimerA3

	#if defined(MODULE_IRDA)
	Init_Irda();              	// 初始化红外
	#endif
	
	Init_RTC();
	Init_hc_sr04();
	//SPIx_Init();
	_EINT();                  	// 使能总中断
	
	ENABLE_TIMERB0();         	// 开启定时器TimerB0中断
	EnableMotor();            	// 使能电机            
	SetMotorDirs(dirBACK); 	// 设置电机初始方向
	//SetMotorRate(MOTOR_ALL, 10);
	Enable_hc_test();

	nRF24L01_IO_set();
	
	if (nRF24L01_Check())
	{
		SystemFlag	|= bNRF_ENABLE;
		NRF24L01_Init(nRF_RX_Mode);
	}
	
	//P5DIR	|= BIT4+BIT5+BIT6;
	//P5SEL	|= BIT4+BIT5+BIT6;
}


uchar CalCheckSum(uchar *pdat, uchar len)
{
	uchar chksum = 0;
	do{
		chksum += pdat[--len];
	}while(len);

	chksum	+= 0x5A;
	return chksum;
}