/*
 * UART.c
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */


#include "UART.h"
#include "micon\SCIc.h"


void _UART1_Activate(void)
{
	uart1_init();
}

_UBYTE* _UART1_GetRecievedData(_UWORD* count)
{
	_UBYTE* p;

	p = uart1_read(count);
	return p;
}

void _UART1_TransmitData(_UBYTE* data, _UWORD count)
{
	uart1_send(data, count);
}


void _UART0_Activate(void)
{
	uart0_init();
}

_UBYTE* _UART0_GetRecievedData(_UWORD* count)
{
	_UBYTE* p;

	p = uart0_read(count);
	return p;
}

void _UART0_TransmitData(_UBYTE* data, _UWORD count)
{
	uart0_send(data, count);
}
