/*
 * File Name: nRF24L01.c
 * Author: Lexi
 * Date: 2015/03/10
 */
// http://www.tuicool.com/articles/Mnyea2

#include "config.h"
#include "nRF24L01.h"
#ifdef MODULE_NRF24L01

void Init_NRF24L01(void)
{
	P3OUT	&= ~CE;
	P3OUT	|= CSN;
	SPIx_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	SPIx_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
	SPIx_RW_Reg(WRITE_REG + EN_AA, 0x00);
	SPIx_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);
	SPIx_RW_Reg(WRITE_REG + SETUP_RETR, 0x00);
	SPIx_RW_Reg(WRITE_REG + RF_CH, 40);
	SPIx_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
	SPIx_RW_Reg(WRITE_REG + RF_SETUP, 0x07);
	SPIx_RW_Reg(WRITE_REG + CONFIG, 0x0E);
}

void SetRx_Mode(void)
{
	P3OUT	&= ~CE;
	SPIx_RW_Reg(WRITE_REG + CONFIG, 0x0F);
	P3OUT	|= CE;
	Delay_us(330);
}

uchar nRF24L01_RxPacket(uchar *rx_buf)
{
	uchar revale = 0;
	uchar status = SPIx_Read(STATUS);
	if (status & 0x40)
	{
		P3OUT	&= ~CE;
		SPIx_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);
		revale = 1;
	}
	SPIx_RW_Reg(WRITE_REG + STATUS, status);
	return revale;
}

void nRF24L01_TxPacket(uchar *tx_buf)
{
	P3OUT	&= ~CE;
	SPIx_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
	SPIx_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);
	P3OUT	|= CE;
	Delay_us(40);
}

void RX_Mode(void)
{
	P3OUT	&= ~CE;
	SPIx_RW_Reg(WRITE_REG + CONFIG, 0x0f);
	SPIx_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
	SPIx_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);
	SPIx_RW_Reg(WRITE_REG + RF_CH, 40);
	SPIx_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
	SPIx_RW_Reg(WRITE_REG + RF_SETUP, 0x07);
	P3OUT	|= CE;
}

void TX_Mode(void)
{
}

#endif