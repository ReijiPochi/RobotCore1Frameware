/*
 * IO.h
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */

#include "..\..\typedefine.h"

#ifndef MODULES_MICON_IO_H_
#define MODULES_MICON_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

void IO_LED_init();

void LED_STATUS_R(_UBYTE value);
void LED_STATUS_G(_UBYTE value);
void LED_STATUS_B(_UBYTE value);
void LED_INFO(_UBYTE value);
void LED_ERROR(_UBYTE value);

void IO_Motor_Init();

_UBYTE ALERT(void);
void STBY(_UBYTE value);

void Motor1_MODE(_UBYTE m1, _UBYTE m2);
void Motor2_MODE(_UBYTE m1, _UBYTE m2);
void Motor3_MODE(_UBYTE m1, _UBYTE m2);
void Motor4_MODE(_UBYTE m1, _UBYTE m2);
void Motor5_MODE(_UBYTE m1, _UBYTE m2);
void Motor6_MODE(_UBYTE m1, _UBYTE m2);

void IO_DIO_Init(IOMode dio1, IOMode dio2, IOMode dio3, IOMode dio4);

void DIO_1_Out(_UBYTE value);
void DIO_2_Out(_UBYTE value);
void DIO_3_Out(_UBYTE value);
void DIO_4_Out(_UBYTE value);
LogicLevel DIO_3_In(void);

void IO_Multi1_Init(IOMode multi1_1, IOMode multi1_2, IOMode multi1_3);

void Multi1_1_Out(LogicLevel value);
void Multi1_2_Out(LogicLevel value);
void Multi1_3_Out(LogicLevel value);

#ifdef __cplusplus
}
#endif

#endif /* MODULES_MICON_IO_H_ */
