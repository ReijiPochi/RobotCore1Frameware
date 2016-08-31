/*
 * SCIc.c
 *
 *  Created on: 2016/06/08
 *      Author: Matsutomo2
 */

#include "SCIc.h"

#include "vect.h"
#include "iodefine.h"


_UBYTE flag_RXI0 = 0;
_UBYTE flag_TXI0 = 0;
_UBYTE flag_RXI1 = 0;
_UBYTE flag_TXI1 = 0;

_UBYTE uart0_data;

static void uart0_set(unsigned char bit);
static void uart0_clear_errorFlag(void);
static void uart1_set(unsigned char bit);
static void uart1_clear_errorFlag(void);

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
	uart1_set(0);

	// I/Oポート機能を設定
	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.PF2PFS.BIT.PSEL = 0x0A;	// RXD1として使用
		MPC.PF3PFS.BIT.PSEL = 0x0A;	// TXD1として使用
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	PORTF.PMR.BIT.B2 = 1;			// 周辺機能として使用
	PORTF.PMR.BIT.B3 = 1;			// 周辺機能として使用

	SCI1.SEMR.BIT.ABCS = 1;			// 基本クロック8サイクルの期間が1ビット期間の転送レート

	// クロック設定
	SCI1.SMR.BIT.CKS = 0x0;			// PCLK/1クロック

	// ビットレート設定
	SCI1.BRR = 4;					// 1.25Mbps

	// エラーフラグをクリア
	uart1_clear_errorFlag();

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
	uart1_set(1);
}

/**
 *  SCIc により受信したデータを読み込みます。
 *
 * @return 受信データがある場合はデータを返します。受信データがない場合は-1を返します。
 */
_SWORD uart1_read(void)
{
	if(	SCI1.SSR.BIT.ORER == 1 || SCI1.SSR.BIT.PER == 1 || SCI1.SSR.BIT.FER == 1 )
	{
		// エラー処理
		_SWORD dumy = SCI1.RDR;
		uart1_clear_errorFlag();

		flag_RXI1 = 0;
		return -1;
	}
	else
	{
		if(flag_RXI1 == 1)
		{
			flag_RXI1 = 0;

			return (_SWORD)SCI1.RDR;
		}
		else
		{
			return -1;
		}
	}
}


void uart1_send(_UBYTE data)
{
	while(flag_TXI1  != 1) { }

	flag_TXI1 = 0;
	SCI1.TDR = data;
}


// SCI1 の RXI1 割り込み
void Excep_SCI1_RXI1(void)
{
	flag_RXI1 = 1;
	IR(SCI1,RXI1) = 0x0;
}

void Excep_SCI1_TXI1(void)
{
	flag_TXI1 = 1;
	IR(SCI1,TXI1) = 0x0;
}

static void uart1_set(unsigned char bit)
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

static void uart1_clear_errorFlag(void)
{
	// パリティエラーフラグ
	SCI1.SSR.BIT.PER = 0;

	// フレーミングエラーフラグ
	SCI1.SSR.BIT.FER = 0;

	// オーバランエラーフラグ
	SCI1.SSR.BIT.ORER = 0;
}


void uart0_init(void)
{
	// プロテクト解除
	SYSTEM.PRCR.WORD = 0xA502;
	{
		// SCI0モジュールストップ状態を解除
		SYSTEM.MSTPCRB.BIT.MSTPB31 = 0;
	}
	SYSTEM.PRCR.WORD = 0xA500;

	// 機能停止
	uart0_set(0);

	// I/Oポート機能を設定
	MPC.PWPR.BIT.B0WI = 0;			// PFSWEレジスタ書き込み許可
	MPC.PWPR.BIT.PFSWE = 1;			// PFSレジスタ書き込み許可
	{
		MPC.P22PFS.BIT.PSEL = 0x0A;	// RXD0として使用
		MPC.P23PFS.BIT.PSEL = 0x0A;	// TXD0として使用
	}
	MPC.PWPR.BIT.PFSWE = 0;			// PFSレジスタ書き込み禁止
	MPC.PWPR.BIT.B0WI = 1;			// PFSWEレジスタ書き込み禁止

	PORT2.PMR.BIT.B2 = 1;			// 周辺機能として使用
	PORT2.PMR.BIT.B3 = 1;			// 周辺機能として使用

	// クロック設定
	SCI0.SMR.BIT.CKS = 0x1;			// PCLK/4クロック

	// ビットレート設定
	SCI0.BRR = 80;					// 9600bps

	// エラーフラグをクリア
	uart0_clear_errorFlag();

	/* Set SCI0 RXI0 interrupt priority level to 7 */
	IPR(SCI0,RXI0) = 0x7;
	/* Enable SCI0 RXI0 interrupts */
	IEN(SCI0,RXI0) = 0x1;
	/* Clear SCI0 RXI0 interrupt flag */
	IR(SCI0,RXI0) = 0x0;

	/* Set SCI0 RXI0 interrupt priority level to 7 */
	IPR(SCI0,TXI0) = 0x7;
	/* Enable SCI0 RXI0 interrupts */
	IEN(SCI0,TXI0) = 0x1;
	/* Clear SCI0 RXI0 interrupt flag */
	IR(SCI0,TXI0) = 0x0;

	// 機能動作
	uart0_set(1);
}

_SWORD uart0_read(void)
{
	if(	SCI0.SSR.BIT.ORER == 1 || SCI0.SSR.BIT.PER == 1 || SCI0.SSR.BIT.FER == 1 )
	{
		// エラー処理
		_SWORD dumy = SCI0.RDR;
		uart1_clear_errorFlag();

		flag_RXI0 = 0;
		return -1;
	}
	else
	{
		if(flag_RXI0 == 1)
		{
			flag_RXI0 = 0;

			uart0_data = SCI0.RDR;
			return uart0_data;
		}
		else
		{
			return -1;
		}
	}
}

void Excep_SCI0_RXI0(void)
{
	flag_RXI0 = 1;
	IR(SCI0,RXI0) = 0x0;
}

void Excep_SCI0_TXI0(void)
{
	flag_TXI0 = 1;
	IR(SCI0,TXI0) = 0x0;
}

static void uart0_set(unsigned char bit)
{
	SCI0.SCR.BYTE = 0x00;


	// TXI割り込み要求
	SCI0.SCR.BIT.TIE = bit;

	// シリアル送信動作
	SCI0.SCR.BIT.TE = bit;

	// RXIおよびERI割り込み要求
	SCI0.SCR.BIT.RIE = bit;

	// シリアル受信動作
	SCI0.SCR.BIT.RE = bit;
}

static void uart0_clear_errorFlag(void)
{
	// パリティエラーフラグ
	SCI0.SSR.BIT.PER = 0;

	// フレーミングエラーフラグ
	SCI0.SSR.BIT.FER = 0;

	// オーバランエラーフラグ
	SCI0.SSR.BIT.ORER = 0;
}
