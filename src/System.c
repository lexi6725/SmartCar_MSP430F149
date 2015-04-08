/*
 * File Name: System.c
 * Author: Lexi
 * Date: 2015/03/11
 */

#include "config.h"
#include "Timer.h"
#include "motor.h"
#include "irda.h"
#include "rtc.h"
#include "HC-SR04.h"
#include "nRF24L01.h"
#include "System.h"
#include "spi.h"

uint SystemFlag = 0;      // ϵͳ��־

/****************************************************
 * ��������Init_clk
 * ������None
 * ����ֵ��None
 * ���ܣ���ʼ��ϵͳʱ��
 ****************************************************/
void Init_clk(void)
{
	uchar i;
	
	BCSCTL1	&= ~XT2OFF;			// ��XT2����
	
	do{
		IFG1 &= ~OFIFG;			// �������������
		for (i = 0xff; i>0; --i);	// ��ʱ�ȴ�
	}while((IFG1&OFIFG) != 0);	// ���������־����������ȏ�	
	
	BCSCTL2	= SELM1 + SELS;	// MCLK and SMCLK Select XT2CLK	8MHz
}

/**********************************************************
 * ��������System_Init
 * ������None
 * ���ܣ���ʼ��ϵͳ
 **********************************************************/
void System_Init(void)
{
	Init_clk();               	// ��ʼ��ϵͳʱ��
	Motor_Init();             	// ��ʼ�����
	TimerB7_Init();           	// ��ʼ����ʱ��TimerB
	TimerA3_Init();           	// ��ʼ����ʱ��TimerA3
	
	Init_Irda();              	// ��ʼ������
	Init_RTC();
	Init_hc_sr04();
	SPIx_Init();
	_EINT();                  	// ʹ�����ж�
	
	ENABLE_TIMERB0();         	// ������ʱ��TimerB0�ж�
	EnableMotor();            	// ʹ�ܵ��            
	SetMotorDirs(dirBACK); 	// ���õ����ʼ����
	//SetMotorRate(MOTOR_ALL, 10);
	Enable_hc_test();

	NRF24L01_Init();
	if (nRF24L01_Check())
	{
		SystemFlag	|= bNRF24L01;
	}
	else
		SystemFlag	&= bNRF24L01;
	
}


uchar CalCheckSum(uchar *pdat, uchar len)
{
	uchar chksum = 0;
	do{
		chksum += pdat[--len];
	}while(len);

	chksum	+= 0x5A;
	return chksum;
}