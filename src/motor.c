/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */
/*
* ��ǰ����(��ǰ����)����PWM���������
* P6[0:1]: PWM Out Left/Right Motor  P6.0 ��  P6.1��
* P6[2:3]: ��ǰ���ַ������
* P6[4:5]: ��ǰ���ַ������
* 		    Directions: Bit0  Bit1
		     ��ת:    1      0
		     ��ת:    0      1
*/

#include "config.h"
#include "motor.h"
#include "Timer.h"
#include "Irda.h"
#include "System.h"
#include "HC-SR04.h"

static uchar motor_flag;

/**************************************************
 * Init_Motor
 * ������None
 * ����ֵ��None
 * ���ܣ���ʼ��Motor������à **************************************************/
void Motor_Init(void)
{	
	//P6.0 and P6.1: PWM������������Ƶ���ٶ�
	P6OUT	= 0;
	P6DIR	|= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5;

	motor_flag = 0;
}

/**************************************************
 * ��������EnableMotor
 * ������None
 * ����ֵ��None
 * ���ܣ�����Motor���ʣ��������
**************************************************/
void EnableMotor(void)
{	

}

/**************************************************
 * ��������DisableMoter
 * ������None
 * ����ֵ��None
* ���ܣ�ֹͣ��� 
**************************************************/
void DisableMoter(void)
{
}
