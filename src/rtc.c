/*
 * File Name: main.c
 * Author: Lexi
 * Date: 2013/03/13
 */

#include "config.h"
#include "rtc.h"
#include "Timer.h"
#include "System.h"

uchar RTC_Flag;

static struct Timer *timer;

void Init_RTC(void)
{
	RTC_Flag = 0;

	timer = GetEmptyTimePoint(TIMER_TYPE_MS);
	timer->flag = TIMER_STOP;
	timer->period = 1024;
	timer->timer_isr = Second_ISR;
	StartTimer(timer);
}

void Second_ISR(void)
{
	RTC_Flag	|= bSecond;
}

