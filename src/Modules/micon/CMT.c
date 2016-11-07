/*
 * CMT.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "CMT.h"
#include "iodefine.h"
#include "..\..\typedefine.h"
#include "vect.h"

void (*callback1)(void);
void (*callback2)(void);
void (*callback3)(void);

void CMT_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// CMTユニット0のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;

		// CMTユニット1のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA14 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;
}

void CMT0_Set(_UBYTE clockSource, _UWORD CMCOR, void (*callback)(void))
{
	// コンペアマッチ値設定
	CMT0.CMCOR = CMCOR;

	// クロックの分周を設定
	CMT0.CMCR.BIT.CKS = clockSource;

	// コンペアマッチ割り込みを許可
	CMT0.CMCR.BIT.CMIE = 1;

	callback1 = callback;

	IPR(CMT0,CMI0) = 0x7;
	IEN(CMT0,CMI0) = 0x1;
	IR(CMT0,CMI0) = 0x0;
}

void CMT0_Start(void)
{
	CMT.CMSTR0.BIT.STR0 = 1;
}

void Excep_CMT0_CMI0(void)
{
	callback1();
	IR(CMT0,CMI0) = 0x0;
}

void CMT0_Stop(void)
{
	CMT.CMSTR0.BIT.STR0 = 0;
}


void CMT1_Set(_UBYTE clockSource, _UWORD CMCOR, void (*callback)(void))
{
	// コンペアマッチ値設定
	CMT1.CMCOR = CMCOR;

	// クロックの分周を設定
	CMT1.CMCR.BIT.CKS = clockSource;

	// コンペアマッチ割り込みを許可
	CMT1.CMCR.BIT.CMIE = 1;

	callback2 = callback;

	IPR(CMT1,CMI1) = 0x8;
	IEN(CMT1,CMI1) = 0x1;
	IR(CMT1,CMI1) = 0x0;
}

void CMT1_Start(void)
{
	CMT.CMSTR0.BIT.STR1 = 1;
}

void Excep_CMT1_CMI1(void)
{
	callback2();
	IR(CMT1,CMI1) = 0x0;
}

void CMT1_Stop(void)
{
	CMT.CMSTR0.BIT.STR1 = 0;
}

void CMT2_Set(_UBYTE clockSource, _UWORD CMCOR, void (*callback)(void))
{
	// コンペアマッチ値設定
	CMT2.CMCOR = CMCOR;

	// クロックの分周を設定
	CMT2.CMCR.BIT.CKS = clockSource;

	// コンペアマッチ割り込みを許可
	CMT2.CMCR.BIT.CMIE = 1;

	callback3 = callback;

	IPR(CMT2,CMI2) = 0x8;
	IEN(CMT2,CMI2) = 0x1;
	IR(CMT2,CMI2) = 0x0;
}

void CMT2_Start(void)
{
	CMT.CMSTR1.BIT.STR2 = 1;
}

void Excep_CMT2_CMI2(void)
{
	callback3();
	IR(CMT2,CMI2) = 0x0;
}

void CMT2_Stop(void)
{
	CMT.CMSTR1.BIT.STR2 = 0;
}
