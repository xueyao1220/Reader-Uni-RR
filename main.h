//==============================================================================
//
// Title:		main.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 10:40:40 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __main_H__
#define __main_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

#define MAIN_MAXUSERS         100
#define MAIN_USERNAMELENGTH   64
#define MAIN_PSWDLENGTH       64
#define MAIN_INIPATHLENGTH    128

#define MAIN_MAXLOGINERRORS   3

#define MAX_NUM_OFTHREADS     100

#define MAIN_MAXARTICLENOLENGTH  32
#define MAIN_MAXARTICLENO        100

#define CALDAT_SIZE_IN_BYTES  16348

#define HM30      1
#define ABLAUF    1
#define FV900X    1
//==============================================================================
// Types

//==============================================================================
// External variables
		





//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);

void Main_vInit(void);  

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */
