/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */

#include "config.h"
#include "motor.h"
#include "Timer.h"

uint MotorFreq = 32;
uint MotorPulseWidth[4] = {16, 64, 16, 16};

/**************************************************
 * Init_Motor
 * 参数：None
 * 返回值：None
 * 功能：初始化Motor所用引�? **************************************************/
void Motor_Init(void)
{	
	// P4.1 P4.2 P4.3 P4.6: PWM脉冲输出，控制电机速度
	P4SEL	|= BIT1+BIT2+BIT3+BIT6;
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
	
	// P6.0 ~ P6.7: motor0~motor3电机运转方向控制
	//P6DIR	= 0xff;
}

/**************************************************
 * 函数名：EnableMotor
 * 参数：None
 * 返回值：None
 * 功能：设置Motor速率，启动电�? **************************************************/
void EnableMotor(void)
{
	SetTimerBRate(TIMERB0, MotorFreq);
	
	SetTimerBRate(TIMERB1, MotorPulseWidth[MOTOR_LF]);
	SetTimerBRate(TIMERB2, MotorPulseWidth[MOTOR_LB]);
	SetTimerBRate(TIMERB3, MotorPulseWidth[MOTOR_RF]);
	SetTimerBRate(TIMERB6, MotorPulseWidth[MOTOR_RB]);
}

/**************************************************
 * 函数名：DisableMoter
 * 参数：None
 * 返回值：None
 * 功能：停止电�? **************************************************/
void DisableMoter(void)
{
	DisableTimerB();
}

/**************************************************
 * 函数名：SetMotorRate
 * 参数：motorctl: 控制的电机，rate：速率
 * 返回值：None
 * 功能：设置电机速率
 **************************************************/
void SetMotorRate(uchar motorctl, uint rate)
{
	if (rate = 0 && rate > MAXRATE)
		return;
	
	DisableMoter();
	MotorPulseWidth[motorctl] = rate;
	EnableMotor();
}

/**************************************************
* 函数名：SetMotorDir
* 参数：motorctl: 控制的电机，dir:方向
* 返回值：None
* 功能：调整电机方�?*
***************************************************/
void SetMotorDir(uchar motorctl, uchar dir)
{
	if (motorctl > MAXMOTORNUM)
		return;
	
	if (!dir)
		P2OUT	&= (dir << (motorctl*2));
	else
		P2OUT	|= (dir << (motorctl*2));
}

void SetMotorDirs(uchar dir)
{
	if (dir == dirFORWARD)
		P2OUT	= ((dirFORWARD)+(dirFORWARD<<2)+(dirFORWARD<<4)+(dirFORWARD<<6));
	else if (dir == dirROLLBACK)
		P2OUT	= ((dirROLLBACK)+(dirROLLBACK<<2)+(dirROLLBACK<<4)+(dirROLLBACK<<6));
	else if (dir == dirLEFT)
		P2OUT	= ((dirROLLBACK)+(dirROLLBACK<<2)+(dirFORWARD<<4)+(dirFORWARD<<6));
	else if (dir == dirRIGHT)
		P2OUT	= ((dirFORWARD)+(dirFORWARD<<2)+(dirROLLBACK<<4)+(dirROLLBACK<<6));
	else
		P2OUT	= ((dirDEBOOST)+(dirDEBOOST<<2)+(dirDEBOOST<<4)+(dirDEBOOST<<6));
}