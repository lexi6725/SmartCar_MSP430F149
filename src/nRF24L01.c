/*
 * File Name: nRF24L01.c
 * Author: Lexi
 * Date: 2015/03/10
 */
// http://www.tuicool.com/articles/Mnyea2

#include "config.h"
#include "nRF24L01.h"
//#include "spi.h"
#ifdef MODULE_NRF24L01

uchar nRF24L01_Status = 0;
uchar TestBuf = 0;

uchar TX_ADDRESS[TX_ADR_WIDTH] = {0x59, 0x42, 0x67, 0x67, 0x92};
uchar RX_ADDRESS[RX_ADR_WIDTH] = {0x59, 0x42, 0x67, 0x67, 0x92};

void delay_1ms(unsigned int i)
{
	unsigned long j;
	for(;i>0;i--)
	{
		for(j=0;j<730;j++);//8M--->1ms
	}
}


void nRF24L01_IO_set(void)
{
      P4DIR |= BIT4;         //ce
      P4DIR |= BIT5;         //csn
      P5DIR |= BIT3;         //sck
      P5DIR |= BIT2;         //mosi out
      P5DIR &=~BIT1;         //MISO IN 
      P1DIR &=~BIT4;         //IRQ
      
      nRF24L01_SCK_0;
      nRF24L01_CE_0;
}

void MOSI_Pin(BYTE state)
{
	if (state)
		nRF24L01_MOSI_1;
	else
		nRF24L01_MOSI_0;
}
BYTE MISO_Pin(void)
{
	return nRF24L01_MISO_IN;
}

uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;

	for (bit_ctr = 0; bit_ctr<8; bit_ctr++)
	{
		MOSI_Pin(byte&0x80);
		byte = (byte<<1);
		nRF24L01_SCK_1;
		byte	|= MISO_Pin();
		nRF24L01_SCK_0;
	}
	return byte;
}

uchar nRF24L01_RW_Reg(uchar reg, uchar value)
{
	uchar status;
	nRF24L01_CSN_0;
	status = SPI_RW(reg);
	SPI_RW(value);
	nRF24L01_CSN_1;

	return status;
}

uchar nRF24L01_Read_Byte(uchar reg)
{
	uchar ret_value;
	nRF24L01_CSN_0;
	SPI_RW(reg);
	ret_value = SPI_RW(0);
	nRF24L01_CSN_1;

	return ret_value;
}

uchar nRF24L01_Read_Buf(uchar reg, uchar *pBuf, uchar len)
{
	uchar status, byte_ctr;

	nRF24L01_CSN_0;
	status = SPI_RW(reg);

	for (byte_ctr = 0; byte_ctr<len; byte_ctr++)
		pBuf[byte_ctr] = SPI_RW(0);

	nRF24L01_CSN_1;

	return status;
}

uchar nRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar len)
{
	uchar status, byte_ctr;

	nRF24L01_CSN_0;
	status = SPI_RW(reg);
	for(byte_ctr = 0; byte_ctr<len; ++byte_ctr)
		SPI_RW(*pBuf++);
	nRF24L01_CSN_1;
	
	return status;
}

void RX_Mode(void)
{
	nRF24L01_CE_0;
	nRF24L01_Write_Buf(WRITE_REG+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	nRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0, RX_ADDRESS,RX_ADR_WIDTH);
	nRF24L01_RW_Reg(WRITE_REG+EN_AA, ENAA_DisableALL);
	nRF24L01_RW_Reg(WRITE_REG+SETUP_RETR,AutoReTxTimes_3);
	nRF24L01_RW_Reg(WRITE_REG+EN_RXADDR, 0x01);
	nRF24L01_RW_Reg(WRITE_REG+RF_CH, 0);
	nRF24L01_RW_Reg(WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);
	nRF24L01_RW_Reg(WRITE_REG+RF_SETUP, 0x27);
	nRF24L01_RW_Reg(WRITE_REG+CONFIG, 0x0F);
	nRF24L01_CE_1;
}

void TX_Mode(void)
{
	nRF24L01_CE_0;

	nRF24L01_Write_Buf(WRITE_REG+TX_ADDR,TX_ADDRESS, TX_ADR_WIDTH);
	nRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
	nRF24L01_RW_Reg(WRITE_REG+EN_AA, ENAA_DisableALL);
	nRF24L01_RW_Reg(WRITE_REG+SETUP_RETR, AutoReTxTimes_3);
	nRF24L01_RW_Reg(WRITE_REG+EN_RXADDR, 0x01);
	nRF24L01_RW_Reg(WRITE_REG+RF_CH, 0);
	nRF24L01_RW_Reg(WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);
	nRF24L01_RW_Reg(WRITE_REG+RF_SETUP, 0x27);
	nRF24L01_RW_Reg(WRITE_REG+CONFIG, 0x0E);
	nRF24L01_CE_1;
}

uchar nRF24L01_Tx_Package(uchar *pbuf, uchar len)
{
	return nRF24L01_Write_Buf(WR_TX_PLOAD, pbuf, len);
}

uchar nRF24L01_Rx_Package(uchar *pbuf, uchar len)
{
	if (len > RX_ADR_WIDTH)
		return 0;

	nRF24L01_Status = nRF24L01_Read_Byte(STATUS);
	nRF24L01_RW_Reg(WRITE_REG+STATUS,nRF24L01_Status);
	if (nRF24L01_Status&RX_OK)
	{
		nRF24L01_Read_Buf(RD_RX_PLOAD, pbuf, len);
		nRF24L01_RW_Reg(FLUSH_RX, 0xff);
	}

	return nRF24L01_Status;
}

uchar nRF24L01_Check(void)
{
	uchar buf[TX_ADR_WIDTH];

	nRF24L01_Write_Buf(WRITE_REG+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	nRF24L01_Read_Buf(TX_ADDR, buf, TX_ADR_WIDTH);

	if (memcmp(TX_ADDRESS, buf, TX_ADR_WIDTH))
		return 0;
	else
		return 1;
}

/*
* nRF24L01≥ı ºªØ
*/
void NRF24L01_Init(uchar Mode)
{
	TestBuf = nRF24L01_Read_Byte(RX_ADDR_P4);	//return is 0xC5,if connection is ok

	if (Mode == nRF_TX_Mode)
		TX_Mode();
	else
		RX_Mode();
	delay_1ms(2);
}
#endif
