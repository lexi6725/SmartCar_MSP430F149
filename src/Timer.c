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

	memset((uchar *)&ms_timer[0], 0, sizeof(ms_timer));
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
 * 函数名：TimerB0_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B0中断服务
 **************************************************/
void TimerB0_ISR(void)
{
	UpdateTimer(TIMER_TYPE_MS);
	
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
	uint random = TBR;
	
	return random+TAR;
}

/**************************************************
 * 函数名：TimerB1_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B1中断服务
 **************************************************/
void TimerB1_ISR(void)
{
	if (TBIV&0x08)
	{
	  IRDA_TIMER_ISR();
	}
}

/*
* 函数名：TimerA3_Init
* 参数：None
* 返回值：None
* 功能：初始化TimerA3
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
