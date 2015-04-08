/*
 * File Name: config.h
 * Author: Lexi
 * Date: 2015/03/10
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <msp430x14x.h>

#define		MODULE_PWM			// PWM电机驱动模块
#define		MODULE_TIMER		// 定时器模块
#define		MODULE_SR04			//超声波模块
#define		MODULE_NRF24L01

#define		SIZE_1K		(1<<10)
#define		SIZE_1M		(1<<20)


typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned long	ulong;

#endif