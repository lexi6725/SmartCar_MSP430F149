/*
 * 文件名: spi.c
 * 作者: Lexi
 * 日期: 2013/03/25
 */
#include "config.h"
#include "spi.h"

uchar SPI_Flag;
uchar Rtx_Buf[2];
uchar Rtx_ctrl;

void SPIx_Init(void)
{
	P3SEL	= 0x0E;
	U0CTL	= CHAR + SYNC + MM + SWRST;
	U0TCTL	= SSEL1 + STC;
	U0BR0 	= 0x02;
	U0BR1	= 0x00;
	U0MCTL	= 0x00;
}

uchar SPIx_RW(uchar Byte)
{
	SPI_Flag	&= ~RECEIVED;
	
	TXBUF_0 = Byte;
	
	while(!SPI_Flag&RECEIVED)
		LPM0;
	
	return Rtx_Buf[0];
}

uchar SPIx_RW_Reg(uchar reg, uchar value)
{
	uchar status;
	P3OUT	&= ~CSN;
	status = SPIx_RW(reg);
	SPIx_RW(value);
	P3OUT	|= CSN;
	
	return status;
}

uchar SPIx_Read(uchar reg)
{
	uchar reg_val;
	P3OUT	&= ~CSN;
	SPIx_RW(reg);
	reg_val = SPIx_RW(0);
	P3OUT	|= CSN;
	
	return reg_val;
}

uchar SPIx_Read_Buf(uchar reg, uchar *pBuf, uchar bytes)
{
	uchar status, byte_ctrl;
	
	P3OUT	&= ~CSN;
	status = SPIx_RW(reg);
	for (byte_ctrl = 0; byte_ctrl < bytes; ++byte_ctrl)
		pBuf[byte_ctrl] = SPIx_RW(0);
	P3OUT	|= CSN;
	
	return status;
}

uchar SPIx_Write_Buf(uchar reg, uchar *pBuf, uchar bytes)
{
	uchar status, byte_ctrl;
	
	P3OUT	&= ~CSN;
	status	= SPIx_RW(reg);
	for (byte_ctrl = 0; byte_ctrl < bytes; ++byte_ctrl)
		SPIx_RW(*pBuf++);
	P3OUT	|= CSN;
	
	return status;
}

void SPI_RXD_ISR(void)
{
	Rtx_Buf[0] = RXBUF_0;
	SPI_Flag	|= RECEIVED;
}



