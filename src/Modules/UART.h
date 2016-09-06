/*
 * UART.h
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MODULES_UART_H_
#define MODULES_UART_H_


#ifdef __cplusplus
extern "C" {
#endif


void _UART1_Activate(void);

_UBYTE* _UART1_GetRecievedData(_UWORD* count);

void _UART1_TransmitData(_UBYTE* data, _UWORD count);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_UART_H_ */
