//==============================================================================
//
// Title:		messages.h
// Purpose:		A short description of the interface.
//
// Created on:	11.01.2018 at 11:46:23 by  .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __messages_H__
#define __messages_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
		
#define MSG_NUMMESSAGES       54
#define MSG_MESSAGELENGTH     256


#define MSG_IDENTIFIETAG            pcMessages[1  ]
#define MSG_CHECKTAG                pcMessages[2  ]
#define MSG_FORMATSDCARD            pcMessages[3  ]
#define MSG_PLAUSICHECK             pcMessages[4  ]
#define MSG_ENVTAGCHECK             pcMessages[5  ]
#define MSG_PRINTLABEL              pcMessages[6  ]
#define MSG_BACKUPSD                pcMessages[7  ]
#define MSG_VERIFYSDLABEL           pcMessages[8  ]
#define MSG_NOTTESTED               pcMessages[9  ]
#define MSG_PASSED                  pcMessages[10 ]
#define MSG_FAILED                  pcMessages[11 ]
#define MSG_POPUP_ERR               pcMessages[12 ]
#define MSG_POPUP_WRN               pcMessages[13 ]
#define MSG_POPUP_HINT              pcMessages[14 ]
#define MSG_POPUP_FV900X            pcMessages[15 ]
#define MSG_POPUP_CP                pcMessages[16 ]
#define MSG_POPUP_DEL_ADMIN         pcMessages[17 ]
#define MSG_POPUP_DEL_USER          pcMessages[18 ]
#define MSG_POPUP_EQUAL_USER        pcMessages[19 ]
#define MSG_POPUP_USER_PSWD         pcMessages[20 ]
#define MSG_POPUP_ADD_USER          pcMessages[21 ]
#define MSG_POPUP_PSWD              pcMessages[22 ]
#define MSG_POPUP_CHANGE_PSWD       pcMessages[23 ]
#define MSG_ERR_READING_ASSICID     pcMessages[24 ]
#define MSG_ERR_REC_ANSWER          pcMessages[25 ]
#define MSG_ERR_READING_SERNR       pcMessages[26 ]
#define MSG_ERR_INITPRINTER         pcMessages[27 ]
#define MSG_ERR_INIT_DM             pcMessages[28 ]
#define MSG_ERR_PRINT_LABEL         pcMessages[29 ]
#define MSG_ERR_HM30NOTFOUND        pcMessages[30 ]
#define MSG_ERR_READINGTAGDATA      pcMessages[31 ]
#define MSG_ERR_READINGBARD         pcMessages[32 ]
#define MSG_ERR_ASICIDSNOTEQUAL     pcMessages[33 ]
#define MSG_ERR_FORMARSDCARD        pcMessages[34 ]
#define MSG_ERR_SENDINGCALDAT       pcMessages[35 ]
#define MSG_ERR_READING_RAWTAG      pcMessages[36 ]
#define MSG_ERR_ANSW_RAWTAG         pcMessages[37 ]
#define MSG_ERR_SEARCHCALDAT        pcMessages[38 ]
#define MSG_ERR_SECONDCALDAT        pcMessages[39 ]
#define MSG_ERR_ASICIDNOTEQUAL      pcMessages[40 ]
#define MSG_ERR_READING_TAG         pcMessages[41 ]
#define MSG_ERR_ANSW_TAG            pcMessages[42 ]
#define MSG_ERR_READING_BARD        pcMessages[43 ]
#define MSG_ERR_ANSW_BARD           pcMessages[44 ]
#define MSG_ERR_PRESSTOLOW          pcMessages[45 ]
#define MSG_ERR_PRESSTOHIGH         pcMessages[46 ]
#define MSG_ERR_TEMPTOLOW           pcMessages[47 ]
#define MSG_ERR_TEMPTOHIGH          pcMessages[48 ]
#define MSG_ERR_VALOUTOFRANGE       pcMessages[49 ]
#define MSG_ERR_READCALDAT          pcMessages[50 ]
#define MSG_ERR_RECCALDAT           pcMessages[51 ]
#define MSG_ERR_COEFFNOTCORRECT     pcMessages[52 ]
#define MSG_ERR_EEPROMINCOMPLETE    pcMessages[53 ]

#define MSG_                    pcMessages[   ]


//==============================================================================
// Types

//==============================================================================
// External variables
		
extern const char pcMessages[MSG_NUMMESSAGES][MSG_MESSAGELENGTH];

//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __messages_H__ */
