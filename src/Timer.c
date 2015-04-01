/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "timer.h"
#include "System.h"

ulong	Second_count = 0;
uint	TimerBRate[7] = {32, 32, 32, 32, 32, 32, 32};

void SyncTimerB(void);

void TimerB7_Init(void)
{
	/* TB1~TB3 TB6 To PWM Out Reset/Set */
	SyncTimerB();
	TBCCTL1 = OUTMOD_7;
	TBCCTL2 = OUTMOD_7;
	TBCCTL3 = OUTMOD_7;
	TBCCTL6 = OUTMOD_7;
	TBCTL |= TASSEL_1 + TBCLR + MC_1;		// ACLK + Up Mode
}

/**************************************************
 * ��������EnableTimerB
 * ������None
 * ����ֵ��None
 * ���ܣ�ʹ��TimerB��ʱ�� 
 **************************************************/
void DisableTimerB(void)
{
	TBCTL	= 0 | TBCLR;			// Disable Timer B
}

void SyncTimerB(void)
{
	TBCCR0 = TimerBRate[0];
	TBCCR1 = TimerBRate[1];
	TBCCR2 = TimerBRate[2];
	TBCCR3 = TimerBRate[3];
	TBCCR4 = TimerBRate[4];
	TBCCR5 = TimerBRate[5];
	TBCCR6 = TimerBRate[6];
}

/**************************************************
 * ��������SetTimerBRate
 * ������TimerBctl:���õĶ�ʱ����Rate������
 * ����ֵ��None
 * ���ܣ�����TimerB7��ʱ����ĳ����ʱ������
 **************************************************/
void SetTimerBRate(unsigned char TimerBctl, unsigned int Rate)
{
	TimerBRate[TimerBctl] = Rate;
}

/**************************************************
 * ��������TimerB0_ISR
 * ������None
 * ����ֵ��None
 * ���ܣ���ʱ��B0�жϷ���
 **************************************************/
uchar TimerB0_ISR(void)
{
	uchar ret = 0;
	
	if (++Second_count >= SIZE_1K)
	{
		SystemFlag	|= bSECOND;
		Second_count = 0;
		ret = 1;
	}
	
	SyncTimerB();
	
	return ret;
}

uint GetRandomNum(void)
{
	uint random = TBR;
	
	return random*TAR;
}

/**************************************************
 * ��������TimerB1_ISR
 * ������None
 * ����ֵ��None
 * ���ܣ���ʱ��B1�жϷ���
 **************************************************/
uchar TimerB1_ISR(void)
{
	return 0;
}


void TimerA3_Init(void)
{
	TACTL	|= TASSEL_2 + MC_2 + ID_3;
}
