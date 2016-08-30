/*
 * SCIc.c
 *
 *  Created on: 2016/06/08
 *      Author: Matsutomo2
 */

#include "SCIc.h"

#include "vect.h"
#include "iodefine.h"


_UBYTE flag_RXI = 0;
_UBYTE flag_TXI = 0;

static void set(unsigned char bit);
static void clear_errorFlag(void);

/**
 *  SCIc を UARTモード で初期化します。
 */
void uart1_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// SCI1モジュールストップ状態を解除
		SYSTEM.MSTPCRB.BIT.MSTPB30 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// 機能停止
	set(0);

	// I/Oポート機能を設定
	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.PF2PFS.BIT.PSEL = 0x0A;	// RXD0として使用
		MPC.PF3PFS.BIT.PSEL = 0x0A;	// TXD0として使用
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	PORTF.PMR.BIT.B2 = 1;			// PB1を周辺機能として使用
	PORTF.PMR.BIT.B3 = 1;			// PB2を周辺機能として使用

	SCI1.SEMR.BIT.ABCS = 1;			// 基本クロック8サイクルの期間が1ビット期間の転送レート

	// クロック設定
	SCI1.SMR.BIT.CKS = 0x0;			// PCLK/1クロック

	// ビットレート設定
	SCI1.BRR = 4;					// 1.25Mbps

	// パリティビット設定
	SCI1.SMR.BIT.PE = 0;			// パリティなし

	// エラーフラグをクリア
	clear_errorFlag();

	/* Set SCI0 RXI0 interrupt priority level to 7 */
	IPR(SCI1,RXI1) = 0x7;
	/* Enable SCI0 RXI0 interrupts */
	IEN(SCI1,RXI1) = 0x1;
	/* Clear SCI0 RXI0 interrupt flag */
	IR(SCI1,RXI1) = 0x0;

	/* Set SCI0 RXI0 interrupt priority level to 7 */
	IPR(SCI1,TXI1) = 0x7;
	/* Enable SCI0 RXI0 interrupts */
	IEN(SCI1,TXI1) = 0x1;
	/* Clear SCI0 RXI0 interrupt flag */
	IR(SCI1,TXI1) = 0x0;

	// 機能動作
	set(1);
}

/**
 *  SCIc により受信したデータを読み込みます。
 *
 * @return 受信データがある場合はデータを返します。受信データがない場合は-1を返します。
 */
_SDWORD uart1_read(void)
{
	if(	SCI1.SSR.BIT.ORER == 1 || SCI1.SSR.BIT.PER == 1 || SCI1.SSR.BIT.FER == 1 )
	{
		// エラー処理
		_UBYTE dumy = SCI1.RDR;
		clear_errorFlag();

		flag_RXI = 0;
		return -1;
	}
	else
	{
		if(flag_RXI == 1)
		{
			flag_RXI = 0;

			return (_SDWORD)SCI1.RDR;
		}
		else
		{
			return -1;
		}
	}
}


void uart1_send(_UBYTE data)
{
	while(flag_TXI  != 1) { }

	flag_TXI = 0;
	SCI1.TDR = data;
}


// SCI1 の RXI1 割り込み
void Excep_SCI1_RXI1(void)
{
	flag_RXI = 1;
	IR(SCI1,RXI1) = 0x0;
}

void Excep_SCI1_TXI1(void)
{
	flag_TXI = 1;
	IR(SCI1,TXI1) = 0x0;
}

static void set(unsigned char bit)
{
	SCI1.SCR.BYTE = 0x00;


	// TXI割り込み要求
	SCI1.SCR.BIT.TIE = bit;

	// シリアル送信動作
	SCI1.SCR.BIT.TE = bit;

	// RXIおよびERI割り込み要求
	SCI1.SCR.BIT.RIE = bit;

	// シリアル受信動作
	SCI1.SCR.BIT.RE = bit;
}

static void clear_errorFlag(void)
{
	// パリティエラーフラグ
	SCI1.SSR.BIT.PER = 0;

	// フレーミングエラーフラグ
	SCI1.SSR.BIT.FER = 0;

	// オーバランエラーフラグ
	SCI1.SSR.BIT.ORER = 0;
}
