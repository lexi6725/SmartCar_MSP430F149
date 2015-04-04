/*
 * File Name: System.c
 * Author: Lexi
 * Date: 2015/03/11
 */

#include "config.h"
#include "Timer.h"
#include "motor.h"
#include "irda.h"

uint SystemFlag = 0;      // ϵͳ��־

/****************************************************
 * ��������Init_clk
 * ������None
 * ����ֵ��None
 * ���ܣ���ʼ��ϵͳʱ��
 ****************************************************/
void Init_clk(void)
{
	uchar i;
	
	BCSCTL1	&= ~XT2OFF;			// ��XT2����
	
	do{
		IFG1 &= ~OFIFG;			// �������������
		for (i = 0xff; i>0; --i);	// ��ʱ�ȴ�
	}while((IFG1&OFIFG) != 0);	// ���������־����������ȏ�	
	
	BCSCTL2	= SELM1 + SELS;	// MCLK and SMCLK Select XT2CLK	8MHz
}

/**********************************************************
 * ��������System_Init
 * ������None
 * ���ܣ���ʼ��ϵͳ
 **********************************************************/
void System_Init(void)
{
	Init_clk();               // ��ʼ��ϵͳʱ��
	Motor_Init();             // ��ʼ�����
	TimerB7_Init();           // ��ʼ����ʱ��TimerB
	TimerA3_Init();           // ��ʼ����ʱ��TimerA3
	
	ENABLE_TIMERB0();         // ������ʱ��TimerB0�ж�
	EnableMotor();            // ʹ�ܵ��            
	SetMotorDirs(dirFRONT); // ���õ����ʼ����
	Init_Irda();              // ��ʼ������
	_EINT();                  // ʹ�����ж�
}