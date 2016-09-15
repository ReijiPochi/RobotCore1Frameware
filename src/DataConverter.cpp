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

_SWORD BitsToInt(_UBYTE* bits)
{
	_UDWORD data = 0, data1 = bits[0], data2 = bits[1], data3 = bits[2], data4 = bits[3];

	data = data1 | data2 << 8 | data3 << 16 | data4 << 24;

	return data;
}

DUALSHOCK3 BitsToDUALSHOCK3(_UBYTE* bits)
{
	DUALSHOCK3 data;

	data.Time = bits[0] | bits[1] << 8 | bits[2] << 16 | bits[3] << 24;
	data.Buttons.WORD = bits[4] | bits[5] << 8;
	data.AnalogL.X = bits[6];
	data.AnalogL.Y = bits[7];
	data.AnalogR.X = bits[8];
	data.AnalogR.Y = bits[9];

	return data;
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

_UBYTE intBytes[4];
_UBYTE* IntToBits(_SDWORD value)
{
	intBytes[0] = value & 0x000000FF;
	intBytes[1] = (value & 0x0000FF00) >> 8;
	intBytes[2] = (value & 0x00FF0000) >> 16;
	intBytes[3] = (value & 0xFF000000) >> 24;

	return intBytes;
}
