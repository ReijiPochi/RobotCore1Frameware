/*
 * DAC.h
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */

#ifndef MODULES_ANALOGOUT_H_
#define MODULES_ANALOGOUT_H_


#ifdef __cplusplus
extern "C" {
#endif


void AnalogOUT_Activate(void);

void AnalogOUT1_SetVoltage(float volts);

void AnalogOUT2_SetVoltage(float volts);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_ANALOGOUT_H_ */
