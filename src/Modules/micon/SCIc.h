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

_SDWORD uart1_read(void);

void uart1_send(_UBYTE data);

#ifdef __cplusplus
}
#endif

#endif /* MICON_SCIC_H_ */
