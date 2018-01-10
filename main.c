//==============================================================================
//
// Title:		main.c
// Purpose:		A short description of the implementation.
//
// Created on:	08.12.2017 at 10:40:40 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "main.h"
#include "Yao_Reader.h"
#include <rs232.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "toolbox.h"   
#include "ini.h"
#include "IniItems.h"
#include "main.h"  


//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
/// HIFN The main entry-point function.

 void Main_vInit(void)
{
   int iFileSize;
   
   Ini_srBuildFilePath(INI_DATA_PATH, INI_DATA_PREFIX, INI_DATA_EXT, MAIN_INIPATHLENGTH, sIniE.szIniFilePath);
   
   Ini_iGetString(sIniE.szIniFilePath, INI_SEC_FOLDERS, INI_KEY_REFFILE, MAIN_INIPATHLENGTH, sIniE.szArtDir);
//   Ini_srBuildFilePath(INI_REF_PATH, "", "", MAIN_INIPATHLENGTH, sIniE.szArtDir);

   if(FileExists(sIniE.szIniFilePath, &iFileSize) <= 0)
      Ini_srCreateDefaultIniFile(sIniE.szIniFilePath);
}
