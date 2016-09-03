/*
 * Buzzer.h
 *
 *  Created on: 2016/09/03
 *      Author: Matsutomo2
 */


#include "..\typedefine.h"

#ifndef MODULES_BUZZER_H_
#define MODULES_BUZZER_H_


#ifdef __cplusplus
extern "C" {
#endif


void Buzzer_Activate(void);

void _Buzzer_Loop(void);

void Buzzer_On(void);

void Buzzer_Off(void);

void Buzzer_OneTime(_UWORD ms);

void Buzzer_StepUp(void);

void Buzzer_StepDown(void);

void Buzzer_Siren1(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_BUZZER_H_ */
