//==============================================================================
//
// Title:		fv900x.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 13:56:04 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __fv900x_H__
#define __fv900x_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "feotypes.h"



//==============================================================================
// Constants
		
		#define FV900X_ID_NRM         0x52     //'R'
#define FV900X_ID_KEY         0x4B     //'K'
#define FV900X_ID_STATUS      0x53     //'S'

#define FV900X_MSG_KEY1       0x01
#define FV900X_MSG_KEY2       0x02
#define FV900X_MSG_KEY3       0x03
#define FV900X_MSG_KEY4       0x04
#define FV900X_MSG_KEY        0x4B     //'K'
#define FV900X_MSG_BARD       0x42     //'B'
#define FV900X_MSG_TAG        0x54     //'T'
#define FV900X_MSG_SETSER     0x69     //'i'
#define FV900X_MSG_GETSER     0x49     //'I'
#define FV900X_MSG_SETTIME    0x64     //'d'
#define FV900X_MSG_GETTIME    0x44     //'D'
#define FV900X_MSG_VER        0x56     //'V'
#define FV900X_MSG_SETUP      0x73     //'s'
#define FV900X_MSG_ERR        0x45     //'E'
#define FV900X_MSG_CLRERR     0x65     //'e'
#define FV900X_MSG_FORMATSD   0x66     //'f'
#define FV900X_MSG_COPYCAL    0x63     //'c'
#define FV900X_MSG_FIELDMODE  0x53     //'S'
#define FV900X_MSG_POLL       0x50     //'P'
#define FV900X_MSG_BUZZ       0x62     //'b'
#define FV900X_MSG_TAGRAW     0x52     //'R'
#define FV900X_MSG_BARDID     0x55     //'U'
#define FV900X_MSG_READCALDAT 0x43     //'C'
#define FV900X_MSG_GETDATE    0x44     //'D'

#define FV900X_MSG_ACK        0x41     //'A'
#define FV900X_MSG_ERRIND     0x4E     //'N'

#define FV900X_MSG_
#define FV900X_MSG_
#define FV900X_MSG_


#define DEVMSG_NO_MSG            -1 
#define DEVMSG_SIMKEY1           0 
#define DEVMSG_SIMKEY2           1 
#define DEVMSG_SIMKEY3           2 
#define DEVMSG_SIMKEY4           3 
#define DEVMSG_READKEY           4 
#define DEVMSG_READBARD          5 
#define DEVMSG_READTAG           6 
#define DEVMSG_SETSER            7 
#define DEVMSG_GETSER            8 
#define DEVMSG_SETTIME           9 
#define DEVMSG_GETTIME           10
#define DEVMSG_GETSWVERS         11
#define DEVMSG_READERRLOG        12
#define DEVMSG_CLRERRLOG         13
#define DEVMSG_FORMATSDCARD      14
#define DEVMSG_STARTFIELDMODE    15
#define DEVMSG_ALIVE             16
#define DEVMSG_BUZZERTEST        17
#define DEVMSG_READRAWTAG        18
#define DEVMSG_GETBARDID         19
#define DEVMSG_READCALDAT        20
#define DEVMSG_GETDATE           21
#define DEVMSG_SETUP             22  //long messages wich needs to send more than one message
#define DEVMSG_COPYCALDAT        23

#define DEVMSG_
#define DEVMSG_


#define FV900X_MSG_LENGTH        61
		
#define S(s) #s
#define STR(s) S(s)


//==============================================================================
// Types
		
typedef struct 
{
   char cProtId;           //identifier of the Protokoll (Protokollkennung)
   char cLength;           //Length of the content of the message [0 to 62]
   char cMessage;          //Messagecharacter
   char *pcContent;        //Content of the Message
   char cExpectedAnswer;   //Which character is expected as Answer?
   float fTimeoutInSec;    //Timeout for this telegram in sec
} sFv900Message_t;


typedef struct
{
   sFv900Message_t  tRequest;
   sFv900Message_t  tAnswer;
}sMessageCouple_t ;

//==============================================================================
// External variables

//==============================================================================
// Global functions


sregt Fv900x_srReceiveMsg(char * pcRecAnswer, uint8 * pu8ContentLength);
//sregt Fv900x_srReceiveLongMsg(char * pcRecAnswer);
sregt Fv900x_srSendMessageByTableIdx(uint16 uiMsgTableIdx, char * pcContent, uint32 ulContentLength);
bool  Fv900x_bDeviceConnected(void);

sregt Fv900x_srInitCom(void);
sregt Fv900x_srUinitCom(void);
sregt Fv900x_srInit(void);
int urAscii2Hex(char ucAscii);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __fv900x_H__ */
