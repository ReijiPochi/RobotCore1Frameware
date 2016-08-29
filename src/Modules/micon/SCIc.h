/*
 * SCIc.h
 *
 *  Created on: 2016/06/08
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MICON_SCIC_H_
#define MICON_SCIC_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  SCIc を UARTモード で初期化します。
 */
void uart_init(void);

/**
 *  SCIc により受信したデータを読み込みます。
 *
 * @return 受信データがある場合はデータを返します。受信データがない場合は-1を返します。
 */
_SDWORD uart_read(void);

void uart_send(_UBYTE data);

#ifdef __cplusplus
}
#endif

#endif /* MICON_SCIC_H_ */
