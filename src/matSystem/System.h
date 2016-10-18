/*
 * System.h
 *
 *  Created on: 2016/09/12
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MATSYSTEM_SYSTEM_H_
#define MATSYSTEM_SYSTEM_H_

extern _UDWORD System_CurrentTime;
extern BOOL System_OnSendTIme;

#ifdef __cplusplus
extern "C" {
#endif

void _System_ClockStart(void);

void _System_ClockStop(void);

void _System_SetTime(_UDWORD time);

void _System_Loop(void);

void System_Log(_UWORD errorLog);

#ifdef __cplusplus
}
#endif


#endif /* MATSYSTEM_SYSTEM_H_ */
