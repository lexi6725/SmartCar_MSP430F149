/*
 * File Name: interrupt.c
 * Author: Lexi
 * Date: 2015/03/11
 */

/*
 * 中断服务程序定义
*/
#include "config.h"
#include "interrupt.h"


/****************************************************
 * ISR_Timer_B0
 * 参数： None
 * 返回值：None
 * 功能：TimerB0中断服务程序
 ****************************************************/
#pragma vector=TIMERB0_VECTOR
__interrupt void ISR_Timer_B0(void)
{
	
}

/****************************************************
 * 函数名：ISR_Timer_B1
 * 参数： None
 * 返回值：None
 * 功能：TimerB1中断服务程序
 ****************************************************/
#pragma vector=TIMERB1_VECTOR
__interrupt void ISR_Timer_B1(void)
{
	
}