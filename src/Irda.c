/*
* 文件名：Irda.c
* 作者：lexi
* 日期：2015/03/30
*/

#include "config.h"
#include "Irda.h"
#include "Timer.h"
#include "motor.h"

uchar Irda_Flag;
uchar Irda_Time;
uchar Irda_Data[33];
uchar Irda_Code[4];

void Init_Irda(void)
{
	P1DIR	&= ~IRDA;
	P1IE	|= IRDA;
	ENABLE_IRDA();

	SetTimerBRate(IRDA_TIMERB, 2);
	ENABLE_TIMERB4();
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
		case LEFT_ROTATE:
			SetMotorDirs(dirLEFT);
			break;
		case LEFT_FORWARD:
		case FORWARD_ROTATE:
		case RIGHT_FORWARD:
			SetMotorDirs(dirFORWARD);
			break;
		case LEFT_ROLLBACK:
		case ROLLBACK_ROTATE:
		case RIGHT_ROLLBACK:
			SetMotorDirs(dirROLLBACK);
			break;
		case RIGHT_ROTATE:
			SetMotorDirs(dirRIGHT);
			break;
		default:
			break;
	}
	SyncMotorRate(Irda_Code[2]);
	Irda_Flag	&= ~IRDA_OK;
}

void IRDA_ISR(void)
{
	static unsigned char index;

	if (!Irda_Flag&(IRDA_RECV|IRDA_OK))
		return;
	
	if (Irda_Time<63&&Irda_Time>33)
		index = 0;
	Irda_Data[index] = Irda_Time;
	Irda_Time = 0;
	if(++index==33)
	{
		Irda_Flag	|= IRDA_RECV;
		index = 0;
	}
}

void IRDA_TIMER_ISR(void)
{
	Irda_Time++;
	SetIrdaPeriod((GetTimerBRate(IRDA_TIMERB)+IRDA_TIMER_PERIOD)%GetTimerBRate(TIMERB0));
}
