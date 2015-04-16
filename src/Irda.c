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
uchar Irda_Code[4];
uchar Irda_Code_Log[4];
uchar dat_ind = 0;
uchar bit_ind = 0;
static struct Timer *timer;

void Init_Irda_Timer(void)
{
	if ((timer = GetEmptyTimePoint(TIMER_TYPE_US)) != NULL)
	{
		timer->flag = TIMER_STOP;
		timer->period = 1;
		timer->timer_isr = IRDA_TIMER_ISR;
	}
}

void Init_Irda(void)
{
	P1DIR	&= ~IRDA;		// 输入方向
	//P1IES	|= IRDA;		// 下降沿触发中断
	//ENABLE_IRDA();			// 打开中断

	Init_Irda_Timer();
	StartTimer(timer);
	Irda_Time = 0;
	Irda_Flag = 0;
}

void Irda_Data_Explain(void)
{
	/*unsigned char byte, bit, index;
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
	Irda_Flag	&= ~IRDA_RECV;*/

	if (Irda_Code_Log[0] == ~Irda_Code_Log[1] && Irda_Code_Log[2] == ~Irda_Code_Log[3])
		Irda_Flag	|= IRDA_COMMUNICATING;
}

void Irda_Process(void)
{
	Irda_Data_Explain();
	
	if (!(Irda_Flag&IRDA_COMMUNICATING))
		return;

	switch(Irda_Code_Log[2])
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

	memset(Irda_Code_Log, 0x00, 4);
	
	Irda_Flag	&= ~IRDA_COMMUNICATING;
}

/*void IRDA_ISR(void)
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
}*/

void IRDA_TIMER_ISR(void)
{
	Irda_Time++;

	if (!(Irda_Flag&IRDA_LOW)&&(P1IN & IRDA))
	{
		Irda_Flag	|= IRDA_LOW;
		Irda_Time = 0;
	}
	else if ((Irda_Flag & IRDA_LOW)&&!(P1IN&IRDA))
	{
		if (!(Irda_Flag&IRDA_START)&&(Irda_Time >  HEADERTIME))
		{
			Irda_Flag	|= IRDA_START;
			dat_ind = 0;
			bit_ind = 0;
		}
		else if ((Irda_Flag&IRDA_START)&&(Irda_Time > DATA_HIGH))
		{
			Irda_Code[dat_ind] |= (1<<bit_ind);
			bit_ind++;
			if (bit_ind >= 7)
			{
				dat_ind++;
				bit_ind = 0;
			}
		}
		else if (Irda_Flag&IRDA_START)
		{
			bit_ind++;
		}
		
		Irda_Flag	&= ~IRDA_LOW;
		
		if (dat_ind >= 4)
		{
			StopTimer(timer);
			Irda_Flag |= IRDA_Dat_OK;
			memcpy(Irda_Code_Log, Irda_Code, 4);
			memset(Irda_Code, 0x00, 4);
		}

		Irda_Time = 0;
	}
}
