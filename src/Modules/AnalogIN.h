/*
 * AnalogIN.h
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MODULES_ANALOGIN_H_
#define MODULES_ANALOGIN_H_


#ifdef __cplusplus
extern "C" {
#endif


void AnalogIN_Activate(void);

void AnalogIN_Sample(void);

float AnalogIN_GetVoltage(_UBYTE channel);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_ANALOGIN_H_ */
