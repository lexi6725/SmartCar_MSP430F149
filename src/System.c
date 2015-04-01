/*
 * File Name: System.c
 * Author: Lexi
 * Date: 2015/03/11
 */

#include "config.h"
#include "Timer.h"
#include "motor.h"

uint SystemFlag = 0;

/****************************************************
 * 函数名：Init_clk
 * 参数＿None
 * 返回值：None
 * 功能：初始化系统时钟
 ****************************************************/
void Init_clk(void)
{
	BCSCTL1	&= ~XT2OFF;			// 打开XT2振荡噿	BCSCTL2	|= SELM1+SELS+DIVS_3;		// MCLK丿MHz, SMCLK丿MHz
	
	do{
		IFG1 &= ~OFIFG;			// 清除振荡器错误标忿		for(i = 0; i < 100; ++i)
			_NOP();				// 延时等待
	}while((IFG1&OFIFG) != 0);	// 如果振荡器标志错误，则继续等徿	
	IFG1 &= ~OFIFG;
}

/**********************************************************
 * 函数名：System_Init
 * 参数＿None
 * 功能：初始化系统
 **********************************************************/
void System_Init(void)
{
	Init_clk();
	Motor_Init();
	TimerB7_Init();
	TimerA3_Init();
	
	ENABLE_TIMERB0();
	EnableMotor();
	SetMotorDirs(dirFORWARD);
	
	_EINT();
	
	SetMotorDirs(dirFORWARD);
}