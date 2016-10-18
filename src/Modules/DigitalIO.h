/*
 * DigitalIO.h
 *
 *  Created on: 2016/09/13
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"





#ifndef MODULES_DIGITALIO_H_
#define MODULES_DIGITALIO_H_



#ifdef __cplusplus
extern "C" {
#endif

void DIO_Activate(IOMode dio1, IOMode dio2, IOMode dio3, IOMode dio4);

void _DIO_Loop(void);

void DIO_SetInterrupt(InterruptCallback callback);

void DIO1_On(void);
void DIO1_Off(void);

void DIO2_On(void);
void DIO2_Off(void);

void DIO3_On(void);
void DIO3_Off(void);

void DIO4_On(void);
void DIO4_Off(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_DIGITALIO_H_ */
