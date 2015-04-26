/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "timer.h"
#include "System.h"
#include "irda.h"

uint	TimerBRate[7] = {32, 0, 0, 0, 0, 0, 0};

static struct Timer *timer = NULL;

void SyncTimerB(void);

/*
* ��������TimerB7_Init
* ������None
* ����ֵ��None
* ���ܣ���ʼ����ʱ��B7
*/
void TimerB7_Init(void)
{
	SyncTimerB();			// Set TimerB7 Period
	
	/* TB1~TB3 TB6 To PWM Out Reset/Set */
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

/*
* ��������SyncTimerB
* ������None
* ����ֵ��None
* ���ܣ�ͬ����ʱ����ʱ����
*/
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

/*
* ��������SetIrdaPeriod
* ������rate: ����Irda��ʱ
* ����ֵ��None
* ���ܣ�ΪIrdaģ���ṩ���ö�ʱʱ��
*/
void SetIrdaPeriod(unsigned int rate)
{
	TBCCR4	= rate;
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

/*
* ��������GetTimerBRate
* ������TimerBctl����ʱ��Bx
* ����ֵ��None
* ���ܣ���ȡָ����ʱ���Ķ�ʱʱ��
*/
unsigned int GetTimerBRate(unsigned char TimerBctl)
{
	return TimerBRate[TimerBctl];
}

void UpdateTimer(uchar type)
{
	struct Timer *t = timer;
	
	while(t != NULL)
	{
		if (t->tmr_type == type)
		{
			if (t->tmr_state == TMR_STATE_RUNNING)
			{
				if (t->tmr_count++ == t->tmr_period)
				{
					t->tmr_isr();
					if (t->tmr_opt == TMR_OPT_ONE_SHOT)
					{
						t->tmr_state = TMR_STATE_STOPPED;
					}
					if (t->tmr_opt == TMR_OPT_PERIODIC)
					{
						t->tmr_count = 0;
					}
				}
			}
		}
		t = t->next;
	}
	
}

void AddTimer(struct Timer *t)
{
	_DINT();
	if (timer == NULL)
	{
		timer = t;
		t->tmr_prev = NULL;
		t->next = NULL;
	}
	else
	{
		timer->tmr_next = t;
		t->tmr_prev = timer;
		t->tmr_next = timer->tmr_next;
	}
	_EINT();
}

void DelTimer(struct Timer * t)
{
	_DINT():
	if (timer == t)
	{
		timer = t->tmr_next;
		t->tmr_next->tmr_prev = timer;
	}
	else
	{
		t->tmr_prev->tmr_next = t->tmr_next;
		t->tmr_next->tmr_prev = t->tmr_prev;
	}
	t->tmr_next = NULL;
	t->tmr_prev = NULL;
	_EINT():
}

void StartTimer(struct Timer *t)
{
	t->state = TMR_STATE_RUNNING;
}

void StopTimer(struct Timer *timer)
{
	if (timer == NULL && timer->flag == TMR_STATE_UNUSED)
		return;

	timer->tmr_state = TMR_STATE_STOPPED;
}

/**************************************************
 * ��������TimerB0_ISR
 * ������None
 * ����ֵ��None
 * ���ܣ���ʱ��B0�жϷ���
 **************************************************/
void TimerB0_ISR(void)
{
	UpdateTimer(TMR_TYPE_1KHz);
	
	SyncTimerB();     // ��һ����ʱ���ں���¶�ʱ��
}

/*
* ��������GetRandomNum
* ������None
* ����ֵ��None
* ���ܣ���ȡһ�������
*/
uint GetRandomNum(void)
{	
	return TAR;
}

/**************************************************
 * ��������TimerB1_ISR
 * ������None
 * ����ֵ��None
 * ���ܣ���ʱ��B1�жϷ���
 **************************************************/
void TimerB1_ISR(void)
{
	#if defined(MODULE_IRDA)
	if (TBIV&0x08)
	{
	  IRDA_TIMER_ISR();
	}
	#endif
}

/*
* ��������TimerA3_Init
* ������None
* ����ֵ��None
* ���ܣ���ʼ��TimerA3
*/
void TimerA3_Init(void)
{
	TACTL	|= TASSEL_2 + MC_1 + ID_3 + TACLR;		// SMCLK, Up Mode, DIV:8
	TACCR0	= 32;
	TACCTL0	|= CCIE;
}

void TimerA_ISR(void)
{
	UpdateTimer(TMR_TYPE_50KHz);
}
