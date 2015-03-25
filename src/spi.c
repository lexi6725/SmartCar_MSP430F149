/*
 * 文件名: spi.c
 * 作者: Lexi
 * 日期: 2013/03/25
 */
#include "config.h"
#include "spi.h"

void SPIx_Init(void)
{
	P3SEL	= 0x0E;
	U0CTL	= CHAR + SYNC + MM + SWRST;
	U0TCTL	= SSEL1 + STC;
	U0BR0 	= 0x02;
	U0BR1	= 0x00;
	U0MCTL	= 0x00;
}

uchar SPIx_ReadWriteByte(uchar TxData)
{
	return 0;
}

void SPI_RXD_ISR(void)
{
}

void SPI_TXD_ISR(void)
{
}
