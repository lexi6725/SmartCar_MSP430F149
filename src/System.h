/* 
 * File Name: System.h
 * Author: Lexi
 * Date: 2015/03/13
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/* SystemFlag Bits */
#define bSystemOK	(1<<0)
#define bPWMRUN		(1<<1)
#define bSECOND		(1<<2)
#define bNRF_READY	(1<<3)
#define bNRF_ENABLE	(1<<4)

extern uint SystemFlag;

extern void System_Init(void);
extern uchar CalCheckSum(uchar *pdat, uchar len);
#endif