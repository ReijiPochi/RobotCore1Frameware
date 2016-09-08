/*
 * Connecter.h
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MATSYSTEM_CONNECTER_H_
#define MATSYSTEM_CONNECTER_H_

typedef union
{
	_SDWORD Int;
	float Float;
} DataValue;


#ifdef __cplusplus
extern "C" {
#endif

void _Connecter_Activate(void);

void _Connecter_Recieve(void);

void _Connecter_Transmit(void);

void Connecter_Send(_UBYTE* data, _UBYTE count);

void Connecter_SendFloat(_UBYTE* head, _UBYTE headCount, float value);

void Connecter_SendInte(_UBYTE* head, _UBYTE headCount, _SDWORD value);

void Connecter_InputToHardwarePort(_UBYTE Adress, DataValue data);

void Connecter_RegistHardwarePort(_UBYTE Adress, void (*Input)(DataValue data));

#ifdef __cplusplus
}
#endif


#endif /* MATSYSTEM_CONNECTER_H_ */
