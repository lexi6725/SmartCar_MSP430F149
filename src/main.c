/*
 * File Name: main.c
 * Author: Lexi
 * Date: 2013/03/13
 */

#include "config.h"
#include "System.h"

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
 * 参数： None
 * 返回值：None
 * 功能：主程序入口
 ****************************************************/
int main( void )
{
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	
	Delay(0xFF0);
	
	System_Init();
	
	while(1)
	{
	}
	
}
 