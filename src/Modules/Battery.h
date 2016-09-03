/*
 * Battery.h
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */

#ifndef MODULES_BATTERY_H_
#define MODULES_BATTERY_H_


#ifdef __cplusplus
extern "C" {
#endif


void _Battery_Activate(void);

void _Battery_Sample(void);

float _Battery_GetVoltage1(void);

float _Battery_GetVoltage2(void);

float _Battery_GetVoltage3(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_BATTERY_H_ */
