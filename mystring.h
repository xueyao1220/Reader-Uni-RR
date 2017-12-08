//==============================================================================
//
// Title:		mystring.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 16:03:48 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __mystring_H__
#define __mystring_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

char *stpcpy(char *dest, const char *src);
char *strncpynul(char *dest, const char *src, int num);
void strncpynulset(char *dest, const char *src, int num);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __mystring_H__ */
