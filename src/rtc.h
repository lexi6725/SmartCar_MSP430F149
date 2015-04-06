/*
 * File Name: rtc.h
 * Author: Lexi
 * Date: 2013/04/06
 */

#ifndef __RTC_H__
#define __RTC_H__

#define bSecond		(1<<0)
#define bMinute		(1<<1)
#define bHour		(1<<2)
#define bDay		(1<<3)
#define bMonth		(1<<4)
#define bYear		(1<<5)


extern uchar RTC_Flag;

extern void Init_RTC(void);
extern void Second_ISR(void);
#endif
