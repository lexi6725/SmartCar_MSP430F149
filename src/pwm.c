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
uint pwmPulseWidth[4] = {400, 400, 400, 400};

/**************************************************
 * 函数名：Init_PWM
 * 参数：None
 * 返回值：None
 * 功能：初始化PWM所用引脚
 **************************************************/
void Init_PWM(void)
{
	P4SEL	|= BIT1+BIT2+BIT3+BIT6;	// 选择P4.1-TB1,P4.2-TB2,P4.3-TB3,P4.4-TB4
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
}

/**************************************************
 * 函数名：EnablePWM
 * 参数：None
 * 返回值：None
 * 功能：设置PWM速率，使能PWM输出
 **************************************************/
void EnablePWM(void)
{	
	SetTimerBRate(TIMERB0, pwmfrequency);
	SetTimerBRate(TIMERB1, pwmPulseWidth[PWM1]);
	SetTimerBRate(TIMERB2, pwmPulseWidth[PWM2]);
	SetTimerBRate(TIMERB3, pwmPulseWidth[PWM3]);
	SetTimerBRate(TIMERB6, pwmPulseWidth[PWM4]);
										 
	EnableTimerB();
}

/**************************************************
 * 函数名：DisablePWM
 * 参数：None
 * 返回值：None
 * 功能：禁止PWM输出
 **************************************************/
void DisablePWM(void)
{
	DisableTimerB();
}

/**************************************************
 * 函数名：SetPWMRate
 * 参数：pwmctl: 控制的PWM电机，rate：速率
 * 返回值：None
 * 功能：设置PWM速率，使能PWM输出
 **************************************************/
void SetPWMRate(uchar pwmctl, uint rate)
{
	DisablePWM();
	pwmPulseWidth[pwmctl] = rate;
	EnablePWM();
}
#endif