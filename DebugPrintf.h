//==============================================================================
//
// Title:		DebugPrintf.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 14:49:49 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __DebugPrintf_H__
#define __DebugPrintf_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
		
#include "feotypes.h"
#include "timer.h"
#include <stdlib.h>

//==============================================================================
// Constants

		
#define DIR_DELIM          	"\\"
#define DIR_DELIMCHAR      '\\'
#define ROOT_DIR           "\\work\\aesculap\\Aesculap_Prüfsystem_50829_SW\\"	 


#define LOGFILES_DIR        ROOT_DIR"LOG"DIR_DELIM


int iLogfileLock;		

// log file, for testing only!
// 0: no log file (normal case)
// 1: activate ERR_ and dbg1+3 (full log file)
// 2: activate ERR_ and dbg2 (minimalist log file)
// 3: activate ERR_ and dbg3 ()
#define DEBUG_LOGFILE 1  // normally 0


//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

#if (DEBUG_LOGFILE)
 #include <stdio.h>
 FILE *logfp;
 #define dbgx(_s)  do { CmtGetLock(iLogfileLock);\
                        fprintf(logfp,"%s, L:%4d, T:%.3f ", __FILE__, __LINE__, Timer());\
                        fprintf _s ;\
                        CmtReleaseLock(iLogfileLock);\
                      } while(0)
                      
 #define ERR_(_s)  do { CmtGetLock(iLogfileLock);\
                        fprintf(logfp,"ERR %s, L:%4d, T:%.3f ", __FILE__, __LINE__, Timer());\
                        fprintf _s ;\
                        CmtReleaseLock(iLogfileLock);\
                      } while(0)
 #if (DEBUG_LOGFILE==1)
  #define dbg1(_s)  dbgx(_s)
  #define dbg2(_s)
  #define dbg3(_s)  dbgx(_s)
 #elif (DEBUG_LOGFILE==2) // minimalist
  #define dbg1(_s)
  #define dbg2(_s)  CmtGetLock(iLogfileLock); fprintf(logfp,"%s, L:%4d, %lu, %s\n", __FILE__, __LINE__, Timer(), _s); CmtReleaseLock(iLogfileLock)
  #define dbg3(_s)
 #elif (DEBUG_LOGFILE==3) // virtual speed
  #define dbg1(_s)
  #define dbg2(_s)
  #define dbg3(_s)  dbgx(_s)
 #endif
#else
 // no log file at all
 #define dbg1(_s)
 #define dbg2(_s)
 #define dbg3(_s)
 #define ERR_(_s)
#endif

int Declare_Your_Functions_Here (int x);
void OpenLogFile(void);
void CloseLogFile(void);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DebugPrintf_H__ */
