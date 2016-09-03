/*
 * MotorPWM.c
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */


#include "Motor.h"
#include "micon/IO.h"
#include "micon/GPT012.h"

#define THRESHOLD	 		(0.001)
#define MAX_ACCELERATION	(0.5)

static float norm(float, _UBYTE*);
static void motor1_SetMode(MotorMode);
static void motor2_SetMode(MotorMode);
static void motor3_SetMode(MotorMode);
static void motor4_SetMode(MotorMode);
static void motor5_SetMode(MotorMode);
static void motor6_SetMode(MotorMode);

float trgDuty[6];
float actualDuty[6];
_UBYTE direction[6];

/**
 *  Motorモジュールを使用可能にします。
 */
void Motor_Activate(void)
{
	GPT012_init();

	IO_Motor_Init();
}

void Motor_UnlockSTBY(void)
{
	STBY(1);
}

void Motor_LockSTBY(void)
{
	STBY(0);
}

void _Motor_Loop(void)
{
	int i;
	float d, a;

	for(i = 0; i < 6; i++)
	{
		d = trgDuty[i] - actualDuty[i];

		a = d * 0.2;

		if(a > MAX_ACCELERATION)
			a = MAX_ACCELERATION;
		else if(a < -MAX_ACCELERATION)
			a = -MAX_ACCELERATION;

		actualDuty[i] += a;
	}



	PWM_M1_set(norm(actualDuty[0], &direction[0]));
	PWM_M2_set(norm(actualDuty[1], &direction[1]));
	PWM_M3_set(norm(actualDuty[2], &direction[2]));
	PWM_M4_set(norm(actualDuty[3], &direction[3]));
	PWM_M5_set(norm(actualDuty[4], &direction[4]));
	PWM_M6_set(norm(actualDuty[5], &direction[5]));

	if(actualDuty[0] < THRESHOLD && actualDuty[0] > -THRESHOLD)
		motor1_SetMode(MotorMode_BRAKE);
	else if(direction[0] == 1)
		motor1_SetMode(MotorMode_CW);
	else if(direction[0] == 0)
		motor1_SetMode(MotorMode_CCW);

	if(actualDuty[1] < THRESHOLD && actualDuty[1] > -THRESHOLD)
		motor2_SetMode(MotorMode_BRAKE);
	else if(direction[1] == 1)
		motor2_SetMode(MotorMode_CW);
	else if(direction[1] == 0)
		motor2_SetMode(MotorMode_CCW);

	if(actualDuty[2] < THRESHOLD && actualDuty[2] > -THRESHOLD)
		motor3_SetMode(MotorMode_BRAKE);
	else if(direction[2] == 1)
		motor3_SetMode(MotorMode_CW);
	else if(direction[2] == 0)
		motor3_SetMode(MotorMode_CCW);

	if(actualDuty[3] < THRESHOLD && actualDuty[3] > -THRESHOLD)
		motor4_SetMode(MotorMode_BRAKE);
	else if(direction[3] == 1)
		motor4_SetMode(MotorMode_CW);
	else if(direction[3] == 0)
		motor4_SetMode(MotorMode_CCW);

	if(actualDuty[4] < THRESHOLD && actualDuty[4] > -THRESHOLD)
		motor5_SetMode(MotorMode_BRAKE);
	else if(direction[4] == 1)
		motor5_SetMode(MotorMode_CW);
	else if(direction[4] == 0)
		motor5_SetMode(MotorMode_CCW);

	if(actualDuty[5] < THRESHOLD && actualDuty[5] > -THRESHOLD)
		motor6_SetMode(MotorMode_BRAKE);
	else if(direction[5] == 1)
		motor6_SetMode(MotorMode_CW);
	else if(direction[5] == 0)
		motor6_SetMode(MotorMode_CCW);


	_LED_Info_Off();

	for(i = 0; i < 6; i++)
	{
		if(actualDuty[i] > THRESHOLD || actualDuty[i] < -THRESHOLD)
			_LED_Info_On();
	}
}

/**
 *  Motor1モジュールのPWM値を設定します。
 *
 *  @param duty デューティー比　( -1.0 ～ 1.0の値 )
 */
void Motor1_SetPWM(float duty)
{
	trgDuty[0] = duty;
}

void Motor2_SetPWM(float duty)
{
	trgDuty[1] = duty;
}

void Motor3_SetPWM(float duty)
{
	trgDuty[2] = duty;
}

void Motor4_SetPWM(float duty)
{
	trgDuty[3] = duty;
}

void Motor5_SetPWM(float duty)
{
	trgDuty[4] = duty;
}

void Motor6_SetPWM(float duty)
{
	trgDuty[5] = duty;
}


void motor1_SetMode(MotorMode mode)
{
	switch(mode)
	{
		case MotorMode_CW:
			Motor1_MODE(1, 0);
			break;

		case MotorMode_CCW:
			Motor1_MODE(0, 1);
			break;

		case MotorMode_BRAKE:
			Motor1_MODE(1, 1);
			break;

		case MotorMode_FREE:
			Motor1_MODE(0, 0);
			break;

		default:
			break;
	}
}

void motor2_SetMode(MotorMode mode)
{
	switch(mode)
	{
		case MotorMode_CW:
			Motor2_MODE(1, 0);
			break;

		case MotorMode_CCW:
			Motor2_MODE(0, 1);
			break;

		case MotorMode_BRAKE:
			Motor2_MODE(1, 1);
			break;

		case MotorMode_FREE:
			Motor2_MODE(0, 0);
			break;

		default:
			break;
	}
}

void motor3_SetMode(MotorMode mode)
{
	switch(mode)
	{
		case MotorMode_CW:
			Motor3_MODE(1, 0);
			break;

		case MotorMode_CCW:
			Motor3_MODE(0, 1);
			break;

		case MotorMode_BRAKE:
			Motor3_MODE(1, 1);
			break;

		case MotorMode_FREE:
			Motor3_MODE(0, 0);
			break;

		default:
			break;
	}
}

void motor4_SetMode(MotorMode mode)
{
	switch(mode)
	{
		case MotorMode_CW:
			Motor4_MODE(1, 0);
			break;

		case MotorMode_CCW:
			Motor4_MODE(0, 1);
			break;

		case MotorMode_BRAKE:
			Motor4_MODE(1, 1);
			break;

		case MotorMode_FREE:
			Motor4_MODE(0, 0);
			break;

		default:
			break;
	}
}

void motor5_SetMode(MotorMode mode)
{
	switch(mode)
	{
		case MotorMode_CW:
			Motor5_MODE(1, 0);
			break;

		case MotorMode_CCW:
			Motor5_MODE(0, 1);
			break;

		case MotorMode_BRAKE:
			Motor5_MODE(1, 1);
			break;

		case MotorMode_FREE:
			Motor5_MODE(0, 0);
			break;

		default:
			break;
	}
}

void motor6_SetMode(MotorMode mode)
{
	switch(mode)
	{
		case MotorMode_CW:
			Motor6_MODE(1, 0);
			break;

		case MotorMode_CCW:
			Motor6_MODE(0, 1);
			break;

		case MotorMode_BRAKE:
			Motor6_MODE(1, 1);
			break;

		case MotorMode_FREE:
			Motor6_MODE(0, 0);
			break;

		default:
			break;
	}
}

float norm(float value, _UBYTE* isPositive)
{
	if(value > 0.0)
	{
		value *= 1.0;
		*isPositive = 1;
	}
	else
	{
		value *= -1.0;
		*isPositive = 0;
	}

	if(value > 1.0)
	{
		value = 1.0;
	}

	return value;
}
