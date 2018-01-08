//==============================================================================
//
// Title:		Ablauf.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 13:54:53 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __Ablauf_H__
#define __Ablauf_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "feotypes.h"  
		

		


//==============================================================================
// Constants
#define ABL_TESTNAMELENGTH    128
#define ABL_TESTHINTLENGTH    256
#define ABL_TESTINFOLENGTH    256
#define ABL_DEFSTRINGLENGTH   128
#define ABL_POPUPSTRINGLENGTH 256

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions



sregt Abl_srGetAsicIdFromTag(void);   
sregt Abl_srGetSerNr(void);   

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Ablauf_H__ */
