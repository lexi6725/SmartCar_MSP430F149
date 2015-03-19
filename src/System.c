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
 * 参数： None
 * 返回值：None
 * 功能：初始化系统时钟
 ****************************************************/
void Init_clk(void)
{
	uchar i;
	BCSCTL1	&= ~XT2OFF;			// 打开XT2振荡器
	BCSCTL2	|= SELM1+SELS;		// MCLK为8MHz, SMCLK为8MHz
	
	do{
		IFG1 &= ~OFIFG;			// 清除振荡器错误标志
		for(i = 0; i < 100; ++i)
			_NOP();				// 延时等待
	}while((IFG1&OFIFG) != 0);	// 如果振荡器标志错误，则继续等待
	
	IFG1 &= ~OFIFG;
}

/**********************************************************
 * 函数名：System_Init
 * 参数： None
 * 功能：初始化系统
 **********************************************************/
void System_Init(void)
{
	Init_clk();
	Init_Motor();
	EnableMotor();
}