/*
 * CMT.h
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */

#include "..\..\typedefine.h"

#ifndef MODULES_MICON_CMT_H_
#define MODULES_MICON_CMT_H_


#ifdef __cplusplus
extern "C" {
#endif


void CMT_init(void);

void CMT0_Set(_UBYTE clockSource, _UWORD CMCOR, void (*callback)(void));

void CMT0_Start(void);

void CMT0_Stop(void);

void CMT1_Set(_UBYTE clockSource, _UWORD CMCOR, void (*callback)(void));

void CMT1_Start(void);

void CMT1_Stop(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_MICON_CMT_H_ */
