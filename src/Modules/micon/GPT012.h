/*
 * GPT.h
 *
 *  Created on: 2016/06/03
 *      Author: Matsutomo2
 */

#ifndef MICON_GPT_H_
#define MICON_GPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  GPT0,GPT1,GPT2を初期化して、PWM出力できる状態にします。
 */
void GPT012_init(void);


void PWM_M1_set(float duty);


void PWM_M2_set(float duty);


void PWM_M3_set(float duty);


void PWM_M4_set(float duty);


void PWM_M5_set(float duty);


void PWM_M6_set(float duty);

#ifdef __cplusplus
}
#endif

#endif /* MICON_GPT_H_ */
