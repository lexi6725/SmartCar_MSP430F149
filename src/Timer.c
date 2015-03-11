/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "timer.h"
#ifdef MODULE_TIMER



void TimerB_Init(void)
{
	TBCTL |= TASSEL_2 + TBCLR;		// SMCLK + Stop Mode
	TBCCTL1 = OUTMOD_7;
	TBCCTL2 = OUTMOD_7;
	TBCCTL3 = OUTMOD_7;
	TBCCTL4 = OUTMOD_7;
}

void EnableTimerB(void)
{
	TBCTL	|= MC_2;
}

void DisableTimerB(void)
{
	TBCTL	|= TBCLR;
}

void SetTimerBRate(unsigned char TimerB1Bit, unsigned int Rate)
{
	switch(TimerB1Bit)
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

void TimerB0_ISR(void)
{
}

void TimerB1_ISR(void)
{
}


#endif