//==============================================================================
//
// Title:		IniItems.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 16:02:55 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __IniItems_H__
#define __IniItems_H__

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

#define SECT   1
#define KEY    2

#define INI_TYPE_NONE      0
#define INI_TYPE_STRING    1
#define INI_TYPE_INT       2

#define INI_DEF_NETDEVICE     "C:\work\aesculap\Aesculap_Prüfsystem_50829_SW\Netzlaufwerk_M"
// device data files
#define INI_DATA_PATH         "./"
#define INI_DATA_PREFIX       "SDCARD"    // data file names have this prefix, followed by hex SerNum
#define INI_DATA_EXT          ".ini"      //  ... and this file extension
#define INI_DATA_EXT_BAK      ".bak"

#define INI_REF_PATH          "../../Netzlaufwerk_M/"          // Root directory of the ref file
#define INI_REF_EXT           ".ref"      //  ... and this file extension
#define INI_REF_EXT_BAK       ".bak"      

#define INI_DIR_DELIM         "/"

#define INI_EXT_LENGTH        4

//Sections
#define INI_SEC_PORTS      "PORTS"
#define INI_SEC_LOGLEVEL   "LOG"
#define INI_SEC_FOLDERS    "FOLDERS"
#define INI_SEC_USERCONF   "USERCONFIG"
#define INI_SEC_USERS      "USERS"
#define INI_SEC_PSWD       "PASSWORDS"
#define INI_SEC_ARTNUMS    "ARTNUMBERS"

#define INI_KEY_HM30PORT         "HM30PORT"
#define INI_KEY_DEVICEPORT       "DEVICEPORT"
#define INI_KEY_MICROSCANPORT    "MICROSCANPORT"
#define INI_KEY_LOGGINGLEVEL     "LOGGINGLEVEL"
#define INI_KEY_REFFILE          "REFFILE"
#define INI_KEY_LOGFOLDER        "LOGFOLDER"
#define INI_KEY_CALDATFOLDER     "CALDATFOLDER"
#define INI_KEY_LASTUSER         "LASTUSER"
#define INI_KEY_USER             "USER"
#define INI_KEY_PSWD             "PSWD"
#define INI_KEY_ARTNUM           "ARTNUM"   
#define INI_KEY_KENNFOLDER       "KENNFOLDER"
#define INI_KEY_ARTNUMCALDAT     "ARTNUMCALDAT"

#define INI_KEY_HM30PORT_DEFVAL      13
#define INI_KEY_DEVICEPORT_DEFVAL    3
#define INI_KEY_PRINTERPORT_DEFVAL   4
#define INI_KEY_MICROSCANPORT_DEFVAL 4
#define INI_KEY_LOGGINGLEVEL_DEFVAL  2
#define INI_KEY_REFFILE_DEFVAL       "C:/work/Aesculap/"
#define INI_KEY_LOGFOLDER_DEFVAL     "C:/work/Aesculap/"
#define INI_KEY_CALDATFOLDER_DEFVAL  "C:/work/Aesculap/"
#define INI_KEY_KENNFOLDER_DEFVAL    "C:/work/Aesculap/"
#define INI_KEY_LASTUSER_DEFVAL      0
#define INI_KEY_USER_DEFVAL          Administrator
#define INI_KEY_PSWD_DEFVAL          admin
#define INI_KEY_ARTNUM_DEFVAL        Auswaehlen
#define INI_KEY_ARTNUMCALDAT_DEFAULT FV909X

#define INI_DEF_FILE "["INI_SEC_PORTS"]\r\n"\
                     INI_KEY_HM30PORT"="STR(INI_KEY_HM30PORT_DEFVAL)"\r\n"\
                     INI_KEY_DEVICEPORT"="STR(INI_KEY_DEVICEPORT_DEFVAL)"\r\n"\
                     INI_KEY_MICROSCANPORT"="STR(INI_KEY_MICROSCANPORT_DEFVAL)"\r\n"\
                     "["INI_SEC_LOGLEVEL"]\r\n"\
                     INI_KEY_LOGGINGLEVEL"="STR(INI_KEY_LOGGINGLEVEL_DEFVAL)"\r\n\r\n"\
                     "["INI_SEC_FOLDERS"]\r\n"\
                     INI_KEY_REFFILE"="STR(INI_KEY_REFFILE_DEFVAL)"\r\n"\
                     INI_KEY_LOGFOLDER"="STR(INI_KEY_LOGFOLDER_DEFVAL)"\r\n\r\n"\
                     INI_KEY_CALDATFOLDER"="STR(INI_KEY_CALDATFOLDER_DEFVAL)"\r\n\r\n"\
                     INI_KEY_KENNFOLDER"="STR(INI_KEY_KENNFOLDER_DEFVAL)"\r\n\r\n"\
                     INI_KEY_ARTNUMCALDAT"="STR(INI_KEY_ARTNUMCALDAT_DEFAULT)"\r\n\r\n"\
                     "["INI_SEC_USERCONF"]\r\n"\
                     INI_KEY_LASTUSER"="STR(INI_KEY_LASTUSER_DEFVAL)"\r\n\r\n"\
                     "["INI_SEC_USERS"]\r\n"\
                     INI_KEY_USER"0="STR(INI_KEY_USER_DEFVAL)"\r\n\r\n"\
                     "["INI_SEC_PSWD"]\r\n"\
                     INI_KEY_PSWD"0="STR(INI_KEY_PSWD_DEFVAL)"\r\n\r\n"\
                     "["INI_SEC_ARTNUMS"]\r\n"\
                     INI_KEY_ARTNUM"0="STR(INI_KEY_ARTNUM_DEFVAL)"\r\n"
                     

#define INI_KEY_
#define INI_KEY_
#define INI_KEY_


#define REF_SEC_TIME             "TIME"
#define REF_SEC_LABEL            "LABEL"
#define REF_SEC_VERSION          "VERSION"
#define REF_SEC_BORDERS          "BORDERS"
#define REF_SEC_BARDVARIANCES    "BARDVARIANCES"
#define REF_SEC_METEOSDVARIANCES "METEOSDVARIANCES"
#define REF_SEC_CURRENT          "CURRENT"
#define REF_SEC_TIME             "TIME"
#define REF_SEC_RAWVALUES        "RAWVALUES"
#define REF_SEC_COEFFVARIANCES   "COEFFVARIANCES"
#define REF_SEC_

#define REF_KEY_WARMUPMETEO      "WARMUPMETEO"
#define REF_KEY_SAMPLEFILE       "SAMPLEFILE"
#define REF_KEY_NUMBER           "NUMBER"
#define REF_KEY_VALIDMIN         "VALIDMIN"
#define REF_KEY_VALIDMAX         "VALIDMAX"
#define REF_KEY_TEMPMINVALUE     "TEMPMINVALUE"
#define REF_KEY_TEMPMAXVALUE     "TEMPMAXVALUE"
#define REF_KEY_PRESSMINVALUE    "PRESSMINVALUE"
#define REF_KEY_PRESSMAXVALUE    "PRESSMAXVALUE"
#define REF_KEY_TEMPMIN          "TEMPMIN"
#define REF_KEY_TEMPMAX          "TEMPMAX"
#define REF_KEY_PRESSMIN         "PRESSMIN"
#define REF_KEY_PRESSMAX         "PRESSMAX"
#define REF_KEY_RAWMIN           "MIN"
#define REF_KEY_RAWLOWMID        "LOWMID"
#define REF_KEY_RAWHIGHMID       "HIGHMID"
#define REF_KEY_RAWMAX           "MAX"
#define REF_KEY_RAWTEMP          "TEMP"
#define REF_KEY_
#define REF_KEY_
#define REF_KEY_
#define REF_KEY_

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __IniItems_H__ */
