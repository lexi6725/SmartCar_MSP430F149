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
 * ������None
 * ����ֵ��None
 * ���ܣ���ʼ��Motor������à **************************************************/
void Motor_Init(void)
{	
	// P4.1 P4.2 P4.3 P4.6: PWM������������Ƶ���ٶ�
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
}

/**************************************************
 * ��������EnableMotor
 * ������None
 * ����ֵ��None
 * ���ܣ�����Motor���ʣ�������c **************************************************/
void EnableMotor(void)
{	
	P4SEL	|= BIT1+BIT2+BIT3+BIT6;
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
}

/**************************************************
 * ��������DisableMoter
 * ������None
 * ����ֵ��None
* ���ܣ�ֹͣ��� 
**************************************************/
void DisableMoter(void)
{
	P4SEL	&= ~(BIT1+BIT2+BIT3+BIT6);
	P4DIR	&= ~(BIT1+BIT2+BIT3+BIT6);
}

/**************************************************
 * ��������SetMotorRate
 * ������motorctl: ���Ƶĵ����rate������
 * ����ֵ��None
 * ���ܣ����õ������
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
* ��������SetMotorDir
* ������motorctl: ���Ƶĵ����dir:����
* ����ֵ��None
* ���ܣ������������
***************************************************/
void SetMotorDirs(uchar dir)
{
	P2OUT	= Directs[dir];
}