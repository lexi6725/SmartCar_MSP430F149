/*
 * File Name: HC-SR04.h
 * Author: Lexi
 * Date: 2015/03/10
 */

#ifndef __HC_SR04_H__
#define __HC_SR04_H__

#define TRIG_OUT()			(P4DIR	|= BIT0)
#define ECHO_IN()			(P1DIR	&= ~BIT0)
#define ECHO_IES()			(P1IES	&= ~BIT0)
#define Enable_HC_SR04_IE()	(P1IE	|= BIT0)
#define Disable_HC_SR04_IE() (P1IE	&= ~BIT0)
#define Check_echo_high()	(P1IN&BITO)

#define TEST_START	(1<<0)
#define TEST_OK		(1<<1)


#endif