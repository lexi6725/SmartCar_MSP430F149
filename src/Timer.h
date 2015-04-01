/*
 * File Name: timer.h
 * Author: Lexi
 * Date: 2015/03/10
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#define TIMERB0		0x0
#define TIMERB1		0x01
#define TIMERB2		0x02
#define TIMERB3		0x03
#define TIMERB4		0x04
#define TIMERB5		0x05
#define TIMERB6		0x06

#define MCLK_FREQ		(1<<23)
#define SMCLK_FREQ		(1<<20)
#define ACLK_FREQ		(1<<16)
#define TIMERB_FREQ		(1<<10)

#define DISABLE_TIMERB0()		(TBCCTL0 &= ~CCIE)
#define DISABLE_TIMERB1()		(TBCCTL1 &= ~CCIE)
#define DISABLE_TIMERB2()		(TBCCTL2 &= ~CCIE)
#define DISABLE_TIMERB3()		(TBCCTL3 &= ~CCIE)
#define DISABLE_TIMERB4()		(TBCCTL4 &= ~CCIE)
#define DISABLE_TIMERB5()		(TBCCTL5 &= ~CCIE)
#define DISABLE_TIMERB6()		(TBCCTL6 &= ~CCIE)

#define ENABLE_TIMERB0()		(TBCCTL0 |= CCIE)
#define ENABLE_TIMERB1()		(TBCCTL1 |= CCIE)
#define ENABLE_TIMERB2()		(TBCCTL2 |= CCIE)
#define ENABLE_TIMERB3()		(TBCCTL3 |= CCIE)
#define ENABLE_TIMERB4()		(TBCCTL4 |= CCIE)
#define ENABLE_TIMERB5()		(TBCCTL5 |= CCIE)
#define ENABLE_TIMERB6()		(TBCCTL6 |= CCIE)

extern void TimerA3_Init(void);
extern void TimerB7_Init(void);
extern void EnableTimerB(uchar ctrbit);
extern void DisableTimerB(void);
extern void SetTimerBRate(unsigned char TimerBctl, unsigned int Rate);

extern uint	GetRandomNum(void);

extern uchar TimerB0_ISR(void);
extern uchar TimerB1_ISR(void);
#endif