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
* 函数名：TimerB7_Init
* 参数：None
* 返回值：None
* 功能：初始化定时器B7
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
 * 函数名：EnableTimerB
 * 参数：None
 * 返回值：None
 * 功能：使能TimerB定时器 
 **************************************************/
void DisableTimerB(void)
{
	TBCTL	= 0 | TBCLR;			// Disable Timer B
}

/*
* 函数名：SyncTimerB
* 参数：None
* 返回值：None
* 功能：同步定时器定时周期
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
* 函数名：SetIrdaPeriod
* 参数：rate: 设置Irda定时
* 返回值：None
* 功能：为Irda模块提供设置定时时间
*/
void SetIrdaPeriod(unsigned int rate)
{
	TBCCR4	= rate;
}

/**************************************************
 * 函数名：SetTimerBRate
 * 参数：TimerBctl:配置的定时器＿Rate：速率
 * 返回值：None
 * 功能：配置TimerB7定时器的某个定时器速率
 **************************************************/
void SetTimerBRate(unsigned char TimerBctl, unsigned int Rate)
{
	TimerBRate[TimerBctl] = Rate;
}

/*
* 函数名：GetTimerBRate
* 参数：TimerBctl：定时器Bx
* 返回值：None
* 功能：获取指定定时器的定时时间
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
 * 函数名：TimerB0_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B0中断服务
 **************************************************/
void TimerB0_ISR(void)
{
	UpdateTimer(TMR_TYPE_1KHz);
	
	SyncTimerB();     // 在一个定时周期后更新定时器
}

/*
* 函数名：GetRandomNum
* 参数：None
* 返回值：None
* 功能：获取一个随机数
*/
uint GetRandomNum(void)
{	
	return TAR;
}

/**************************************************
 * 函数名：TimerB1_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B1中断服务
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
* 函数名：TimerA3_Init
* 参数：None
* 返回值：None
* 功能：初始化TimerA3
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
