/*
 * GPT456.h
 *
 *  Created on: 2016/09/03
 *      Author: Matsutomo2
 */

#include "..\..\typedefine.h"

#ifndef MODULES_MICON_GPT46_H_
#define MODULES_MICON_GPT46_H_


#ifdef __cplusplus
extern "C" {
#endif

void GPT46_init(void);


void PWM1_set(_UWORD fq, float duty);

void PWM1_On(void);

void PWM1_Off(void);


void BUZZER_set(_UWORD fq, float duty);

void BUZZER_On(void);

void BUZZER_Off(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_MICON_GPT46_H_ */
