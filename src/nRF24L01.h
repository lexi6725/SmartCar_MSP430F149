/*
 * File Name: nRF24L01.h
 * Author: Lexi
 * Date: 2015/03/10
 */

#ifndef __NRF24L01_H__
#define __NRF24L01_H__

/////////////////////////////////////////////////////////////
// NRF24L01发送接收数据宽度定义
#define TX_ADR_WIDTH	5		//5字节的发送地址宽度
#define RX_ADR_WIDTH	5		// 5字节的接收地址宽度
#define TX_PLOAD_WIDTH	32		// 32字节的发送缓冲区宽度
#define RX_PLOAD_WIDTH	32		// 32字节的接收缓冲区宽度

/**********************************************************
* NRF24L01寄存器操作命令
***********************************************************/
#define READ_REG			0x00		//读配置寄存器，低5位为寄存器地址
#define WRITE_REG			0x20		//写配置寄存器，低5位为寄存器地址
#define RD_RX_PLOAD			0x61		//读RX有效数据，1~32字节
#define WR_TX_PLOAD			0xA0		//写TX有效数据，1~32字节
#define	FLUSH_TX			0xE1		//清除TX_FIFO寄存器，发射模式下用
#define FLUSH_RX			0xE2		//清除RX_FIFO寄存器，接收模式下使用
#define REUSE_TX_PL			0xE3		//重新使用上一包数据，CE为高，数据包被连续发送
#define	NOP					0xFF		//空操作，可以用来读状态寄存器

/**********************************************************
* NRF24L01寄存器地址
***********************************************************/
#define CONFIG				0x00		//配置寄存器地址；
										//Bit0:1 接收模式 0发送模式Bit1: 1 PowerUp      0 PowerDown
										//Bit2:1 CRC two byte  0 CRC one byte     Bit3: 1 Enable CRC 0 Disable CRC 
										//Bit4: 1 Enabel IRQ 0 DisableIRQ               Bit5: 1 TX_IRQ
										//Bit6: 1 TX_IRQ						  Bit7: Only '0'
#define	EN_AA				0x01		//使能自动应答功能Bit[0:5]:对应通道0~5
#define EN_RXADDR			0x02		//接收地址使能,Bit[0:5]:对应通道0~5
#define SETUP_AW			0x03		//设置地址宽度(所有数据通道):bit1,0:00,3字节;01,4字节;02,5字节;
#define SETUP_RETR			0x04		//建立自动重发;bit3:0,自动重发计数器;bit7:4,自动重发延时 250*x+86us
#define RF_CH				0x05		//RF通道,bit6:0,工作通道频率;
#define RF_SETUP			0x06		//RF寄存器;bit3:传输速率(0:1Mbps,1:2Mbps);bit2:1,发射功率;bit0:低噪声放大器增益
#define	STATUS				0x07		//状态寄存器;bit0:TX FIFO满标志;bit3:1,接收数据通道号(最大:6);bit4,达到最多次重发
										//bit5:数据发送完成中断;bit6:接收数据中断;
#define MAX_TX				0x10		//达到最大发送次数中断
#define	TX_OK				0x20		//TX发送完成中断
#define	RX_OK				0x40		//接收到数据中断

#define OBSERVE_TX			0x08		//发送检测寄存器,bit7:4,数据包丢失计数器;bit3:0,重发计数器
#define CD					0x09		//载波检测寄存器,bit0,载波检测;
#define RX_ADDR_P0			0x0A		//数据通道0接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P1			0x0B		//数据通道1接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P2			0x0C		//数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define	RX_ADDR_P3			0x0D		//数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define	RX_ADDR_P4			0x0E		//数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define	RX_ADDR_P5			0x0F		//数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define	TX_ADDR				0x10		//发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define	RX_PW_P0			0x11		//接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P1			0x12		//接收数据通道1有效数据宽度(1~32字节),设置为0则非法
#define	RX_PW_P2			0x13		//接收数据通道2有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P3			0x14		//接收数据通道3有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P4			0x15		//接收数据通道4有效数据宽度(1~32字节),设置为0则非法
#define	RX_PW_P5			0x16		//接收数据通道5有效数据宽度(1~32字节),设置为0则非法
#define	FIFO_STATUS			0x17		//FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留
										//bit4,TX FIFO空标志;bit5,TX FIFO满标志;bit6,1,循环发送上一数据包.0,不循环;
/*****************************************************
*操作线
******************************************************/
#define	nRF24L01_CE_1			(P4OUT	|= BIT4)	//使能NRF24L01片选信号
#define nRF24L01_CSN_1		(P4OUT	|= BIT5)	// 使能SPI片选信号
#define nRF24L01_CE_0		(P4OUT	&= ~BIT4)	//取消NRF24L01片选信号
#define nRF24L01_CSN_0		(P4OUT	&= ~BIT5)	//取消SPI片选信号
#define nRF24L01_SCK_0		(P5OUT	&= ~BIT3)
#define nRF24L01_SCK_1		(P5OUT	|= BIT3)
#define nRF24L01_MOSI_0		(P5OUT	&= ~BIT2)
#define nRF24L01_MOSI_1		(P5OUT	|= BIT2)
#define nRF24L01_MISO_IN	((P5IN>>1)&0x01)

#define nRF24L01_CE_OUT()	(P4DIR	|= BIT4)
#define nRF24L01_CSN_OUT()	(P4DIR	|= BIT5)
#define nRF24L01_IRQ_IN()	(P1DIR	&= ~BIT4)	
#define nRF24L01_SCK_OUT()	(P5DIR	|= BIT3)
#define nRF24L01_MOSI_OUT() (P5DIR	|= BIT2)
#define nRF24L01_MISO_OUT()	(P5DIR	&= ~BIT1)

///===============REG setting data===============
//===0x00 CONFIG===============
#define MASK_RX_DR	0x40
#define MASK_TX_DS	0x20
#define MASK_MAX_RT	0x10
#define EN_CRC		0x08
#define CRCO			0x04	// 0---1byte,1---2byte
#define PWR_UP		0x02		// 1---power up,0---power down
#define PRIM_RX		0x01		// 1---RX mode,0---TX mode

//===0x01 EN_AA================
//使能自响应通道，默认5通道全开
#define ENAA_P5		0x20
#define ENAA_P4		0x10
#define ENAA_P3		0x08
#define ENAA_P2		0x04
#define ENAA_P1		0x02
#define ENAA_P0		0x01
#define ENAA_DisableALL	0x00

//===0x02 EN_RXADDR============
#define ERX_P5		0x20
#define ERX_P4		0x10
#define ERX_P3		0x08
#define ERX_P2		0x04
#define ERX_P1		0x02
#define ERX_P0		0x01
#define ERX_None		0x00
//===0x03 SETUP_AW=============
#define AW_3Bytes		0x01
#define AW_4Bytes		0x02
#define AW_5Bytes		0x03
//===0x04 SETUP_RETR============
#define AutoReTxDalay_250uS		0x00//default
#define AutoReTxDalay_500uS		0x10
#define AutoReTxDalay_750uS		0x20
#define AutoReTxDalay_1000uS	0x30
#define AutoReTxDalay_1250uS	0x40
#define AutoReTxDalay_1500uS	0x50
#define AutoReTxDalay_1750uS	0x60
#define AutoReTxDalay_2000uS	0x70
#define AutoReTxDalay_2250uS	0x80
#define AutoReTxDalay_2500uS	0x90
#define AutoReTxDalay_2750uS	0xA0
#define AutoReTxDalay_3000uS	0xB0
#define AutoReTxDalay_3250uS	0xC0
#define AutoReTxDalay_3500uS	0xD0
#define AutoReTxDalay_3750uS	0xE0
#define AutoReTxDalay_4000uS	0xF0
#define AutoReTx_Disable		0x00
#define AutoReTxTimes_1			0x01
#define AutoReTxTimes_2			0x02
#define AutoReTxTimes_3			0x03//default
#define AutoReTxTimes_4			0x04
#define AutoReTxTimes_5			0x05
#define AutoReTxTimes_6			0x06
#define AutoReTxTimes_7			0x07
#define AutoReTxTimes_8			0x08
#define AutoReTxTimes_9			0x09
#define AutoReTxTimes_10		0x0A
#define AutoReTxTimes_11		0x0B
#define AutoReTxTimes_12		0x0C
#define AutoReTxTimes_13		0x0D
#define AutoReTxTimes_14		0x0E
#define AutoReTxTimes_15		0x0F
//===0x06 RF_SETUP============
#define RF_DR_1Mbps			0x00
#define RF_DR_2Mbps			0x08

#define nRF_TX_Mode		0x00
#define nRF_RX_Mode		0x01

#define RF_IRQ_IS()		(P1IFG&BIT4)


// Communicate Define
#define HEAD1		0x00
#define ADDR		HEAD1+1
#define ALEN		0x02
#define HEAD2		ADDR+ALEN
#define CMD			HEAD2+1
#define DLEN		CMD+1
#define D_ID		DLEN+1
#define DATA		D_ID+1

extern void nRF24L01_IO_set(void);
extern void NRF24L01_Init(uchar Mode);
extern uchar nRF24L01_Check(void);
extern void RX_Mode(void);
extern void TX_Mode(void);
//extern uchar nRF24L01_Tx_Package(uchar *pbuf, uchar len);
//extern uchar nRF24L01_Rx_Package(uchar *pbuf, uchar len);
extern void nRF24L01_ISR(void);
extern void nRF24L01_Comm_Process(void);
#endif