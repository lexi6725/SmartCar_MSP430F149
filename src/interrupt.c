/*
 * File Name: interrupt.c
 * Author: Lexi
 * Date: 2015/03/11
 */

/*
 * �жϷ��������
*/
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "spi.h"
#include "irda.h"

/****************************************************
 * ISR_Timer_B0
 * ������ None
 * ����ֵ��None
 * ���ܣ�TimerB0�жϷ������
 ****************************************************/
#pragma vector=TIMERB0_VECTOR
__interrupt void ISR_Timer_B0(void)
{
	TimerB0_ISR();
}

/****************************************************
 * ��������ISR_Timer_B1
 * ������ None
 * ����ֵ��None
 * ���ܣ�TimerB1�жϷ������
 ****************************************************/
#pragma vector=TIMERB1_VECTOR
__interrupt void ISR_Timer_B1(void)
{
	if (TBIV&0x08)
	{
		IRDA_TIMER_ISR();
	}
}

#pragma vector=UART0RX_VECTOR
__interrupt void ISR_SPI0(void)
{
	SPI_RXD_ISR();
}

#pragma vector=PORT1_VECTOR
__interrupt void ISR_IRDA(void)
{
	if (CHECK_IRDA())
	{
		IRDA_ISR();
		CLR_IRDA_FLG();
	}
}