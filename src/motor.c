/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */

#include "config.h"
#include "motor.h"
#include "Timer.h"
#include "Irda.h"
#include "System.h"
#include "HC-SR04.h"

const uchar Directs[5] = {0x00, 0xAA, 0x55, 0xA5, 0x5A};
const uchar Motors[4] = {MOTOR_LF, MOTOR_LB, MOTOR_RF, MOTOR_RB};
static struct Timer *timer;
static uchar motor_flag;

/**************************************************
 * Init_Motor
 * ������None
 * ����ֵ��None
 * ���ܣ���ʼ��Motor������à **************************************************/
void Motor_Init(void)
{	
	// P4.1 P4.2 P4.3 P4.6: PWM������������Ƶ���ٶ�
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
	P2DIR	|= 0xff;

	timer = GetEmptyTimePoint(TIMER_TYPE_MS);
	timer->flag	= TIMER_STOP;
	timer->period = 55;
	timer->timer_isr = Motor_Status_Update;
	motor_flag = 0;
}

/**************************************************
 * ��������EnableMotor
 * ������None
 * ����ֵ��None
 * ���ܣ�����Motor���ʣ��������
**************************************************/
void EnableMotor(void)
{	
	P4DIR	|= BIT1+BIT2+BIT3+BIT6;
	P4SEL	|= BIT1+BIT2+BIT3+BIT6;
	StartTimer(timer);
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
 * ������motorctl: 0,���е��; 1���󷽵��;2���ҷ����   rate������
 * ����ֵ��None
 * ���ܣ����õ������
 **************************************************/
void SetMotorRate(uchar motorctl, uchar rate)
{
	if (rate <= 0 && rate > MAXRATE && motorctl > 2)
		return;
	
	if (motorctl == 0)            // ���е��
	{
		SetTimerBRate(MOTOR_LF, rate);
		SetTimerBRate(MOTOR_LB, rate);
		SetTimerBRate(MOTOR_RF, rate);
		SetTimerBRate(MOTOR_RB, rate);
	}
	else if (motorctl == 1)     // �����
	{
		SetTimerBRate(MOTOR_LF, rate);
		SetTimerBRate(MOTOR_LB, rate);
	}
	else if (motorctl == 2)   // �Ҳ���
	{
		SetTimerBRate(MOTOR_RF, rate);
		SetTimerBRate(MOTOR_RB, rate);
	}
}

/*
* ��������GetMaxRateCtl
* ������None
* ����ֵ��������±�
* ���ܣ���ȡ����ٶȵ�����±�
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
* ��������SetMotorDir
* ������motorctl: ���Ƶĵ����dir:����
* ����ֵ��None
* ���ܣ������������
***************************************************/
void SetMotorDirs(uchar dir)
{
	P2OUT	= Directs[dir];
	SyncMotorRate(dir);
}

/*
* ��������SyncMotorRate
* ������type: �������
* ����ֵ��None
* ���ܣ�ʹ����ﵽ�ض�������ģʽ�ٶ�
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

void Motor_Status_Update(void)
{
	uint ins = hc_get_instance();
	if (ins < 10)
	{
		SetMotorDirs(dirLEFT);
		SyncMotorRate(dirLEFT);
		motor_flag	|= bDIR;
	}
	else
	{
		SetMotorDirs(dirFRONT);
		SyncMotorRate(dirFRONT);
		motor_flag &= ~bDIR;
	}
}

uchar Get_Motor_Status(void)
{
	return motor_flag;
}

uchar Get_Motor_Rate(uchar *pdat, uchar motor_type)
{
	uint rate;
	
	if (motor_type == MOTOR_ALL)
	{
		rate = GetTimerBRate(MOTOR_LF);
		memcpy(&pdat[0], &rate, 2);
		rate = GetTimerBRate(MOTOR_LB);
		memcpy(&pdat[2], &rate, 2);
		rate = GetTimerBRate(MOTOR_RF);
		memcpy(&pdat[4], &rate, 2);
		rate = GetTimerBRate(MOTOR_RB);
		memcpy(&pdat[6], &rate, 2);
		return 8;
	}
	else
	{
		rate = GetTimerBRate(motor_type);
		memcpy(&pdat[0], &rate, 2);
		return 2;
	}
	return 0;
}