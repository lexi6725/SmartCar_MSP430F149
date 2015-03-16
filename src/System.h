/* 
 * File Name: System.h
 * Author: Lexi
 * Date: 2015/03/13
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/* SystemFlag Bits */
#define SystemOK	(1<<0)
#define PWMRUN		(1<<1)

extern uint SystemFlag;

extern void System_Init(void);

#endif