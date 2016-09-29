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

void GPT456_init(void);


void Servo1_set(_UWORD fq, float duty);

void Servo1_On(void);

void Servo1_Off(void);


void Servo2_set(_UWORD fq, float duty);

void Servo2_On(void);

void Servo2_Off(void);


void BUZZER_set(_UWORD fq, float duty);

void BUZZER_On(void);

void BUZZER_Off(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_MICON_GPT46_H_ */
