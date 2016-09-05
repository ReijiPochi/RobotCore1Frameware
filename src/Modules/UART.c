/*
 * UART.c
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */


#include "UART.h"
#include "micon\SCIc.h"


void UART1_Activate(void)
{
	uart1_init();
}

_UBYTE* UART1_GetRecievedData(_UWORD* count)
{
	_UBYTE* p;

	p = uart1_read(count);
	return p;
}

void UART1_TransmitData(_UBYTE* data, _UWORD count)
{
	uart1_send(data, count);
}
