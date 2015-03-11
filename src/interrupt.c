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



#pragma vector=TIMERB0_VECTOR
__interrupt void ISR_Timer_B0(void)
{
	
}

#pragma vector=TIMERB1_VECTOR
__interrupt void ISR_Timer_B1(void)
{
	
}