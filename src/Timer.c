/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "timer.h"
#include "System.h"
#ifdef MODULE_TIMER

ulong	Second_count = 0;

void TimerB7_Init(void)
{
	/* TB1~TB3 TB6 To PWM Out */
	TBCCTL1 = OUTMOD_7;
	TBCCTL2 = OUTMOD_7;
	TBCCTL3 = OUTMOD_7;
	TBCCTL6 = OUTMOD_7;
	TBCTL |= TASSEL_1 + TBCLR + MC_1;		// ACLK + Up Mode
}

/**************************************************
 * 函数名：EnableTimerB
 * 参数：None
 * 返回值：None
 * 功能：使能TimerB定时�? **************************************************/
void DisableTimerB(void)
{
	TBCTL	= 0 | TBCLR;			// Disable Timer B
}

/**************************************************
 * 函数名：SetTimerBRate
 * 参数：TimerBctl:配置的定时器�?Rate：速率
 * 返回值：None
 * 功能：配置TimerB7定时器的某个定时器速率
 **************************************************/
void SetTimerBRate(unsigned char TimerBctl, unsigned int Rate)
{
	switch(TimerBctl)
	{
	case TIMERB0:			// TIMETB-0
		TBCCR0 = Rate;
		break;
	case TIMERB1:			// TIMETB-1
		TBCCR1	= Rate;
		break;
	case TIMERB2:			// TIMETB-2
		TBCCR2	= Rate;
		break;
	case TIMERB3:			// TIMETB-3
		TBCCR3	= Rate;
		break;
	case TIMERB4:			// TIMETB-4
		TBCCR4	= Rate;
		break;
	case TIMERB5:			// TIMETB-5
		TBCCR5	= Rate;
		break;
	case TIMERB6:			// TIMETB-6
		TBCCR6	= Rate;
		break;
	}
}

/**************************************************
 * 函数名：TimerB0_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B0中断服务
 **************************************************/
void TimerB0_ISR(void)
{
	if (++Second_count > SIZE_1K)
	{
		SystemFlag	|= bSECOND;
		Second_count = 0;
	}
}

/**************************************************
 * 函数名：TimerB1_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B1中断服务
 **************************************************/
void TimerB1_ISR(void)
{
}


void TimerA3_Init(void)
{
	TACTL	|= TASSEL_2 + MC_2 + ID_3;
}

#endif