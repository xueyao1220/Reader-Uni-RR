//==============================================================================
//
// Title:		ini.c
// Purpose:		A short description of the implementation.
//
// Created on:	08.12.2017 at 15:59:49 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <windows.h>


#include "ini.h"
#include "IniItems.h"
#include "mystring.h"
#include "retvalnew.h"   

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
#define MAIN_USERNAMELENGTH   64
#define MAIN_MAXUSERS         100

#define MAIN_PSWDLENGTH       64
#define MAIN_INIPATHLENGTH    128

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
sIni_t sIniE;

sregt Ini_srCryptStr(char *pcSrc, char *pcDest)
{
   uint16 uiCnt = 0;
   
   if(!pcSrc || !pcDest)
      return E_NULLPTR;
      
   while(*pcSrc != '\0')
   {
      //"de-/encryption"
      *pcDest++ = *pcSrc++ ^ 0xff;
      //string is to long?
      if(uiCnt>MAIN_USERNAMELENGTH)
         return ERR;
      uiCnt++;
   }
   return OK;
}

//-----------------------------------------------------------------------------
// FUNCTION: Ini_srBuildFilePath
//
// DESCRIPTION:
//    Build up the Pathstring
//
// PARAMETERS: 
//    void
//
// RETURNS: void
//
// VERSION DATE         AUTHOR     CHANGES
// VER     18.08.2008   R.Merkt    creation
//-----------------------------------------------------------------------------
sregt Ini_srBuildFilePath(char *pszFilePath, char *pszFilename, char *pszExtension, uint16 uiLength, char *pszCompleteName)
{
   if(!pszFilePath || !pszFilename || !pszExtension || !pszCompleteName)
      return E_NULLPTR;

   //to avoid copying too long Pathnames
   if((strlen(pszFilePath) >= uiLength-(INI_EXT_LENGTH+strlen(pszFilename)+1) ||
      (strlen(pszFilename) >= uiLength-(INI_EXT_LENGTH+strlen(pszFilePath)+1))))
      return ERR;
      
   strncpy(pszCompleteName, pszFilePath, uiLength-(INI_EXT_LENGTH+strlen(pszFilename)+1));   //1 is added to extension length for the terminator
   strncat(pszCompleteName, pszFilename, uiLength-(INI_EXT_LENGTH+1));                       //1 is added to extension length for the terminator
   strncat(pszCompleteName, pszExtension, INI_EXT_LENGTH);                                   //adds terminator automaticly
   
   return OK;
}

//-----------------------------------------------------------------------------
// FUNCTION: Ini_srCreateDefaultIniFile
//
// DESCRIPTION:
//    Re-/Creates the Ini-File and fills it with default Values.
//    ATTENTION. all Users, exept the Administartor will be deleted.
//
// PARAMETERS: 
//    void
//
// RETURNS: void
//
// VERSION DATE         AUTHOR     CHANGES
// VER     18.08.2008   R.Merkt    creation
//-----------------------------------------------------------------------------
sregt Ini_srCreateDefaultIniFile(const char *pszFilePath)
{
   FILE *pFile;
   char acNrmPswd[MAIN_PSWDLENGTH], acCryptPswd[MAIN_PSWDLENGTH], acKey[8];
   
   memset( acNrmPswd, 0, MAIN_PSWDLENGTH);
   memset( acCryptPswd, 0, MAIN_PSWDLENGTH);
   
   //Delete old IniFile and create the new one
   pFile = fopen(pszFilePath, "wb");
   
   //Now fill it with default values
   fprintf(pFile, INI_DEF_FILE);
   
   fclose(pFile);
   
   //Stored Pswd must be encrypted
   //Build the Key
   sprintf(acKey,"%s0", INI_KEY_PSWD);
   Ini_iGetString(pszFilePath, INI_SEC_PSWD, acKey, MAIN_PSWDLENGTH, acNrmPswd);
   Ini_srCryptStr(acNrmPswd, acCryptPswd);
   Ini_srWriteStringToIniFile(pszFilePath, INI_SEC_PSWD, acKey, acCryptPswd);
   return OK;
}

//-----------------------------------------------------------------------------
// FUNCTION: Ini_bSectionExists
//
// DESCRIPTION:
//    function only used in case of writing a new value to avoid making a new Section
//
// PARAMETERS: 
//    void
//
// RETURNS: void
//
// VERSION DATE         AUTHOR     CHANGES
// VER     18.08.2008   R.Merkt    creation
//-----------------------------------------------------------------------------
static bool Ini_bSectionExists(const char *pszFilename, const char *pszSection)
{
   //TODO fill function
   return TRUE;
}

//-----------------------------------------------------------------------------
// FUNCTION: Ini_bKeyExists
//
// DESCRIPTION:
//    function only used in case of writing a new value to avoid making a new Key
//
// PARAMETERS: 
//    void
//
// RETURNS: void
//
// VERSION DATE         AUTHOR     CHANGES
// VER     18.08.2008   R.Merkt    creation
//-----------------------------------------------------------------------------
static bool Ini_bKeyExists(const char *pszFilename, const char *pszSection, const char *pszKey)
{
   //TODO fill function
   return TRUE;
}

//-----------------------------------------------------------------------------
// Read from .ini files
int Ini_iGetFloat(const char *pszFilePath, const char *pszSection, const char *pszKey, float *pf)
{
   DWORD dwRet;
   char cBuf[32];

   dwRet = GetPrivateProfileString(pszSection, pszKey, "", cBuf, 32, pszFilePath);
   if(!dwRet || cBuf[0] == '\0')
      return FALSE; // empty or error
   if(pf)
      sscanf(cBuf, "%f",pf); 
   return TRUE; // ok
}

int Ini_iGetUint32(const char *pszFilePath, const char *pszSection, const char *pszKey, uint32 *pul)
{
   UINT uValue;

   uValue = GetPrivateProfileInt(pszSection, pszKey, 0xFFFFFFFF, pszFilePath);
   if(uValue == 0xFFFFFFFF)
      return FALSE; // error
   if(pul)
      *pul = (uint32)uValue;
   return TRUE; // ok
}
int Ini_iGetInt32(const char *pszFilePath, const char *pszSection, const char *pszKey, int *pi)
{
   int iValue;
   iValue = GetPrivateProfileInt(pszSection, pszKey, -8000000000, pszFilePath);
   if(iValue == -8000000000)
      return FALSE; // error
   if(pi)
      *pi = (int)iValue;
   return TRUE; // ok
   
}

int Ini_iGetUint16(const char *pszFilePath, const char *pszSection, const char *pszKey, uint16 *pui)
{
   UINT uValue;

   uValue = GetPrivateProfileInt(pszSection, pszKey, 0x10000, pszFilePath);
   if(uValue > 0xFFFFu)
      return FALSE; // error
   if(pui)
      *pui = (uint16)uValue;
   return TRUE; // ok
}

int Ini_iGetInt16(const char *pszFilePath, const char *pszSection, const char *pszKey, int16 *pi)
{
   UINT uValue;
   int32 lValue;

   uValue = GetPrivateProfileInt(pszSection, pszKey, 0x10000, pszFilePath);
   lValue = (int32)uValue;
   if(lValue > 32767l || lValue < -32768l)
      return FALSE; // error
   if(pi)
      *pi = (int16)lValue;
   return TRUE; // ok
}

int Ini_iGetUchar(const char *pszFilePath, const char *pszSection, const char *pszKey, uchar *puc)
{
   UINT uValue;

   uValue = GetPrivateProfileInt(pszSection, pszKey, 0x100, pszFilePath);
   if(uValue > 0xFFu)
      return FALSE; // error
   if(puc)
      *puc = (uchar)uValue;
   return TRUE; // ok
}

int Ini_iGetString(const char *pszFilePath, const char *pszSection, const char *pszKey, int iSize, char *psz)
{
   DWORD dwRet;
   char cBuf[512];

   if(iSize > sizeof(cBuf))
      iSize = sizeof(cBuf);
   dwRet = GetPrivateProfileString(pszSection, pszKey, "", cBuf, iSize, pszFilePath);
   if(!dwRet || cBuf[0] == '\0')
      return FALSE; // empty or error
   if(psz)
      stpcpy(psz, cBuf);
   return TRUE; // ok
}

sregt Ini_srWriteNewUserToIniFile(const char *pszFileName, const char *pszUser, const char *pszPswd)
{
   uint16 uiIdx;
   char caKey[8];
   //Get Idx of last user
   for(uiIdx = 0; uiIdx < MAIN_MAXUSERS; uiIdx++)
   {
      sprintf(caKey,"%s%i",INI_KEY_USER, uiIdx);
      if(!Ini_bKeyExists(pszFileName, INI_SEC_USERS, caKey))
         break;
   }
   
   Ini_srWriteStringToIniFile(pszFileName, INI_SEC_USERS, caKey, pszUser);
   
   sprintf(caKey,"%s%i",INI_KEY_PSWD, uiIdx);
   Ini_srWriteStringToIniFile(pszFileName, INI_SEC_PSWD, caKey, pszPswd);
   return OK;
}
sregt Ini_srChangeUserPassword(const char *pszFileName, const char *pszUser, const char *pszOldPswd, const char *pszNewPswd)
{
   //TODO fill function
   return OK;
}
sregt Ini_srWriteUint16ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, uint16 uiValue)
{
   char caValue[16];
   sregt srError = OK;
   
   sprintf(caValue, "%d", uiValue);
   if(WritePrivateProfileString(pszSection, pszKey, caValue, pszFileName) == 0)
      srError = GetLastError();
      
   return srError;
}
sregt Ini_srWriteInt16ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, int16 iValue)
{
   char caValue[16];
   sregt srError = OK;
   
   sprintf(caValue, "%d", iValue);
   if(WritePrivateProfileString(pszSection, pszKey, caValue, pszFileName) == 0)
      srError = GetLastError();
      
   return srError;
}
sregt Ini_srWriteUint32ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, uint32 ulValue)
{
   char caValue[16];
   sregt srError = OK;
   
   sprintf(caValue, "%d", ulValue);
   if(WritePrivateProfileString(pszSection, pszKey, caValue, pszFileName) == 0)
      srError = GetLastError();
      
   return srError;
}
sregt Ini_srWriteInt32ToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, int32 lValue)
{
   char caValue[16];
   sregt srError = OK;
   
   sprintf(caValue, "%d", lValue);
   if(WritePrivateProfileString(pszSection, pszKey, caValue, pszFileName) == 0)
      srError = GetLastError();
      
   return srError;
}
sregt Ini_srWriteDoubleToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, double dValue)
{
   char caValue[16];
   sregt srError = OK;
   
   sprintf(caValue, "%8.8f", dValue);
   if(WritePrivateProfileString(pszSection, pszKey, caValue, pszFileName) == 0)
      srError = GetLastError();
      
   return srError;
}
sregt Ini_srWriteStringToIniFile(const char *pszFileName, const char *pszSection, const char *pszKey, const char * pszValue)
{
   sregt srError = OK;
   
   if(WritePrivateProfileString(pszSection, pszKey, pszValue, pszFileName) == 0)
      srError = GetLastError();
      
   return srError;
}
