/*
* �ļ�����Irda.h
* ���ߣ�lexi
* ���ڣ�2015/03/30
*/

#ifndef __IRDA_H__
#define __IRDA_H__

#define IRDA	BIT5
#define CHECK_IRDA()	(P1IN&IRDA);

extern uchar Irda_Time;

#endif