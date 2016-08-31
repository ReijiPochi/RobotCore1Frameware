/*
 * Bluetooth.c
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */


#include "Bluetooth.h"
#include "micon/SCIc.h"

void Bluetooth_Activate(void)
{
	uart0_init();
}

_SWORD Bluetooth_GetRecieveData(void)
{
	return uart0_read();
}
