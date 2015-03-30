/*
* 文件名：Irda.c
* 作者：lexi
* 日期：2015/03/30
*/

#include "config.h"
#include "Irda.h"
uchar Irda_Time=0;

void Init_Irda(void)
{
	P1DIR	&= ~IRDA;
	P1IE	|= IRDA;
}

void IRDA_ISR(void)
{
	
	//if (Irda_Time<63)
}
