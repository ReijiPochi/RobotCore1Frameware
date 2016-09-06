/*
 * Servo.c
 *
 *  Created on: 2016/09/06
 *      Author: Matsutomo2
 */


#include "Servo.h"
#include "micon\GPT46.h"

void Servo_Activate(void)
{
	//GPT46_init();
	PWM1_set(50, 1.0);
	PWM1_On();
}

void Servo1_RotationIn(float degree, SetBy setter)
{
	float duty = 0.05 + (degree + 90.0) / 3600.0;
	duty = 1.0 - duty;

	PWM1_set(50, duty);
	PWM1_On();
}
