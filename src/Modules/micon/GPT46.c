/*
 * GPT46.c
 *
 *  Created on: 2016/09/03
 *      Author: Matsutomo2
 */


#include "GPT46.h"
#include "iodefine.h"
#include "..\..\typedefine.h"

#define TIMER_FQ	(3125000)

void GPT46_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// GPTユニット1のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA6 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// カウント停止
	GPTB.GTSTR.BIT.CST4 = 0;
	GPTB.GTSTR.BIT.CST6 = 0;

	// 動作モード設定
	GPT4.GTCR.BIT.MD = 0;			// のこぎり波ＰＷＭモード
	GPT6.GTCR.BIT.MD = 0;

	// カウント方向設定
	GPT4.GTUDC.BIT.UDF = 1;			// カウント方向強制設定する
	{
		GPT4.GTUDC.BIT.UD = 1;		// アップカウント
	}
	GPT4.GTUDC.BIT.UDF = 0;			// カウント方向強制設定解除

	GPT6.GTUDC.BIT.UDF = 1;			// カウント方向強制設定する
	{
		GPT6.GTUDC.BIT.UD = 1;		// アップカウント
	}
	GPT6.GTUDC.BIT.UDF = 0;			// カウント方向強制設定解除

	// カウントクロックの選択
	GPT4.GTCR.BIT.TPCS = 3;			// PCLKA / 8
	GPT6.GTCR.BIT.TPCS = 3;

	// 周期設定
	GPT4.GTPR = 65535;
	GPT6.GTPR = 65535;

	// カウンタ初期値設定
	GPT4.GTCNT = 0x0000;
	GPT6.GTCNT = 0x0000;

	// GTIOC端子機能設定
	GPT4.GTIOR.BIT.GTIOB = 0x19;	// コンペアマッチで出力Ｌ、周期の終わりでＨ
	GPT6.GTIOR.BIT.GTIOA = 0x19;

	// GTIOC端子モード選択
	PORT9.PMR.BIT.B2 = 0;			// PMRを0にしてから…
	PORT9.PMR.BIT.B3 = 0;

	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.P92PFS.BIT.PSEL = 0x6;	// GTIOC4Bを選択
		MPC.P93PFS.BIT.PSEL = 0x6;	// GTIOC6Aを選択
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	// 端子を周辺機能として使用
	PORT9.PMR.BIT.B2 = 1;
	PORT9.PMR.BIT.B3 = 1;

	// コンペアマッチ値設定
	GPT4.GTCCRB = 0;
	GPT6.GTCCRA = 0;

	// GTIOC端子出力許可設定
	GPT4.GTONCR.BIT.OBE = 0;
	GPT6.GTONCR.BIT.OAE = 0;

	// カウント開始
	GPTB.GTSTR.BIT.CST4 = 1;
	GPTB.GTSTR.BIT.CST6 = 1;
}


void PWM1_set(_UWORD fq, float duty)
{
	_UWORD cycle = TIMER_FQ / fq;
	if(cycle > 65535)
	{
		cycle = 65535;
	}

	GPT6.GTPR = cycle;
	GPT6.GTCCRA = (_UWORD)(cycle * duty);
}

void PWM1_On(void)
{
	GPT6.GTONCR.BIT.OAE = 1;
}

void PWM1_Off(void)
{
	GPT6.GTONCR.BIT.OAE = 0;
}


void BUZZER_set(_UWORD fq, float duty)
{
	_UWORD cycle = TIMER_FQ / fq;
	if(cycle > 65535)
	{
		cycle = 65535;
	}

	GPT4.GTPR = cycle;
	GPT4.GTCCRB = (_UWORD)(cycle * duty);
}

void BUZZER_On(void)
{
	GPT4.GTONCR.BIT.OBE = 1;
}

void BUZZER_Off(void)
{
	GPT4.GTONCR.BIT.OBE = 0;
}

