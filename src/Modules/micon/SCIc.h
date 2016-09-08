/*
 * SCIc.h
 *
 *  Created on: 2016/06/08
 *      Author: Matsutomo2
 */

#include "..\..\typedefine.h"

#ifndef MICON_SCIC_H_
#define MICON_SCIC_H_

#ifdef __cplusplus
extern "C" {
#endif

void uart1_init(void);

_UBYTE* uart1_read(_UWORD* count);

void uart1_send(_UBYTE* data, _UWORD count);

void uart0_init(void);

_UBYTE* uart0_read(_UWORD* count);

void uart0_send(_UBYTE* data, _UWORD count);

#ifdef __cplusplus
}
#endif

#endif /* MICON_SCIC_H_ */
