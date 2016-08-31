/*
 * GPT.c
 *
 *  Created on: 2016/06/03
 *      Author: Matsutomo2
 */

#include "iodefine.h"
#include "..\..\typedefine.h"
#include "GPT012.h"


#define PWM_CYCLE_TIME (5000) //  TIMER_CLOCK / PWM_FREQUENCY : 20 kHz

/**
 *  GPT0,GPT1,GPT2を初期化して、PWM出力できる状態にします。
 */
void GPT012_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// GPTユニット0のモジュールストップ状態を解除
		SYSTEM.MSTPCRA.BIT.MSTPA7 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// カウント停止
	GPT.GTSTR.BIT.CST0 = 0;
	GPT.GTSTR.BIT.CST1 = 0;
	GPT.GTSTR.BIT.CST2 = 0;

	// 動作モード設定
	GPT0.GTCR.BIT.MD = 0;			// のこぎり波ＰＷＭモード
	GPT1.GTCR.BIT.MD = 0;
	GPT2.GTCR.BIT.MD = 0;

	// カウント方向設定
	GPT0.GTUDC.BIT.UDF = 1;			// カウント方向強制設定する
	{
		GPT0.GTUDC.BIT.UD = 1;		// アップカウント
	}
	GPT0.GTUDC.BIT.UDF = 0;			// カウント方向強制設定解除

	GPT1.GTUDC.BIT.UDF = 1;			// カウント方向強制設定する
	{
		GPT1.GTUDC.BIT.UD = 1;		// アップカウント
	}
	GPT1.GTUDC.BIT.UDF = 0;			// カウント方向強制設定解除

	GPT2.GTUDC.BIT.UDF = 1;			// カウント方向強制設定する
	{
		GPT2.GTUDC.BIT.UD = 1;		// アップカウント
	}
	GPT2.GTUDC.BIT.UDF = 0;			// カウント方向強制設定解除

	// カウントクロックの選択
	GPT0.GTCR.BIT.TPCS = 0;			// 分周しない
	GPT1.GTCR.BIT.TPCS = 0;
	GPT2.GTCR.BIT.TPCS = 0;

	// 周期設定
	GPT0.GTPR = PWM_CYCLE_TIME;
	GPT1.GTPR = PWM_CYCLE_TIME;
	GPT2.GTPR = PWM_CYCLE_TIME;

	// カウンタ初期値設定
	GPT0.GTCNT = 0x0000;
	GPT1.GTCNT = 0x0000;
	GPT2.GTCNT = 0x0000;

	// GTIOC端子機能設定
	GPT0.GTIOR.BIT.GTIOA = 0x19;	// コンペアマッチで出力Ｌ、周期の終わりでＨ
	GPT0.GTIOR.BIT.GTIOB = 0x19;
	GPT1.GTIOR.BIT.GTIOA = 0x19;
	GPT1.GTIOR.BIT.GTIOB = 0x19;
	GPT2.GTIOR.BIT.GTIOA = 0x19;
	GPT2.GTIOR.BIT.GTIOB = 0x19;

	// GTIOC端子モード選択
	PORTD.PMR.BIT.B7 = 0;			// PMRを0にしてから…
	PORTD.PMR.BIT.B6 = 0;
	PORTD.PMR.BIT.B5 = 0;
	PORTD.PMR.BIT.B4 = 0;
	PORTD.PMR.BIT.B3 = 0;
	PORTD.PMR.BIT.B2 = 0;

	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.PD7PFS.BIT.PSEL = 0x6;	// GTIOC0Aを選択
		MPC.PD6PFS.BIT.PSEL = 0x6;	// GTIOC0Bを選択
		MPC.PD5PFS.BIT.PSEL = 0x6;	// GTIOC1Aを選択
		MPC.PD4PFS.BIT.PSEL = 0x6;	// GTIOC1Bを選択
		MPC.PD3PFS.BIT.PSEL = 0x6;	// GTIOC2Aを選択
		MPC.PD2PFS.BIT.PSEL = 0x6;	// GTIOC2Bを選択
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	// 端子を周辺機能として使用
	PORTD.PMR.BIT.B7 = 1;			// PMRを0にしてから…
	PORTD.PMR.BIT.B6 = 1;
	PORTD.PMR.BIT.B5 = 1;
	PORTD.PMR.BIT.B4 = 1;
	PORTD.PMR.BIT.B3 = 1;
	PORTD.PMR.BIT.B2 = 1;

	// コンペアマッチ値設定
	GPT0.GTCCRA = 0;
	GPT0.GTCCRB = 0;
	GPT1.GTCCRA = 0;
	GPT1.GTCCRB = 0;
	GPT2.GTCCRA = 0;
	GPT2.GTCCRB = 0;

	// GTIOC端子出力許可設定
	GPT0.GTONCR.BIT.OAE = 1;
	GPT0.GTONCR.BIT.OBE = 1;
	GPT1.GTONCR.BIT.OAE = 1;
	GPT1.GTONCR.BIT.OBE = 1;
	GPT2.GTONCR.BIT.OAE = 1;
	GPT2.GTONCR.BIT.OBE = 1;

	// カウント開始
	GPT.GTSTR.BIT.CST0 = 1;
	GPT.GTSTR.BIT.CST1 = 1;
	GPT.GTSTR.BIT.CST2 = 1;
}

void PWM_M1_set(float duty)
{
	GPT0.GTCCRA = (_UWORD)(PWM_CYCLE_TIME * duty);
}

void PWM_M2_set(float duty)
{
	GPT0.GTCCRB = (_UWORD)(PWM_CYCLE_TIME * duty);
}

void PWM_M3_set(float duty)
{
	GPT1.GTCCRA = (_UWORD)(PWM_CYCLE_TIME * duty);
}

void PWM_M4_set(float duty)
{
	GPT1.GTCCRB = (_UWORD)(PWM_CYCLE_TIME * duty);
}

void PWM_M5_set(float duty)
{
	GPT2.GTCCRA = (_UWORD)(PWM_CYCLE_TIME * duty);
}

void PWM_M6_set(float duty)
{
	GPT2.GTCCRB = (_UWORD)(PWM_CYCLE_TIME * duty);
}

