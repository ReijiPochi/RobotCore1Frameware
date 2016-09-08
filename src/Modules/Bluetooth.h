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
	union
	{
		_UWORD WORD;
		struct
		{
			BOOL UpArrow:1;
			BOOL DownArrow:1;
			BOOL RightArrow:1;
			BOOL LeftArrow:1;
			BOOL Sankaku:1;
			BOOL Batsu:1;
			BOOL Maru:1;
			BOOL Shikaku:1;
			_UBYTE dummy:1;
			BOOL L1:1;
			BOOL L2:1;
			BOOL R1:1;
			BOOL R2:1;
			BOOL Start:1;
			BOOL Select:1;
		}BIT;
	} Buttons;

	struct
	{
		_SBYTE X;
		_SBYTE Y;
	} AnalogL;

	struct
	{
		_SBYTE X;
		_SBYTE Y;
	} AnalogR;
} DUALSHOCK3;


#ifdef __cplusplus
extern "C" {
#endif


void Bluetooth_Activate(void (*callback)(DUALSHOCK3));

void _Bluetooth_Loop(void);

void _Bluetooth_Do(_UBYTE module, _UBYTE command, _UBYTE* value);

#ifdef __cplusplus
}
#endif

#endif /* MODULES_BLUETOOTH_H_ */
