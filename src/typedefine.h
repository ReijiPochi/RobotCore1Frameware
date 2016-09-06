/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  RobotCore1Framework                    */
/*      FILE         :  typedefine.h                           */
/*      DESCRIPTION  :  Aliases of Integer Type                */
/*      CPU SERIES   :  RX600                                  */
/*      CPU TYPE     :  RX63T                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                              
                                                                           
                                                                           
                                                                           
                                                                            
/*********************************************************************
*
* Device     : RX
*
* File Name  : typedefine.h
*
* Abstract   : Aliases of Integer Type.
*
* History    : 1.00  (2009-08-07)
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2009 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
*
*********************************************************************/

#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

typedef signed char _SBYTE;
typedef unsigned char _UBYTE;
typedef signed short _SWORD;
typedef unsigned short _UWORD;
typedef signed int _SINT;
typedef unsigned int _UINT;
typedef signed long _SDWORD;
typedef unsigned long _UDWORD;
typedef signed long long _SQWORD;
typedef unsigned long long _UQWORD;

typedef enum
{
	ForceByHost     		= 0x0,
	LookByHost      		= 0x1,
	Free            		= 0x2,
	ConnectToHardwarePort 	= 0x3
} ModulePortState;

typedef enum
{
	RobotCore		= 0x0,
	MatStudio		= 0x1
} SetBy;

typedef enum
{
	False			= 0x0,
	True			= 0x1
} BOOL;

#endif

