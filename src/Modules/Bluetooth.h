/*
 * Bluetooth.h
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MODULES_BLUETOOTH_H_
#define MODULES_BLUETOOTH_H_


typedef struct
{
	BOOL Maru;
} DUALSHOCK3;


#ifdef __cplusplus
extern "C" {
#endif


void Bluetooth_Activate(void);

_SWORD Bluetooth_GetRecieveData(void);




#ifdef __cplusplus
}
#endif

#endif /* MODULES_BLUETOOTH_H_ */
