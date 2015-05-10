/*
 * File Name: motor.c
 * Author: Lexi
 * Date: 2013/03/18
 */
/*
* 左前后轮(右前后轮)共用PWM及方向控制
* P6[0:1]: PWM Out Left/Right Motor  P6.0 左  P6.1右
* P6[2:3]: 左前后轮方向控制
* P6[4:5]: 右前后轮方向控制
* 		    Directions: Bit0  Bit1
		     正转:    1      0
		     反转:    0      1
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
 * 参数：None
 * 返回值：None
 * 功能：初始化Motor所用引脿 **************************************************/
void Motor_Init(void)
{	
	//P6.0 and P6.1: PWM脉冲输出，控制电机速度
	P6OUT	= 0;
	P6DIR	|= BIT0+BIT1+BIT2+BIT3+BIT4+BIT5;

	motor_flag = 0;
}

/**************************************************
 * 函数名：EnableMotor
 * 参数：None
 * 返回值：None
 * 功能：设置Motor速率，启动电机
**************************************************/
void EnableMotor(void)
{	

}

/**************************************************
 * 函数名：DisableMoter
 * 参数：None
 * 返回值：None
* 功能：停止电机 
**************************************************/
void DisableMoter(void)
{
}
