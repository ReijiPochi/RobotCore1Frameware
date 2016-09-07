/*
 * DataLogger.h
 *
 *  Created on: 2016/09/07
 *      Author: Matsutomo2
 */

#include "..\typedefine.h"
#include "..\matSystem\Connecter.h"

#ifndef MODULES_DATALOGGER_H_
#define MODULES_DATALOGGER_H_


#ifdef __cplusplus
extern "C" {
#endif


void DataLogger_Activate(void);

void _DataLogger_Loop(void);

void _DataLogger_Do(_UBYTE module, _UBYTE command, _UBYTE* value);

void DataLogger1_LoggingStart(void);

void DataLogger1_LoggingStop(void);

void DataLogger1_DataIn(DataValue data);

void DataLogger_Log(_UBYTE adress, DataValue data);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_DATALOGGER_H_ */
