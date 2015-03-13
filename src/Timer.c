/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "timer.h"
#include "pwm.h"
#ifdef MODULE_TIMER


/**************************************************
 * 函数名：TimerB_Init
 * 参数：None
 * 返回值：None
 * 功能：初始化TimerB定时器
 **************************************************/
void TimerB_Init(void)
{
	TBCTL |= TASSEL_2 + TBCLR + MC_1;		// SMCLK + Up Mode
	
	/* TB1~TB3 TB6 To PWM Out */
	TBCCTL1 = OUTMOD_7;
	TBCCTL2 = OUTMOD_7;
	TBCCTL3 = OUTMOD_7;
	TBCCTL6 = OUTMOD_7;
}

/**************************************************
 * 函数名：EnableTimerB
 * 参数：None
 * 返回值：None
 * 功能：使能TimerB定时器
 **************************************************/
void EnableTimerB(void)
{
	TBCTL	|= TBIE;		// Enable Timer B
}

/**************************************************
 * 函数名：EnableTimerB
 * 参数：None
 * 返回值：None
 * 功能：使能TimerB定时器
 **************************************************/
void DisableTimerB(void)
{
	TBCTL	= 0;			// Disable Timer B
}

/**************************************************
 * 函数名：SetTimerBRate
 * 参数：TimerBctl:配置的定时器， Rate：速率
 * 返回值：None
 * 功能：配置TimerB7定时器的某个定时器速率
 **************************************************/
void SetTimerBRate(unsigned char TimerBctl, unsigned int Rate)
{
	switch(TimerBctl)
	{
	case TIMERB0:			// TIMETB-0
		DISABLE_TIMERB0();
		TBCCR0 = Rate;
		ENABLE_TIMERB0();
		break;
	case TIMERB1:			// TIMETB-1
		DISABLE_TIMERB1();
		TBCCR1	= Rate;
		ENABLE_TIMERB1();
		break;
	case TIMERB2:			// TIMETB-2
		DISABLE_TIMERB2();
		TBCCR2	= Rate;
		ENABLE_TIMERB2();
		break;
	case TIMERB3:			// TIMETB-3
		DISABLE_TIMERB3();
		TBCCR3	= Rate;
		ENABLE_TIMERB3();
		break;
	case TIMERB4:			// TIMETB-4
		DISABLE_TIMERB4();
		TBCCR4	= Rate;
		ENABLE_TIMERB4();
		break;
	case TIMERB5:			// TIMETB-5
		DISABLE_TIMERB5();
		TBCCR5	= Rate;
		ENABLE_TIMERB5();
		break;
	case TIMERB6:			// TIMETB-6
		DISABLE_TIMERB6();
		TBCCR6	= Rate;
		ENABLE_TIMERB6();
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


#endif