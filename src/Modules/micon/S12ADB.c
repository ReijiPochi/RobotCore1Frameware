/*
 * S12ADB.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "S12ADB.h"
#include "iodefine.h"
#include "vect.h"

_UWORD values[3];
_UWORD values1[4];

void S12AD_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// S12ADユニット0のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;

		// 12ビットA/Dコンバータ制御部モジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA24 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// スキャンモード選択
	S12AD.ADCSR.BIT.ADCS = 0x0;		// 1サイクルスキャンモード

	// A/D変換チャンネル選択
	S12AD.ADANSA.BIT.ANSA = 0x7;	// AN000 ~ AN002 を変換

	// スキャン終了割り込み許可
	S12AD.ADCSR.BIT.ADIE = 1;		// 許可

	// I/Oポート機能を設定
	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.P40PFS.BIT.ASEL = 1;	// アナログ端子として使用
		MPC.P41PFS.BIT.ASEL = 1;	// アナログ端子として使用
		MPC.P42PFS.BIT.ASEL = 1;	// アナログ端子として使用
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	IPR(S12AD,S12ADI) = 0x7;
	IEN(S12AD,S12ADI) = 0x1;
	IR(S12AD,S12ADI) = 0x0;
}

void S12AD_Sample(void)
{
	if(S12AD.ADCSR.BIT.ADST == 0)
	{
		// 変換開始
		S12AD.ADCSR.BIT.ADST = 1;
	}
}

void Excep_S12AD_S12ADI(void)
{
	values[0] = S12AD.ADDR0;
	values[1] = S12AD.ADDR1;
	values[2] = S12AD.ADDR2;

	IR(S12AD,S12ADI) = 0x0;
}

_UWORD S12ADB_GetVoltage(_UBYTE channel)
{
	if(channel > 2)
		return 0.0;

	return values[channel];
}


void S12AD1_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// S12AD1ユニット0のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;

		// 12ビットA/Dコンバータ制御部モジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA24 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// スキャンモード選択
	S12AD1.ADCSR.BIT.ADCS = 0x0;		// 1サイクルスキャンモード

	// A/D変換チャンネル選択
	S12AD1.ADANSA.BIT.ANSA = 0xF;	// AN100 ~ AN103 を変換

	// スキャン終了割り込み許可
	S12AD1.ADCSR.BIT.ADIE = 1;		// 許可

	// I/Oポート機能を設定
	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.P44PFS.BIT.ASEL = 1;	// アナログ端子として使用
		MPC.P45PFS.BIT.ASEL = 1;	// アナログ端子として使用
		MPC.P46PFS.BIT.ASEL = 1;	// アナログ端子として使用
		MPC.P47PFS.BIT.ASEL = 1;	// アナログ端子として使用
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	IPR(S12AD1,S12ADI1) = 0x7;
	IEN(S12AD1,S12ADI1) = 0x1;
	IR(S12AD1,S12ADI1) = 0x0;
}

void S12AD1_Sample(void)
{
	if(S12AD1.ADCSR.BIT.ADST == 0)
	{
		// 変換開始
		S12AD1.ADCSR.BIT.ADST = 1;
	}
}

void Excep_S12AD1_S12ADI1(void)
{
	values1[0] = S12AD1.ADDR0;
	values1[1] = S12AD1.ADDR1;
	values1[2] = S12AD1.ADDR2;
	values1[3] = S12AD1.ADDR3;

	IR(S12AD1,S12ADI1) = 0x0;
}

_UWORD S12AD1_GetVoltage(_UBYTE channel)
{
	if(channel > 3)
		return 0.0;

	return values1[channel];
}
