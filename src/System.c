/*
 * File Name: System.c
 * Author: Lexi
 * Date: 2015/03/11
 */

#include "config.h"
#include "Timer.h"
#include "motor.h"

uint SystemFlag = 0;

/****************************************************
 * ��������Init_clk
 * ������None
 * ����ֵ��None
 * ���ܣ���ʼ��ϵͳʱ��
 ****************************************************/
void Init_clk(void)
{
	BCSCTL1	&= ~XT2OFF;			// ��XT2�񵴇�	BCSCTL2	|= SELM1+SELS+DIVS_3;		// MCLKدMHz, SMCLKدMHz
	
	do{
		IFG1 &= ~OFIFG;			// �������������		for(i = 0; i < 100; ++i)
			_NOP();				// ��ʱ�ȴ�
	}while((IFG1&OFIFG) != 0);	// ���������־����������ȏ�	
	IFG1 &= ~OFIFG;
}

/**********************************************************
 * ��������System_Init
 * ������None
 * ���ܣ���ʼ��ϵͳ
 **********************************************************/
void System_Init(void)
{
	Init_clk();
	Motor_Init();
	TimerB7_Init();
	TimerA3_Init();
	
	ENABLE_TIMERB0();
	EnableMotor();
	SetMotorDirs(dirFORWARD);
	
	_EINT();
	
	SetMotorDirs(dirFORWARD);
}