/*
* 文件名：Irda.h
* 作者：lexi
* 日期：2015/03/30
*/

#ifndef __IRDA_H__
#define __IRDA_H__

#define IRDA	BIT5
#define ENABLE_IRDA()	(P1IE	|= IRDA)
#define DISABLE_IRDA()	(P1IE	&= ~IRDA)
#define CHECK_IRDA()	(P1IFG&IRDA)
#define CLR_IRDA_FLG()	(P1IFG&=~IRDA)

#define IRDA_TIMER_PERIOD	4
#define IRDA_TIMERB			TIMERB4

#define IRDA_RECV		(1<<0)
#define IRDA_OK			(1<<1)

#define LEFT_ROTATE		0x08
#define RIGHT_ROTATE	0x5A
#define	FORWARD_ROTATE	0x18
#define	ROLLBACK_ROTATE	0x52
#define LEFT_FORWARD	0x0C
#define RIGHT_FORWARD	0x5E
#define LEFT_ROLLBACK	0x42
#define	RIGHT_ROLLBACK	0x4A

extern uchar Irda_Time;

extern void Init_Irda(void);
extern void IRDA_TIMER_ISR(void);
extern void IRDA_ISR(void);
extern void Irda_Process(void);
#endif