/*
 * File Name: HC-SR04.c
 * Author: Lexi
 * Date: 2015/03/10
 * 超声波模块
 * 使用2个IO口，Trig and Echo，Trig用于使能超声波，echo返回
 * trig可使用普通IO口，echo使用中断IO
 */

#include "config.h"
#include "HC-SR04.h"
#include "Timer.h"

#ifdef MODULE_SR04
struct Timer *timer[2];
uchar count;
uchar hc_flag;

void Init_hc_sr04(void)
{
	TRIG_OUT();
	ECHO_IN();
	ECHO_IES();
	
	if ((timer[0] = GetEmptyTimePoint(TIMER_TYPE_MS)) != NULL)
	{
		timer[0]->flag = TIMER_STOP;
		timer[0]->period = 50;
		timer[0]->timer_isr = start_hc_test;
		timer[0]->chksum = CalCheckSum((uchar *)timer[0], sizeof(struct Timer)-1);
	}
	if ((timer[1] = GetEmptyTimePoint(TIMER_TYPE_US)) != NULL)
	{
		timer[1]->flag = TIMER_STOP;
		timer[1]->period = 10;
		timer[1]->timer_isr = hc_sr04_timer_ISR();
		timer[1]->chksum = CalCheckSum((char *)timer[1], sizeof(struct Timer)-1);
	}
	hc_flag = 0;
}

void start_hc_test(void)
{
	
}

void hc_sr04_echo_ISR(void)
{
	Enable_HC_SR04_IE();
	count = 0;
}

void hc_sr04_timer_ISR(void)
{
	if (Check_echo_high())
		count++;
	else
	{
		StopTimer(timer);
		Disable_HC_SR04_IE();
		hc_flag |= TEST_OK;
	}
}



#endif