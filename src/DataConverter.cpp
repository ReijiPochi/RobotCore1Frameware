/*
 * DataConverter.cpp
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */


#include "DataConverter.h"

static _UBYTE IntParse(_UBYTE _char);

union IntFloat
{
	_UDWORD Int;
	float Float;
};


_UBYTE IntParse(_UBYTE _char)
{
	switch(_char)
	{
		case '0':
			return 0;

		case '1':
			return 1;

		case '2':
			return 2;

		case '3':
			return 3;

		case '4':
			return 4;

		case '5':
			return 5;

		case '6':
			return 6;

		case '7':
			return 7;

		case '8':
			return 8;

		case '9':
			return 9;
	}

	return 0;
}


_SWORD StringToWORD(_UBYTE* string, _UBYTE count)
{
	_SWORD value = 0;
	_SWORD digit = 1;
	_SBYTE i;

	for(i = count - 1; i >= 0; i--)
	{
		value += IntParse(string[i]) * digit;
		digit *= 10;
	}

	return value;
}

float BitsToFloat(_UBYTE* bits)
{
	IntFloat data;
	_UDWORD data1 = bits[0], data2 = bits[1], data3 = bits[2], data4 = bits[3];

	data.Int = 0;
	data.Int = data1 | data2 << 8 | data3 << 16 | data4 << 24;

	return data.Float;
}

_UBYTE bytes[4];

_UBYTE* FloatToBits(float value)
{
	IntFloat data;
	data.Float = value;

	bytes[0] = data.Int & 0x000000FF;
	bytes[1] = (data.Int & 0x0000FF00) >> 8;
	bytes[2] = (data.Int & 0x00FF0000) >> 16;
	bytes[3] = (data.Int & 0xFF000000) >> 24;

	return bytes;
}
