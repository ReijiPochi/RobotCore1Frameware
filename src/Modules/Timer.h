/*
 * Timer.h
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "..\typedefine.h"

#ifndef MODULES_TIMER_H_
#define MODULES_TIMER_H_


typedef enum
{
	TimerClock_8	= 8,
	TimerClock_32	= 32,
	TimerClock_128	= 128,
	TimerClock_512	= 512
} TimerClock;


#ifdef __cplusplus
extern "C" {
#endif


void _Timer_Activate(void);

void _Timer1_Set(TimerClock clock, _UDWORD interval, void (*callback)(void));

void _Timer1_Start(void);

void _Timer1_Stop(void);

void Timer2_Set(TimerClock clock, _UDWORD interval, void (*callback)(void));

void Timer2_Start(void);

void Timer2_Stop(void);


#ifdef __cplusplus
}
#endif

#endif /* MODULES_TIMER_H_ */
