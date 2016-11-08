/*
 * RIIC.c
 *
 *  Created on: 2016/11/08
 *      Author: Matsutomo2
 */

#include "RIIC.h"

void RIIC_init(void)
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

	RIIC1.ICCR1.BIT.ICE = 0;		// SCLn、SDAn端子非駆動状態

	RIIC1.ICCR1.BIT.IICRST = 1;		// RIICリセット

	RIIC1.ICCR1.BIT.ICE = 1;		// 内部リセット

	// ジェネラルコールアドレス許可
	RIIC1.ICSER.BIT.GCAE = 0;		// ジェネラルコールアドレス検出は無効


}
