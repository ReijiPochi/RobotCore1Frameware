/*
 * Servo.c
 *
 *  Created on: 2016/09/06
 *      Author: Matsutomo2
 */


#include "Servo.h"

#include "micon/GPT456.h"

void Servo_Activate(void)
{
	//GPT46_init();
	Servo1_set(50, 1.0);
	Servo1_On();
	Servo2_set(50, 1.0);
	Servo2_On();
}

void Servo1_RotationIn(float degree, SetBy setter)
{
	float duty = 1.0 - (0.05 + degree / 1800.0);

	Servo1_set(50, duty);
	Servo1_On();
}

void Servo2_RotationIn(float degree, SetBy setter)
{
	float duty = 1.0 - (0.05 + degree / 1800.0);

	Servo2_set(50, duty);
	Servo2_On();
}
