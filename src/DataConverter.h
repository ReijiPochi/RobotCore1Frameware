/*
 * DataConverter.h
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */

#include "typedefine.h"

#ifndef DATACONVERTER_H_
#define DATACONVERTER_H_


#ifdef __cplusplus
extern "C" {
#endif


_SWORD StringToWORD(_UBYTE* string, _UBYTE count);
float BitsToFloat(_UBYTE* bits);
_SWORD BitsToInt(_UBYTE* bits);
_UBYTE* FloatToBits(float value);
_UBYTE* IntToBits(_SDWORD value);


#ifdef __cplusplus
}
#endif


#endif /* DATACONVERTER_H_ */
