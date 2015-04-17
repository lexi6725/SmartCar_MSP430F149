/*
 * File Name: nRF24L01.h
 * Author: Lexi
 * Date: 2015/03/10
 */

#ifndef __NRF24L01_H__
#define __NRF24L01_H__

/////////////////////////////////////////////////////////////
// NRF24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH	5		//5�ֽڵķ��͵�ַ���
#define RX_ADR_WIDTH	5		// 5�ֽڵĽ��յ�ַ���
#define TX_PLOAD_WIDTH	32		// 32�ֽڵķ��ͻ��������
#define RX_PLOAD_WIDTH	32		// 32�ֽڵĽ��ջ��������

/**********************************************************
* NRF24L01�Ĵ�����������
***********************************************************/
#define READ_REG			0x00		//�����üĴ�������5λΪ�Ĵ�����ַ
#define WRITE_REG			0x20		//д���üĴ�������5λΪ�Ĵ�����ַ
#define RD_RX_PLOAD			0x61		//��RX��Ч���ݣ�1~32�ֽ�
#define WR_TX_PLOAD			0xA0		//дTX��Ч���ݣ�1~32�ֽ�
#define	FLUSH_TX			0xE1		//���TX_FIFO�Ĵ���������ģʽ����
#define FLUSH_RX			0xE2		//���RX_FIFO�Ĵ���������ģʽ��ʹ��
#define REUSE_TX_PL			0xE3		//����ʹ����һ�����ݣ�CEΪ�ߣ����ݰ�����������
#define	NOP					0xFF		//�ղ���������������״̬�Ĵ���

/**********************************************************
* NRF24L01�Ĵ�����ַ
***********************************************************/
#define CONFIG				0x00		//���üĴ�����ַ��
										//Bit0:1 ����ģʽ 0����ģʽBit1: 1 PowerUp      0 PowerDown
										//Bit2:1 CRC two byte  0 CRC one byte     Bit3: 1 Enable CRC 0 Disable CRC 
										//Bit4: 1 Enabel IRQ 0 DisableIRQ               Bit5: 1 TX_IRQ
										//Bit6: 1 TX_IRQ						  Bit7: Only '0'
#define	EN_AA				0x01		//ʹ���Զ�Ӧ����Bit[0:5]:��Ӧͨ��0~5
#define EN_RXADDR			0x02		//���յ�ַʹ��,Bit[0:5]:��Ӧͨ��0~5
#define SETUP_AW			0x03		//���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define SETUP_RETR			0x04		//�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define RF_CH				0x05		//RFͨ��,bit6:0,����ͨ��Ƶ��;
#define RF_SETUP			0x06		//RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define	STATUS				0x07		//״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
										//bit5:���ݷ�������ж�;bit6:���������ж�;
#define MAX_TX				0x10		//�ﵽ����ʹ����ж�
#define	TX_OK				0x20		//TX��������ж�
#define	RX_OK				0x40		//���յ������ж�

#define OBSERVE_TX			0x08		//���ͼ��Ĵ���,bit7:4,���ݰ���ʧ������;bit3:0,�ط�������
#define CD					0x09		//�ز����Ĵ���,bit0,�ز����;
#define RX_ADDR_P0			0x0A		//����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P1			0x0B		//����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P2			0x0C		//����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define	RX_ADDR_P3			0x0D		//����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define	RX_ADDR_P4			0x0E		//����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define	RX_ADDR_P5			0x0F		//����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define	TX_ADDR				0x10		//���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define	RX_PW_P0			0x11		//��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1			0x12		//��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define	RX_PW_P2			0x13		//��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3			0x14		//��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4			0x15		//��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define	RX_PW_P5			0x16		//��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define	FIFO_STATUS			0x17		//FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
										//bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
/*****************************************************
*������
******************************************************/
#define	nRF24L01_CE_1			(P4OUT	|= BIT4)	//ʹ��NRF24L01Ƭѡ�ź�
#define nRF24L01_CSN_1		(P4OUT	|= BIT5)	// ʹ��SPIƬѡ�ź�
#define nRF24L01_CE_0		(P4OUT	&= ~BIT4)	//ȡ��NRF24L01Ƭѡ�ź�
#define nRF24L01_CSN_0		(P4OUT	&= ~BIT5)	//ȡ��SPIƬѡ�ź�
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
//ʹ������Ӧͨ����Ĭ��5ͨ��ȫ��
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