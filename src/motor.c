/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */

#include "config.h"
#include "motor.h"
#include "Timer.h"

uint MotorFreq = 1024;
uint MotorPulseWidth[4] = {300, 300, 1000, 1000};

/**************************************************
 * Init_Motor
 * 参数：None
 * 返回值：None
 * 功能：初始化Motor所用引脚
 **************************************************/
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
 * 功能：设置Motor速率，启动电机
 **************************************************/
void EnableMotor(void)
{
	SetTimerBRate(TIMERB0, MotorFreq);
	
	SetTimerBRate(TIMERB1, MotorPulseWidth[MOTOR1]);
	SetTimerBRate(TIMERB2, MotorPulseWidth[MOTOR2]);
	SetTimerBRate(TIMERB3, MotorPulseWidth[MOTOR3]);
	SetTimerBRate(TIMERB6, MotorPulseWidth[MOTOR4]);
	
	EnableTimerB();
}

/**************************************************
 * 函数名：DisableMoter
 * 参数：None
 * 返回值：None
 * 功能：停止电机
 **************************************************/
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
	DisableMoter();
	MotorPulseWidth[motorctl] = rate;
	EnableMotor();
}

void SetMotorDir(uchar motorctl, uchar dir)
{
	
}