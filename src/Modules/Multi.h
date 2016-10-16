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


void Multi_Activate(MultiMode m1, MultiMode m2);

void Multi_DOUT1(LogicLevel value, _SBYTE module);

void Multi_DOUT2(LogicLevel value,_SBYTE module);

void Multi_DOUT3(LogicLevel value,_SBYTE module);


#endif /* MODULES_MULTI_H_ */
