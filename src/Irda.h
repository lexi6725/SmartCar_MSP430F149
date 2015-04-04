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

#define IRDA_RECV			(1<<0)
#define IRDA_OK				(1<<1)
#define IRDA_START_TIMER	(1<<2)

#define CH_REDUCE		0x45
#define CH_DEFAULT		0x46
#define CH_INCREASE		0x47
#define PREV			0x44
#define NEXT			0x40
#define PLAY_PAUSE		0x43
#define ADD				0x07
#define REDUCE			0x15
#define EQ				0xD9
#define ADD_100			0x19
#define ADD_200			0x0D
#define DIGIT_0			0x16
#define DIGIT_1			0x0C
#define DIGIT_2			0x18
#define DIGIT_3			0x5E
#define DIGIT_4			0x08
#define DIGIT_5			0x1C
#define DIGIT_6			0x5A
#define DIGIT_7			0x42
#define DIGIT_8			0x52
#define DIGIT_9			0x4A

extern uchar Irda_Time;

extern void Init_Irda(void);
extern void IRDA_TIMER_ISR(void);
extern void IRDA_ISR(void);
extern void Irda_Process(void);
#endif
