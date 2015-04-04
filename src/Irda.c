/*
* 文件名：Irda.c
* 作者：lexi
* 日期：2015/03/30
*/

#include "config.h"
#include "Irda.h"
#include "Timer.h"
#include "motor.h"
#include "System.h"

uchar Irda_Flag;
uchar Irda_Time;
uchar Irda_Data[33];
uchar Irda_Code[4];
static struct Timer *timer;

void Init_Irda_Timer(void)
{
	if ((timer = GetEmptyTimePoint(TIMER_TYPE_US)) != NULL)
	{
		timer->flag = TIMER_STOP;
		timer->period = 128;
		timer->timer_isr = IRDA_TIMER_ISR;
		timer->chksum = CalCheckSum((uchar *)timer, sizeof(struct Timer)-1);
	}
}

void Init_Irda(void)
{
	P1DIR	&= ~IRDA;		// 输入方向
	P1IES	|= IRDA;		// 下降沿触发中断
	ENABLE_IRDA();			// 打开中断

	Init_Irda_Timer();
	Irda_Time = 0;
	Irda_Flag = 0;
}

void Irda_Data_Explain(void)
{
	unsigned char byte, bit, index;
	unsigned char cord, value;

	if (!(Irda_Flag&(IRDA_RECV|IRDA_OK)))
		return;

	for (byte = 0; byte < 4; ++byte) {
		for (bit = 0; bit < 8; ++bit) {
			cord	= Irda_Data[index];
			value	= value>>1;
			if (cord>7)
				value	|= 0x80;
			index++;
		}
		Irda_Code[byte] = value;
		value = 0;
	}
	Irda_Flag	&= ~IRDA_RECV;

	if (Irda_Code[0] == ~Irda_Code[1] && Irda_Code[2] == ~Irda_Code[3])
		Irda_Flag	|= IRDA_OK;
}

void Irda_Process(void)
{
	Irda_Data_Explain();
	
	if (!(Irda_Flag&IRDA_OK))
		return;

	switch(Irda_Code[2])
	{
		case DIGIT_4:
			SetMotorDirs(dirLEFT);
			SyncMotorRate(dirLEFT);
			break;
		case DIGIT_1:
		case DIGIT_2:
		case DIGIT_3:
			SetMotorDirs(dirLEFT);
			SyncMotorRate(dirLEFT);
			break;
		case DIGIT_7:
		case DIGIT_8:
		case DIGIT_9:
			SetMotorDirs(dirBACK);
			SyncMotorRate(dirBACK);
			break;
		case DIGIT_6:
			SetMotorDirs(dirRIGHT);
			SyncMotorRate(dirRIGHT);
			break;
		case DIGIT_5:
			SetMotorDirs(dirDEBOOST);
			SyncMotorRate(dirDEBOOST);
			break;
		default:
			break;
	}
	
	Irda_Flag	&= ~IRDA_OK;
}

void IRDA_ISR(void)
{
	static unsigned char index;

	if (!Irda_Flag&(IRDA_RECV|IRDA_OK))
		return;

	if (!(Irda_Flag & IRDA_START_TIMER))
	{
		if ((timer == NULL))
		{
			Init_Irda_Timer();
		}
		StartTimer(timer);
		Irda_Flag |= IRDA_START_TIMER;
		return;
	}
	
	if (Irda_Time<63&&Irda_Time>33)
	{
		index = 0;
	}
	Irda_Data[index] = Irda_Time;
	Irda_Time = 0;
	if(++index==33)
	{
		StopTimer(timer);
		Irda_Flag	|= IRDA_RECV;
		index = 0;
	}
}

void IRDA_TIMER_ISR(void)
{
	Irda_Time++;
	
}
