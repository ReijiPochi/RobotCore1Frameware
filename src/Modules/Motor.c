/*
 * MotorPWM.c
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */


#include "Motor.h"
#include "micon/IO.h"
#include "micon/GPT012.h"
#include "..\DataConverter.h"
#include "..\matSystem\Connecter.h"

#define THRESHOLD	 		(0.001)
#define MAX_ACCELERATION	(0.5)

static float norm(float, _UBYTE*);
static void motor1_SetMode(MotorMode);
static void motor2_SetMode(MotorMode);
static void motor3_SetMode(MotorMode);
static void motor4_SetMode(MotorMode);
static void motor5_SetMode(MotorMode);
static void motor6_SetMode(MotorMode);

static void Motor1_DutyOut(float duty);
static void Motor2_DutyOut(float duty);
static void Motor3_DutyOut(float duty);
static void Motor4_DutyOut(float duty);
static void Motor5_DutyOut(float duty);
static void Motor6_DutyOut(float duty);

static void motor1_Do(_UBYTE command, _UBYTE* value);
static void motor2_Do(_UBYTE command, _UBYTE* value);
static void motor3_Do(_UBYTE command, _UBYTE* value);
static void motor4_Do(_UBYTE command, _UBYTE* value);
static void motor5_Do(_UBYTE command, _UBYTE* value);
static void motor6_Do(_UBYTE command, _UBYTE* value);

ModulePortState motor1_DutyIn_State = Free;
ModulePortState motor2_DutyIn_State = Free;
ModulePortState motor3_DutyIn_State = Free;
ModulePortState motor4_DutyIn_State = Free;
ModulePortState motor5_DutyIn_State = Free;
ModulePortState motor6_DutyIn_State = Free;

ModulePortState motor1_DutyOut_State = Free;
ModulePortState motor2_DutyOut_State = Free;
ModulePortState motor3_DutyOut_State = Free;
ModulePortState motor4_DutyOut_State = Free;
ModulePortState motor5_DutyOut_State = Free;
ModulePortState motor6_DutyOut_State = Free;

_UBYTE motor1_DutyIn_HardwarePortAdress = 0;

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

	Motor1_DutyOut(norm(actualDuty[0], &direction[0]));
	Motor2_DutyOut(norm(actualDuty[1], &direction[1]));
	Motor3_DutyOut(norm(actualDuty[2], &direction[2]));
	Motor4_DutyOut(norm(actualDuty[3], &direction[3]));
	Motor5_DutyOut(norm(actualDuty[4], &direction[4]));
	Motor6_DutyOut(norm(actualDuty[5], &direction[5]));

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

void Motor1_DutyIn(float duty, SetBy setter)
{
	if(motor1_DutyIn_State == Free)
		trgDuty[0] = duty;
	else if(motor1_DutyIn_State == ForceByHost && setter == MatStudio)
	{
		trgDuty[0] = duty;
	}
}

void Motor1_DutyOut(float duty)
{
	DataValue data;
	PWM_M1_set(duty);
	if(motor1_DutyOut_State == LookByHost)
		Connecter_SendFloat("Mm1;5:", 6, duty);
	if(motor1_DutyIn_HardwarePortAdress != 0)
	{
		data.Float = duty;
		Connecter_InputToHardwarePort(motor1_DutyIn_HardwarePortAdress, data);
	}
}

void Motor2_DutyIn(float duty, SetBy setter)
{
	if(motor2_DutyIn_State == Free)
		trgDuty[1] = duty;
	else if(motor2_DutyIn_State == ForceByHost && setter == MatStudio)
	{
		trgDuty[1] = duty;
	}
}

void Motor2_DutyOut(float duty)
{
	PWM_M2_set(duty);
	if(motor2_DutyOut_State == LookByHost)
		Connecter_SendFloat("Mm2;5:", 6, duty);
}

void Motor3_DutyIn(float duty, SetBy setter)
{
	if(motor3_DutyIn_State == Free)
		trgDuty[2] = duty;
	else if(motor3_DutyIn_State == ForceByHost && setter == MatStudio)
	{
		trgDuty[2] = duty;
	}
}

void Motor3_DutyOut(float duty)
{
	PWM_M3_set(duty);
	if(motor3_DutyOut_State == LookByHost)
		Connecter_SendFloat("Mm3;5:", 6, duty);
}

void Motor4_DutyIn(float duty, SetBy setter)
{
	if(motor4_DutyIn_State == Free)
		trgDuty[3] = duty;
	else if(motor4_DutyIn_State == ForceByHost && setter == MatStudio)
	{
		trgDuty[3] = duty;
	}
}

void Motor4_DutyOut(float duty)
{
	PWM_M4_set(duty);
	if(motor4_DutyOut_State == LookByHost)
		Connecter_SendFloat("Mm4;5:", 6, duty);
}

void Motor5_DutyIn(float duty, SetBy setter)
{
	if(motor5_DutyIn_State == Free)
		trgDuty[4] = duty;
	else if(motor5_DutyIn_State == ForceByHost && setter == MatStudio)
	{
		trgDuty[4] = duty;
	}
}

void Motor5_DutyOut(float duty)
{
	PWM_M5_set(duty);
	if(motor5_DutyOut_State == LookByHost)
		Connecter_SendFloat("Mm5;5:", 6, duty);
}

void Motor6_DutyIn(float duty, SetBy setter)
{
	if(motor6_DutyIn_State == Free)
		trgDuty[5] = duty;
	else if(motor6_DutyIn_State == ForceByHost && setter == MatStudio)
	{
		trgDuty[5] = duty;
	}
}

void Motor6_DutyOut(float duty)
{
	PWM_M6_set(duty);
	if(motor6_DutyOut_State == LookByHost)
		Connecter_SendFloat("Mm6;5:", 6, duty);
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


void _Motor_Do(_UBYTE module, _UBYTE command, _UBYTE* value)
{
	switch(module)
	{
		case '1':
			motor1_Do(command, value);
			break;

		case '2':
			motor2_Do(command, value);
			break;

		case '3':
			motor3_Do(command, value);
			break;

		case '4':
			motor4_Do(command, value);
			break;

		case '5':
			motor5_Do(command, value);
			break;

		case '6':
			motor6_Do(command, value);
			break;
		default:
			break;
	}
}

void motor1_Do(_UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 3:		// DutyIn_DL_Value
			Motor1_DutyIn(BitsToFloat(value), MatStudio);
			break;

		case 4:		// DutyOut_DL_State
			if(value[0] == 1)
				motor1_DutyOut_State = LookByHost;
			else
				motor1_DutyOut_State = Free;
			break;

		case 5:		// DutyOut_UP_Value
			Connecter_SendFloat("Mm1;5:", 6, trgDuty[0]);
			break;

		case 6:		// DutyOut_DL_ConnectToHardwarePort
			motor1_DutyIn_HardwarePortAdress = BitsToInt(value);
			if(value == '0')
				DataLogger1_LoggingStop();
			else
				DataLogger1_LoggingStart();
			break;

		default:
			break;
	}
}

void motor2_Do(_UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 3:		// DutyIn_DL_Value
			Motor2_DutyIn(BitsToFloat(value), MatStudio);
			break;

		case 4:		// DutyOut_DL_State
			if(value[0] == 1)
				motor2_DutyOut_State = LookByHost;
			else
				motor2_DutyOut_State = Free;
			break;

		case 5:		// DutyOut_UP_Value
			Connecter_SendFloat("Mm2;5:", 6, trgDuty[1]);
			break;

		default:
			break;
	}
}

void motor3_Do(_UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 3:		// DutyIn_DL_Value
			Motor3_DutyIn(BitsToFloat(value), MatStudio);
			break;

		case 4:		// DutyOut_DL_State
			if(value[0] == 1)
				motor3_DutyOut_State = LookByHost;
			else
				motor3_DutyOut_State = Free;
			break;

		case 5:		// DutyOut_UP_Value
			Connecter_SendFloat("Mm3;5:", 6, trgDuty[2]);
			break;

		default:
			break;
	}
}

void motor4_Do(_UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 3:		// DutyIn_DL_Value
			Motor4_DutyIn(BitsToFloat(value), MatStudio);
			break;

		case 4:		// DutyOut_DL_State
			if(value[0] == 1)
				motor4_DutyOut_State = LookByHost;
			else
				motor4_DutyOut_State = Free;
			break;

		case 5:		// DutyOut_UP_Value
			Connecter_SendFloat("Mm4;5:", 6, trgDuty[3]);
			break;

		default:
			break;
	}
}

void motor5_Do(_UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 3:		// DutyIn_DL_Value
			Motor5_DutyIn(BitsToFloat(value), MatStudio);
			break;

		case 4:		// DutyOut_DL_State
			if(value[0] == 1)
				motor5_DutyOut_State = LookByHost;
			else
				motor5_DutyOut_State = Free;
			break;

		case 5:		// DutyOut_UP_Value
			Connecter_SendFloat("Mm5;5:", 6, trgDuty[4]);
			break;

		default:
			break;
	}
}

void motor6_Do(_UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 3:		// DutyIn_DL_Value
			Motor6_DutyIn(BitsToFloat(value), MatStudio);
			break;

		case 4:		// DutyOut_DL_State
			if(value[0] == 1)
				motor6_DutyOut_State = LookByHost;
			else
				motor6_DutyOut_State = Free;
			break;

		case 5:		// DutyOut_UP_Value
			Connecter_SendFloat("Mm6;5:", 6, trgDuty[5]);
			break;

		default:
			break;
	}
}
