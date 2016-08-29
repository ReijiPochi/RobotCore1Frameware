/*
 * MotorPWM.h
 *
 *  Created on: 2016/08/15
 *      Author: Reiji
 */

#ifndef MODULES_MOTORPWM_H_
#define MODULES_MOTORPWM_H_


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
 *  MotorPWM1モジュールを使用可能にします。
 */
void MotorPWM1_Activate(void);

/**
 *  MotorPWM1モジュールのPWM値を設定します。
 *
 *  @param duty デューティー比　( 0 ～ 1.0の値 )
 */
void MotorPWM1_SetPWM(float duty);

/**
 *  MotorPWM1モジュールのモード (正転、逆転、ブレーキ、開放) を設定します。
 */
void MotorPWM1_SetMode(MotorMode mode);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_MOTORPWM_H_ */
