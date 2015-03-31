/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */

#include "config.h"
#include "motor.h"
#include "Timer.h"

const uchar Directs[5] = {0x00, 0xAA, 0x55, 0xA5, 0x5A};
/**************************************************
 * Init_Motor
 * 参数：None
 * 返回值：None
 * 功能：初始化Motor所用引脿 **************************************************/
void Motor_Init(void)
{	
	// P4.1 P4.2 P4.3 P4.6: PWM脉冲输出，控制电机速度
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
}

/**************************************************
 * 函数名：EnableMotor
 * 参数：None
 * 返回值：None
 * 功能：设置Motor速率，启动电朿 **************************************************/
void EnableMotor(void)
{	
	P4SEL	|= BIT1+BIT2+BIT3+BIT6;
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
}

/**************************************************
 * 函数名：DisableMoter
 * 参数：None
 * 返回值：None
* 功能：停止电机 
**************************************************/
void DisableMoter(void)
{
	P4SEL	&= ~(BIT1+BIT2+BIT3+BIT6);
	P4DIR	&= ~(BIT1+BIT2+BIT3+BIT6);
}

/**************************************************
 * 函数名：SetMotorRate
 * 参数：motorctl: 控制的电机，rate：速率
 * 返回值：None
 * 功能：设置电机速率
 **************************************************/
void SetMotorRate(uchar motorctl, uint rate)
{
	if (rate = 0 && rate > MAXRATE && motorctl < 4)
		return;
	
	if (motorctl == 0)
	{
		SetTimerBRate(MOTOR_LF, rate);
		SetTimerBRate(MOTOR_LB, rate);
		SetTimerBRate(MOTOR_RF, rate);
		SetTimerBRate(MOTOR_RB, rate);
	}
	else
		SetTimerBRate(motorctl, rate);
}

/**************************************************
* 函数名：SetMotorDir
* 参数：motorctl: 控制的电机，dir:方向
* 返回值：None
* 功能：调整电机方向
***************************************************/
void SetMotorDirs(uchar dir)
{
	P2OUT	= Directs[dir];
}