/*
 * File Name: motor.h
 * Author: Lexi
 * Date: 2013/03/18
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MAXMOTORNUM		4

#define MAXRATE		31

#define		MOTOR_PWM_DIR_OUT		(P6DIR	|= (BIT0+BIT1))
#define		MOTOR_OUT_1_PWM(x)		(P6OUT	|= (BIT0<<x))
#define		MOTOR_OUT_0_PWM(x)		(P6OUT &= ~(BIT0<<x))

#define 	MOTOR_DIRECT_DIR_OUT	(P6DIR	|= (BIT2+BIT3+BIT4+BIT5))
#define		MOTOR_DIRECT_FORWARD(x)	(P6OUT	&= ~(0x3<<(((x)+1)*2)); P6OUT	|= (0x2<<(((x)+1)*2)))
#define		MOTOR_DIRECT_REV(x)		(P6OUT	&= ~(0x3<<(((x)+1)*2)); P6OUT	|= (0x1<<(((x)+1)*2)))
#define		MOTOR_DIRECT_STOP(x)	(P6OUT	&= ~(0x3<<(((x)+1)*2)))

extern void Motor_Init(void);
extern void EnableMotor(void);
extern void DisableMoter(void);

#endif