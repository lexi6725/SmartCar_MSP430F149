/*
 * 文件名: spi.h
 * 作者: Lexi
 * 日期: 2013/03/25
 */

#ifndef __SPI_H__
#define __SPI_H__

#define SPI_TXD_EN()	ME1 |= USPIE0; IE1 |= UTXIE0;
#define SPI_TXD_DIS()	ME1 &= ~USPIE0; IE1 &= ~UTXIE0;

#define SPI_RXD_EN()	ME1 |= USPIE0; IE1 |= URXIE0;
#define SPI_RXD_DIS()	ME1 &= ~USPIE0; IE1 &= ~URXIE0;

#define SPI_RST()		U0CTL &= ~SWRST;

#define SPI_SCK_OUT()	(P5DIR	|= BIT3)
#define SPI_SCK_FUN()	(P5SEL	|= BIT3)
#define SPI_MOSI_OUT()	(P5DIR	|= BIT1)
#define SPI_MOSI_FUN()	(P5SEL	|= BIT1)
#define SPI_MISO_IN()	(P5DIR	&= ~BIT2)
#define SPI_MISO_FUN()	(P5SEL	|= BIT2)

extern uchar SPI_Flag;
#define RECEIVED	0x1
#define	TRANSMIT	0x02

extern void SPIx_Init(void);
extern void SPI_RXD_ISR(void);
extern uchar SPIx_RW_Byte(uchar Byte);

#endif