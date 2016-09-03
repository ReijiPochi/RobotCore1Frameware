/*
 * S12ADB.h
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "..\..\typedefine.h"

#ifndef MODULES_MICON_S12ADB_H_
#define MODULES_MICON_S12ADB_H_


#ifdef __cplusplus
extern "C" {
#endif


void S12AD_init(void);

void S12AD_Sample(void);

_UWORD S12AD_GetVoltage(_UBYTE channel);

void S12AD1_init(void);

void S12AD1_Sample(void);

_UWORD S12AD1_GetVoltage(_UBYTE channel);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_MICON_S12ADB_H_ */
