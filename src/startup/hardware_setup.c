/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  DistanceMeter                          */
/*      FILE         :  hardware_setup.cpp                     */
/*      DESCRIPTION  :  Hardware Setup file                    */
/*      CPU SERIES   :  RX600                                  */
/*      CPU TYPE     :  RX63T                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                                


#include "../Modules/micon/iodefine.h"
#include "../typedefine.h"

#define WAIT_TIME_FOR_MAIN_OSCILLATION      (24746)	// 10,000us + (131072 + 16384) / 10MHz = 24.746ms
#define WAIT_TIME_FOR_PLL_OSCILLATION       (1810)	// 500us + (131072 + 131072) / 200MHz  = 1.81ms


extern void HardwareSetup(void);
void wait(_UINT);


void HardwareSetup(void)
{
	/********** I/Oポート初期化 **********/

	// プロテクトを解除
	SYSTEM.PRCR.WORD = 0xA503;					// PRCRレジスタを書き換える場合、上位8ビットは"0xA5"にする必要がある



	/********** メインクロックの発振設定  **********/

	// メインクロック発振器の発振安定待ち時間を選択  (発振安定時間が 10ms と仮定)
	SYSTEM.MOSCWTCR.BYTE = 0x0D;				// 131072 cycles

	// メインクロック発振器を動作
	SYSTEM.MOSCCR.BYTE = 0x00;
	while(SYSTEM.MOSCCR.BYTE != 0x00) { }		// レジスタの値が書き換わるまで待機

	// メインクロック発振安定待機時間
	wait(WAIT_TIME_FOR_MAIN_OSCILLATION);



	/********** PLL クロックの発振設定  **********/

	// PLL 入力分周比を選択
	SYSTEM.PLLCR.BIT.PLIDIV = 0x0;				// 1分周

	// 周波数逓倍率を選択
	SYSTEM.PLLCR.BIT.STC = 0x13;				// x20

	// PLL クロック発振器のウエイトコントロールレジスタを設定
	SYSTEM.PLLWTCR.BYTE = 0x0A;					// 131072 cycles

	// PLL を動作
	SYSTEM.PLLCR2.BIT.PLLEN = 0;

	// PLL クロック発振安定待機時間
	wait(WAIT_TIME_FOR_PLL_OSCILLATION);



	/********** クロック初期設定  **********/

	// 内部クロックの分周比を選択
	SYSTEM.SCKCR.LONG = 0x21013112;				// S12AD用クロック			: 4分周  =  50 MHz
												// AD用クロック				: 2分周  = 100 MHz
												// 周辺モジュールクロックb		: 2分周  = 100 MHz
												// タイマモジュールクロック		: 8分周  =  25 MHz
												// 外部バスクロック			: 2分周  = 100 MHz
												// システムクロック			: 2分周  = 100 MHz
												// FlashIFクロック			: 4分周  =  50 MHz
	while(SYSTEM.SCKCR.LONG != 0x21013112) { }	// レジスタの値が書き換わるまで待機

	// クロックソースを選択
	SYSTEM.SCKCR3.WORD = 0x0400;				// PLL回路を選択
	while(SYSTEM.SCKCR3.WORD != 0x0400) { }		// レジスタの値が書き換わるまで待機



	// プロテクトを設定
	SYSTEM.PRCR.WORD = 0xA500;					// PRCRレジスタを書き換える場合、上位8ビットは"0xA5"にする必要がある
}



/**
 * LOCO がカウントソースのCMT0 を使用して time で指定された時間だけソフトウェアウエイトします
 *
 * @author R.Tanizaki
 * @param time (UnsignedLong) ウエイトする時間 [us]
 * @return void
 */
void wait(_UINT time)
{
	/********** 開始処理 **********/

	// CMT0, CMT1 のモジュールストップ状態を解除
	MSTP(CMT0) = 0;

	// CMT0 のカウントを停止
	CMT.CMSTR0.BIT.STR0 = 0;

	// CMT0 のカウントソースを設定
	CMT0.CMCR.BIT.CKS = 0x1;

	// コンペアマッチ割り込みを許可
	CMT0.CMCR.BIT.CMIE = 1;

	// CMT0 のカウントをクリア
	CMT0.CMCNT = 0x0000;

	if(time != 0)
	{
		time -= 1;						// 関数がコールされてからの時間を差し引く（？）
	}

	// CMT0 に待ち時間を設定
	CMT0.CMCOR = (_UWORD)(time / 256);	// (1 / 125kHz) * 32 * 1000000 : 1count = 256us

	// CMT0 割り込み要求をクリア
	while(IR(CMT0,CMI0) == 1)
	{
		IR(CMT0,CMI0) = 0;
	}



	/********** ソフトウェアウエイト **********/

	// CMT0 のカウントを開始
	CMT.CMSTR0.BIT.STR0 = 1;

	// CMI0 割り込みが発生するまで待機
	while(IR(CMT0,CMI0) == 0) { }



	/********** 終了処理 **********/

	// CMT0 のカウントを停止
	CMT.CMSTR0.BIT.STR0 = 0;

	// CMT0 を初期化
	CMT0.CMCR.BIT.CKS = 0x0;
	CMT0.CMCR.BIT.CMIE = 0;
	CMT0.CMCOR = 0x0000;
	IR(CMT0,CMI0) = 0;

	// CMT0, CMT1 をモジュールストップ状態に
	MSTP(CMT0) = 1;
}
