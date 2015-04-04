/*
 * File Name: System.c
 * Author: Lexi
 * Date: 2015/03/11
 */

#include "config.h"
#include "Timer.h"
#include "motor.h"
#include "irda.h"

uint SystemFlag = 0;      // 系统标志

/****************************************************
 * 函数名：Init_clk
 * 参数＿None
 * 返回值：None
 * 功能：初始化系统时钟
 ****************************************************/
void Init_clk(void)
{
	uchar i;
	
	BCSCTL1	&= ~XT2OFF;			// 打开XT2振荡器
	
	do{
		IFG1 &= ~OFIFG;			// 清除振荡器错误标忿
		for (i = 0xff; i>0; --i);	// 延时等待
	}while((IFG1&OFIFG) != 0);	// 如果振荡器标志错误，则继续等徿	
	
	BCSCTL2	= SELM1 + SELS;	// MCLK and SMCLK Select XT2CLK	8MHz
}

/**********************************************************
 * 函数名：System_Init
 * 参数＿None
 * 功能：初始化系统
 **********************************************************/
void System_Init(void)
{
	Init_clk();               // 初始化系统时钟
	Motor_Init();             // 初始化电机
	TimerB7_Init();           // 初始化定时器TimerB
	TimerA3_Init();           // 初始化定时器TimerA3
	
	ENABLE_TIMERB0();         // 开启定时器TimerB0中断
	EnableMotor();            // 使能电机            
	SetMotorDirs(dirFRONT); // 设置电机初始方向
	Init_Irda();              // 初始化红外
	_EINT();                  // 使能总中断
}