//==============================================================================
//
// Title:		ini.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 15:59:49 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __ini_H__
#define __ini_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "IniItems.h"
#include "feotypes.h"  
#include "fv900x.h" 
		

//==============================================================================
// Constants
#define MAX_DIR_NAME_LEN      256

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

typedef struct{
   char szIniFilePath[MAX_DIR_NAME_LEN];     //ini-File
   char szRefFileName[MAX_DIR_NAME_LEN];     //Ref File
   char szArtDir[MAX_DIR_NAME_LEN];          //ArticleDir
   char szLogFileDir[MAX_DIR_NAME_LEN];      //LogfileDir
   char szKennFolder[MAX_DIR_NAME_LEN];      //KENNFOLDER
   char szArtNumCaldat[MAX_DIR_NAME_LEN];    //ATRNUMCALDAT
} sIni_t;

extern sIni_t sIniE;

sregt Ini_srCryptStr(char *pcSrc, char *pcDest);


int Ini_iGetFloat(const char *pszFilePath, const char *pszSection, const char *pszKey, float *pf);
int Ini_iGetUint32(const char *pszFilePath, const char *pszSection, const char *pszKey, uint32 *pul);
int Ini_iGetInt32(const char *pszFilePath, const char *pszSection, const char *pszKey, int *pi);
int Ini_iGetUint16(const char *pszFilePath, const char *pszSection, const char *pszKey, uint16 *pui);
int Ini_iGetInt16(const char *pszFilePath, const char *pszSection, const char *pszKey, int16 *pi);
int Ini_iGetUchar(const char *pszFilePath, const char *pszSection, const char *pszKey, uchar *puc);
int Ini_iGetString(const char *pszFilePath, const char *pszSection, const char *pszKey, int iSize, char *psz);

sregt Ini_srBuildFilePath(char *pszFilePath, char *pszFilename, char *pszExtension, uint16 uiLength, char *pszCompleteName);
sregt Ini_srWriteUserToIniFile(const char *pszFilePath, const char *pszUser, const char *pszPswd);
sregt Ini_srCreateDefaultIniFile(const char *pszFilePath);

sregt Ini_srWriteUint16ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, uint16 uiValue);
sregt Ini_srWriteInt16ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, int16 iValue);
sregt Ini_srWriteUint32ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, uint32 ulValue);
sregt Ini_srWriteInt32ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, int32 lValue);
sregt Ini_srWriteDoubleToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, double dValue);
sregt Ini_srWriteStringToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, const char * pszValue);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __ini_H__ */
