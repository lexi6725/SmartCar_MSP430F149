/*
 * File Name: timer.c
 * Author: Lexi
 * Date: 2015/03/10
 */

#include "config.h"
#include "types.h"
#include "timer.h"
#include "System.h"


static Timer_t TimerArray[TIMER_MAX_NUM];

/*
* 函数名：Timer_Init
* 参数：None
* 返回值：None
* 功能：初始化定时器
*/
void Timer_Init(void)
{
	// TimerA3
	TACTL	|= TASSEL_2 + MC_1 + ID_0 + TACLR;		// SMCLK, Up Mode, DIV:8
	TACCR0	= (1<<16)-1;					// 1Hz
	TACCTL0	|= CCIE;

	// TimerB7
	TBCCR0 = 0x20;							// 1KHz
	TBCTL |= TASSEL_1 + TBCLR + MC_1;		// ACLK + Up Mode
	TBCCTL0 |= CCIE;
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

uint8_t UpdateTimer(uint8_t type)
{
	uint8_t index, ret_value;
	Timer_t *pTimer = &TimerArray[0];
	ret_value = 0;

	for (index = 0; index < TIMER_MAX_NUM; ++index)
	{
		if ((pTimer->Tmr_Opt&(TMR_STATE_USED|TMR_STATE_STARTED|TMR_OPT_HIGH)==(TMR_STATE_USED|TMR_STATE_STARTED|type))
		{
			pTimer->Tmr_Count++;
			if (pTimer->Tmr_Count==pTimer->Tmr_Period)
			{
				pTimer->Tmr_Count = 0;
				ret_value += pTimer->Tmr_CallBack();
				if (pTimer->Tmr_Opt&TMR_OPT_ONE_SHOT)
					pTimer->opt	&= ~TMR_STATE_STARTED;
			}
		}
	}

	return ret_value;
}

uint8_t TimerCreate(uint8_t TimerIndex, 
						TMR_CALLBACK CallBack, 
						uint16_t period,
						uint8_t opt
						)
{
	if (TimerIndex>TIMER_MAX_NUM || TimerArray[TimerIndex].opt&TMR_STATE_USED)
		return 0x81;			// -1
		
	_DINT();
	TimerArray[TimerIndex].Tmr_CallBack = CallBack;
	TimerArray[TimerIndex].Tmr_Period = period;
	TimerArray[TimerIndex].Tmr_Opt = opt|TMR_STATE_USED;
	TimerArray[TimerIndex].Tmr_Count = 0;
	_EINT();
}

uint8_t	TimerChangeState(uint8_t TimerIndex, uint8_t state, uint8_t flag)
{
	if (TimerIndex>TIMER_MAX_NUM || TimerArray[TimerIndex].opt&TMR_STATE_USED)
		return 0x81;			// -1

	_DINT();
	if (flag)
		TimerArray[TimerIndex].opt |= state;
	else
		TimerArray[TimerIndex].opt &= ~state;
	_EINT();
}

/**************************************************
 * 函数名：TimerB0_ISR
 * 参数：None
 * 返回值：None
 * 功能：定时器B0中断服务
 **************************************************/
void TimerB0_ISR(void)
{
	UpdateTimer(TMR_OPT_HIGH);
}

void TimerA_ISR(void)
{
	UpdateTimer(0);
}
