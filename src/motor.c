/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */

#include "config.h"
#include "motor.h"
#include "Timer.h"
#include "Irda.h"

const uchar Directs[5] = {0x00, 0xAA, 0x55, 0xA5, 0x5A};
const uchar Motors[4] = {MOTOR_LF, MOTOR_LB, MOTOR_RF, MOTOR_RB};
/**************************************************
 * Init_Motor
 * 参数：None
 * 返回值：None
 * 功能：初始化Motor所用引脿 **************************************************/
void Motor_Init(void)
{	
	// P4.1 P4.2 P4.3 P4.6: PWM脉冲输出，控制电机速度
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
	P2DIR	|= 0xff;
}

/**************************************************
 * 函数名：EnableMotor
 * 参数：None
 * 返回值：None
 * 功能：设置Motor速率，启动电机
**************************************************/
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
 * 参数：motorctl: 0,所有电机; 1，左方电机;2，右方电机   rate：速率
 * 返回值：None
 * 功能：设置电机速率
 **************************************************/
void SetMotorRate(uchar motorctl, uint rate)
{
	if (rate <= 0 && rate > MAXRATE && motorctl > 2)
		return;
	
	if (motorctl == 0)            // 所有电机
	{
		SetTimerBRate(MOTOR_LF, rate);
		SetTimerBRate(MOTOR_LB, rate);
		SetTimerBRate(MOTOR_RF, rate);
		SetTimerBRate(MOTOR_RB, rate);
	}
	else if (motorctl == 1)     // 左侧电机
	{
		SetTimerBRate(MOTOR_LF, rate);
		SetTimerBRate(MOTOR_LB, rate);
	}
	else if (motorctl == 2)   // 右侧电机
	{
		SetTimerBRate(MOTOR_RF, rate);
		SetTimerBRate(MOTOR_RB, rate);
	}
}

/*
* 函数名：GetMaxRateCtl
* 参数：None
* 反回值：最大电机下标
* 功能：获取最大速度电机的下标
*/
unsigned char GetMaxRateCtl(void)
{
	uchar i, ctl;

	ctl = 0;
	for (i = 1; i < MAXMOTORNUM; ++i)
	{
		if (GetTimerBRate(Motors[i-1])<GetTimerBRate(Motors[i]))
			ctl = i;
	}
	return ctl;
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

/*
* 函数名：SyncMotorRate
* 参数：type: 电机方向
* 返回值：None
* 功能：使电机达到特定的运行模式速度
*/
void SyncMotorRate(uchar type)
{
	uchar max_rate_ctl = GetMaxRateCtl();
	if (type == dirFRONT|| type == dirBACK|| type == dirLEFT|| type == dirRIGHT || type == dirDEBOOST)
		SetMotorRate(MOTOR_ALL, GetTimerBRate(max_rate_ctl));
	else if (type == dirLEFTFRONT|| type == dirLEFTBACK)
	{
		SetMotorRate(1, 0);
		SetMotorRate(2, GetTimerBRate(max_rate_ctl));
	}
	else if (type == dirRIGHTFRONT|| type == dirRIGHTBACK)
	{
		SetMotorRate(1, GetTimerBRate(max_rate_ctl));
		SetMotorRate(2, 0);
	}
}