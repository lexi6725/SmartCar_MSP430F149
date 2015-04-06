/*
 * File Name: HC-SR04.h
 * Author: Lexi
 * Date: 2015/03/10
 */

#ifndef __HC_SR04_H__
#define __HC_SR04_H__

#define TRIG_OUT()			(P4DIR	|= BIT0)
#define TRIG_OUT_HIGH()		(P4OUT	|= BIT0)
#define TRIG_OUT_LOW()		(P4OUT	&= ~BIT0)
#define ECHO_IN()			(P1DIR	&= ~BIT0)
#define ECHO_IES()			(P1IES	&= ~BIT0)
#define Enable_HC_SR04_IE()	(P1IE	|= BIT0)
#define Disable_HC_SR04_IE() (P1IE	&= ~BIT0)
#define Check_echo_high()	(P1IN&BIT0)
#define CHECK_HC_ECHO()		(P1IFG&BIT0)

#define bTEST_START		(1<<0)
#define bECHO			(1<<1)
#define bTEST_OK		(1<<2)

extern void Init_hc_sr04(void);
extern void Enable_hc_test(void);
extern void Disable_hc_test(void);
extern void start_hc_test(void);
extern void hc_sr04_echo_ISR(void);
extern void hc_sr04_timer_ISR(void);
extern uint hc_get_instance(void);
#endif