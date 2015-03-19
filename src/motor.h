/*
 * File Name: motor.h
 * Author: Lexi
 * Date: 2013/03/18
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR1		0
#define MOTOR2		1
#define MOTOR3		2
#define MOTOR4		3

extern void Init_Motor(void);
extern void EnableMotor(void);
extern void DisableMoter(void);
extern void SetMotorRate(uchar motorctl, uint rate);
#endif