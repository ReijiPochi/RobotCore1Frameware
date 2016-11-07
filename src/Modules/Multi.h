/*
 * Multi.h
 *
 *  Created on: 2016/10/16
 *      Author: Reiji
 */

#include "..\typedefine.h"

typedef enum
{
	AllIO,
	Motor
} MultiMode;

#ifndef MODULES_MULTI_H_
#define MODULES_MULTI_H_


#ifdef __cplusplus
extern "C" {
#endif


void Multi1_Activate(MultiMode mode);

void Multi1_DOUT1(LogicLevel value);

void Multi1_DOUT2(LogicLevel value);

void Multi1_DOUT3(LogicLevel value);


#ifdef __cplusplus
}
#endif

#endif /* MODULES_MULTI_H_ */
