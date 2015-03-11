/*
 * File Name: pwm.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "pwm.h"
#include "Timer.h"
#ifdef MODULE_PWM

uint pwmfrequency = 800;
uint dutycycle = 400;

	 
void Init_PWM(void)
{
	P4SEL	|= BIT1+BIT2+BIT3+BIT4;	// 选择P4.1-TB1,P4.2-TB2,P4.3-TB3,P4.4-TB4
	P4DIR	|= BIT1+BIT2+BIT3+BIT4;
	
	SetTimerBRate(TIMERB0, pwmfrequency);
	SetTimerBRate(TIMERB1, dutycycle);
	SetTimerBRate(TIMERB2, dutycycle);
	SetTimerBRate(TIMERB3, dutycycle);
	SetTimerBRate(TIMERB4, dutycycle);
}

#endif