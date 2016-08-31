/*
 * MotorPWM.h
 *
 *  Created on: 2016/08/15
 *      Author: Reiji
 */

#ifndef MODULES_MOTOR_H_
#define MODULES_MOTOR_H_


typedef enum
{
	MotorMode_CW,
	MotorMode_CCW,
	MotorMode_BRAKE,
	MotorMode_FREE
} MotorMode;


#ifdef __cplusplus
extern "C" {
#endif


/**
 *  Motorモジュールを使用可能にします。
 */
void Motor_Activate(void);

void Motor_UnlockSTBY(void);

void Motor_LockSTBY(void);

void _Motor_Loop(void);


void Motor1_SetPWM(float duty);
void Motor2_SetPWM(float duty);
void Motor3_SetPWM(float duty);
void Motor4_SetPWM(float duty);
void Motor5_SetPWM(float duty);
void Motor6_SetPWM(float duty);



#ifdef __cplusplus
}
#endif


#endif /* MODULES_MOTOR_H_ */
