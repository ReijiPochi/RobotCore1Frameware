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

void System_ClockStart(void);

void _System_Loop(void);


#endif /* MATSYSTEM_SYSTEM_H_ */
