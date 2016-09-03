/*
 * DAa.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "DAa.h"
#include "iodefine.h"

void DAa_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// D/Aユニット0のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA19 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// I/Oポート機能を設定
	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.P54PFS.BIT.ASEL = 1;	// アナログ端子として使用
		MPC.P55PFS.BIT.ASEL = 1;	// アナログ端子として使用
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	// D/A許可
	DA.DACR.BIT.DAE = 1;
}

void DA0_SetValue(_UWORD value)
{
	DA.DADR0 = value;
}

void DA1_SetValue(_UWORD value)
{
	DA.DADR1 = value;
}
