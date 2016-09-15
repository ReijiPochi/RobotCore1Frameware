/*
 * Bluetooth.h
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MODULES_BLUETOOTH_H_
#define MODULES_BLUETOOTH_H_


#ifdef __cplusplus
extern "C" {
#endif


void Bluetooth_Activate(void (*callback)(DUALSHOCK3));

void _Bluetooth_Loop(void);

void _Bluetooth_Do(_UBYTE module, _UBYTE command, _UBYTE* value);

void Bluetooth_CommandIn(DUALSHOCK3 value, SetBy setter);

void Bluetooth_Vibrate1(void);

void Bluetooth_Vibrate2(void);


#ifdef __cplusplus
}
#endif

#endif /* MODULES_BLUETOOTH_H_ */
