/*
 * File Name: motor.h
 * Author: Lexi
 * Date: 2013/03/18
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_LF		0
#define MOTOR_LB		1
#define MOTOR_RF		2
#define MOTOR_RB		3

#define MAXMOTORNUM		3

// 电机方向定义
#define dirDEBOOST		0x00
#define dirFORWARD		0x01
#define dirROLLBACK		0x02
#define dirLEFT			0x03
#define	dirRIGHT		0x04

#define MAXRATE		31

struct Direct{
	int		x;
	int		y;
	int		z;
};

struct Motor {
	uchar	MotorFlag;
	uint*	MotorRate[4];
	
	struct Direct dir;
	float	angle;
};

extern void Motor_Init(void);
extern void EnableMotor(void);
extern void DisableMoter(void);
extern void SetMotorRate(uchar motorctl, uint rate);
extern void SetMotorDir(uchar motorctl, uchar dir);
extern void SetMotorDirs(uchar dir);
#endif