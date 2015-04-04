/*
 * File Name: motor.h
 * Author: Lexi
 * Date: 2013/03/18
 */

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_ALL		0
#define MOTOR_LF		1
#define MOTOR_LB		2
#define MOTOR_RF		3
#define MOTOR_RB		6

#define MAXMOTORNUM		4

/* ���������*/
#define dirDEBOOST		0

// ��ת,��ת,ǰ���������ǰת
#define dirFRONT		1
#define dirLEFTFRONT	1
#define dirRIGHTFRONT	1
// ����,����,���˵��������ת
#define dirBACK			2
#define dirLEFTBACK		2
#define dirRIGHTBACK		2
// ����ת,����ת��������෴
#define dirLEFT			3
#define	dirRIGHT		4

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
extern void SetMotorDirs(uchar dir);
extern void SyncMotorRate(uchar type);
#endif