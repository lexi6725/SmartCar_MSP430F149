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
	SPI_MISO_FUN();
	SPI_MOSI_FUN();
	SPI_SCK_FUN();
	
	U1CTL	= CHAR + SYNC + MM + SWRST;
	U1TCTL	= CKPL + SSEL1 + STC;
	U1BR0 	= 0x02;
	U1BR1	= 0x00;
	U1MCTL	= 0x00;
	ME2		|= USPIE1;
	U1CTL	&= ~SWRST;
	IE2		|= URXIE1;

}

uchar SPIx_RW_Byte(uchar Byte)
{
	uchar retry = 0;
	SPI_Flag	&= ~RECEIVED;
	
	TXBUF_1 = Byte;
	
	while(!SPI_Flag&RECEIVED)
	{
		if (retry++>200)
			return 0;
	}
	
	return RXBUF_1;
}

void SPI_RXD_ISR(void)
{
	Rtx_Buf[0]	= RXBUF_1;
	SPI_Flag	|= RECEIVED;
}
