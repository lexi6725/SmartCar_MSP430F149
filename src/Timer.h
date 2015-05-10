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

typedef int (*TMR_CALLBACK)(void);

typedef struct {
	uint16_t		Tmr_Count;		/* Timer expires */
	uint16_t		Tmr_Period;		/* Timer Period */
	TMR_CALLBACK	Tmr_CallBack;	/* When Timer count == period, run the function*/
	uint8_t			Tmr_Opt;		/* TMR Options: TMR_OPT_ONE_SHOT/TMR_OPT_PERIODIC*/
} Timer_t;


/* Struct Timer's state defined*/
#define TMR_STATE_USED		(1<<0)
#define TMR_STATE_STARTED	(1<<1)

#define TMR_OPT_ONE_SHOT	(1<<2)
#define TMR_OPT_HIGH		(1<<3)

extern void TimerA3_Init(void);
extern void TimerB7_Init(void);
extern void EnableTimerB(uchar ctrbit);
extern void DisableTimerB(void);
extern void SetTimerBRate(unsigned char TimerBctl, unsigned int Rate);

extern uint	GetRandomNum(void);

extern void TimerB0_ISR(void);
extern void TimerB1_ISR(void);
extern void TimerA_ISR(void);
extern void SetIrdaPeriod(unsigned int rate);
extern unsigned int GetTimerBRate(unsigned char TimerBctl);

extern struct Timer* GetEmptyTimePoint(uchar type);
extern void DelTimer(struct Timer * timer);
extern void StartTimer(struct Timer *timer);
extern void StopTimer(struct Timer *timer);
extern void UpdateTimer(uchar type);
#endif
