/*
 * Servo.h
 *
 *  Created on: 2016/09/06
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"

#ifndef MODULES_SERVO_H_
#define MODULES_SERVO_H_


#ifdef __cplusplus
extern "C" {
#endif


void Servo_Activate(void);

void Servo1_RotationIn(float degree, SetBy setter);

void Servo2_RotationIn(float degree, SetBy setter);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_SERVO_H_ */
