/*
 * File Name: main.c
 * Author: Lexi
 * Date: 2013/03/13
 */

#include "config.h"
#include "System.h"
#include "motor.h"
#include "Timer.h"
#include "irda.h"
#include "rtc.h"
extern uchar RTC_Flag;

void Delay(unsigned long num)
{
	while (num > 0)
	{
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		num--;
	}
}


/****************************************************
 * 函数名：main
 * 参数＿None
 * 返回值：None
 * 功能：主程序入口
 ****************************************************/
int main( void )
{
	uchar dir[4] = {dirFRONT, dirBACK, dirLEFT, dirRIGHT};
	uchar indDir = 0;
	//uchar second_count = 0;
	//Stop watchdog timer to prevent time out reset 
	WDTCTL = WDTPW + WDTHOLD;
	
	Delay(0xFF0);
	
	System_Init();
	
	while(1)
	{
		if (RTC_Flag&bSecond)
		//if (hc_get_instance() < 10)
		{
			//if (++second_count >= GetRandomNum()%3)
			//{
				if (++indDir >= 4)
					indDir = 0;
				SetMotorDirs(dir[GetRandomNum()%4]);
				SetMotorRate(MOTOR_ALL, GetRandomNum()%MAXRATE);
				//second_count = 0;
			//}
			RTC_Flag	&= ~bSecond;
		}

		//Irda_Process();
		
		//LPM0;
	}
}
 