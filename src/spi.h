/*
 * 文件名: spi.h
 * 作者: Lexi
 * 日期: 2013/03/25
 */

#ifndef __SPI_H__
#define __SPI_H__

#define	CE	BIT0
#define CSN	BIT4

#define SPI_TXD_EN()	ME1 |= USPIE0; IE1 |= UTXIE0;
#define SPI_TXD_DIS()	ME1 &= ~USPIE0; IE1 &= ~UTXIE0;

#define SPI_RXD_EN()	ME1 |= USPIE0; IE1 |= URXIE0;
#define SPI_RXD_DIS()	ME1 &= ~USPIE0; IE1 &= ~URXIE0;

#define SPI_RST()		U0CTL &= ~SWRST;

extern uchar SPI_Flag;
#define RECEIVED	0x1
#define	TRANSMIT	0x02

extern void SPI_RXD_ISR(void);

#endif