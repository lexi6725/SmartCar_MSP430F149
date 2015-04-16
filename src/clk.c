/***********************************
* File Name: clk.c
* Author: Lexi
* Date: 2015/04/16
************************************/

#include "config.h"
#include "clk.h"

static const uchar CLK_SHIFT[3] = {ACLK_SHIFT, MCLK_SHIFT, SMCLK_SHIFT};

void Init_Clk(void)
{
	uchar i;
	
	BCSCTL1	&= ~XT2OFF;			// 打开XT2振荡器
	
	do{
		IFG1 &= ~OFIFG;			// 清除振荡器错误标忿
		for (i = 0xff; i>0; --i);	// 延时等待
	}while(IFG1&OFIFG);	// 如果振荡器标志错误，则继续等徿	
	
	BCSCTL2	= SELM_2 + SELS;	// MCLK and SMCLK Select XT2CLK	8MHz
}

void Set_Clk(uchar clk_type, uchar div)
{
	uchar org_cfg;
	
	if (clk_type > SMCLK_TYPE || div > DIV_8)
		return;
	
	if (clk_type>ACLK_TYPE)
	{
		org_cfg = BCSCTL2;
		org_cfg &= ~(0x3<<CLK_SHIFT[clk_type]);
		org_cfg |= (div<<CLK_SHIFT[clk_type]);
		BCSCTL2 = org_cfg;
	}
	else
	{
		org_cfg = BCSCTL1;
		org_cfg &= ~(0x03<<CLK_SHIFT[clk_type]);
		org_cfg	|= (div<<CLK_SHIFT[clk_type]);
		BCSCTL1 = org_cfg;
	}
}
