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

#define		MODULE_PWM			// PWM�������ģ��
#define		MODULE_TIMER		// ��ʱ��ģ��
#define		MODULE_SR04			//������ģ��
#define		MODULE_NRF24L01
//#define		MODULE_IRDA

#define		SIZE_1K		(1<<10)
#define		SIZE_1M		(1<<20)

#define TIMER_MAX_NUM	4			//�����ʱ������
#define TMR_RTC_SECOND		0
#define TMR_MOTOR_FREQ		1
#define	TMR_MOTOR_LEFT		2
#define	TMR_MOTOR_RIGHT 	3

#endif