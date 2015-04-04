/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "timer.h"
#include "System.h"
#include "irda.h"

ulong	Second_count = 0;
uint	TimerBRate[7] = {32, 0, 0, 0, 0, 0, 0};

static struct Timer ms_timer[MS_MAX_TIMERS];
static struct Timer us_timer[US_MAX_TIMERS];

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

	memset((uchar *)&ms_timer[0], 0, sizeof(ms_timer));
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

struct Timer* GetTimerType(uchar type)
{
	if (type)
		return us_timer;
	
	return ms_timer;
}

uchar GetTimerMaxNum(uchar type)
{
	if (type)
		return US_MAX_TIMERS;

	return MS_MAX_TIMERS;
}

void UpdateTimer(uchar type)
{
	struct Timer *timer = GetTimerType(type);
	uchar	count = GetTimerMaxNum(type);
	uchar	index;
	
	for (index = 0; index < count; ++index)
	{
		if (timer->chksum != CalCheckSum((uchar *)timer, sizeof(struct Timer)-1))
			memset((uchar*)timer, 0, sizeof(struct Timer));
		
		if (timer->flag == TIMER_RUN)
		{
			if (--timer->count == 0)
			{
				timer->timer_isr();
				timer->count= timer->period;
			}
			timer->chksum = CalCheckSum((uchar*)timer, sizeof(struct Timer)-1);
		}
		timer++;
	}	
}

struct Timer* GetEmptyTimePoint(uchar type)
{
	uchar index;
	struct Timer *timer = GetTimerType(type);
	uchar num = GetTimerMaxNum(type);

	for (index = 0; index < num; ++index)
	{
		if (timer->flag == NO_USE_TIMER)
		{
			return timer;
		}
	}

	return NULL;
}

/*signed char AddTimer(struct Timer *t, uchar type)
{
	uchar index;
	struct Timer *timer = GetTimerType(type);
	uchar count = GetTimerMaxNum(type);

	for (index = 0; index < count; ++index)
	{
		if (timer->flag == NO_USE_TIMER)
		{
			timer->flag = t->flag;
			timer->count = t->period;
			timer->period = t->period;
			timer->timer_isr = t->timer_isr;
			timer->chksum = CalCheckSum((uchar *)timer,sizeof(struct Timer)-1);
			if (type)
				return index|0x40;
			return index;
		}
	}

	return -ERR_NO_TIMER;
}*/

void DelTimer(struct Timer * timer)
{
	if (timer != NULL)
		memset((uchar*)timer, 0, sizeof(struct Timer));
}

void StartTimer(struct Timer *timer)
{
	if (timer == NULL)
		return;
	
	if (timer->chksum != CalCheckSum((uchar *)timer, sizeof(struct Timer)-1))
	{
		memset((uchar *)timer, 0, sizeof(struct Timer));
		timer = NULL;
	}
	else
	{
		timer->flag = TIMER_RUN;
		timer->count = timer->period;
		timer->chksum = CalCheckSum((uchar *)timer, sizeof(struct Timer)-1);
	}
}

void StopTimer(struct Timer *timer)
{
	if (timer == NULL)
		return;

	if (timer->chksum == CalCheckSum((uchar *)timer,sizeof(struct Timer)-1))
	{
		timer->flag = TIMER_STOP;
		timer->chksum = CalCheckSum((uchar *)timer, sizeof(struct Timer)-1);
	}
	else
	{
		memset((uchar*)timer, 0, sizeof(struct Timer));
		timer = NULL;
	}
}

/**************************************************
 * ��������TimerB0_ISR
 * ������None
 * ����ֵ��None
 * ���ܣ���ʱ��B0�жϷ���
 **************************************************/
void TimerB0_ISR(void)
{
	UpdateTimer(TIMER_TYPE_MS);
	
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
	uint random = TBR;
	
	return random+TAR;
}

/**************************************************
 * ��������TimerB1_ISR
 * ������None
 * ����ֵ��None
 * ���ܣ���ʱ��B1�жϷ���
 **************************************************/
void TimerB1_ISR(void)
{
	if (TBIV&0x08)
	{
	  IRDA_TIMER_ISR();
	}
}

/*
* ��������TimerA3_Init
* ������None
* ����ֵ��None
* ���ܣ���ʼ��TimerA3
*/
void TimerA3_Init(void)
{
	TACTL	|= TASSEL_2 + MC_2 + ID_3;		// SMCLK, Continue Mode, DIV:8
	
	memset((uchar *)&us_timer[0], 0, sizeof(us_timer));
}

void TimerA_ISR(void)
{
	UpdateTimer(TIMER_TYPE_US);
}
