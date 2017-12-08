//==============================================================================
//
// Title:		fv900x.c
// Purpose:		A short description of the implementation.
//
// Created on:	08.12.2017 at 13:56:04 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "fv900x.h"


#include <windows.h>
#include <rs232.h>
#include <ansi_c.h>
#include <userint.h>
#include <utility.h>
#include "timer.h"
#include "retvalnew.h"
#include "DebugPrintf.h"
//#include "messages.h"

#include "Ablauf.h"
#include "main.h"
//#include "ini.h"
#include "fv900x.h"
#include "feotypes.h"  




//==============================================================================
// Constants

#define DEVICE_CP_BAUD       115200
#define DEVICE_CP_PARITY     0   
#define DEVICE_CP_DATABITS   8   
#define DEVICE_CP_STOPBITS   1   
#define DEVICE_CP_QUEUESIZE  512
#define DEVICE_CP_DEFAULTPORTNUMBER 7

#define DEVICECOM_RETRIES        3
#define DEVICECOM_PORTTIMEOUT    0.01f //Timeout is specified with 1 minute, just for debugging set to 1.0f
#define DEVICECOM_ALIVEDUR       2.0f

#define DEVCOM_MAXTELEGRAMLENGTH 66

#define DEVCOM_STATE_INIT        0
#define DEVCOM_STATE_SENDING     1
#define DEVCOM_STATE_RECEIVING   2
#define DEVCOM_STATE_PREPARED    3
#define DEVCOM_STATE_STOPPED     4

#define DEVMSG_BYTESPOS_PROTID         0
#define DEVMSG_BYTESPOS_LENGTH         1
#define DEVMSG_BYTESPOS_CONTENT        2
#define DEVMSG_BYTESPOS_REC_DATA       3
#define DEVMSG_BYTESPOS_LONGMSG_LENGTH 3
#define DEVMSG_BYTESPOS_LONGMSG_CONT   7
#define DEVMSG_BYTESPOS_LONGMSG_DATA   8

//==============================================================================
// Types



//==============================================================================
// Static global variables

static struct
{
   sMessageCouple_t  tActRequest;         //actual request answer couple
   sregt             srComState;          //State of the communication
   char              cMessageRequested;   //Is a new Message requestet, and which is requeseted. If no Message is requested this Value is -1
   bool              bDeviceConnected;    //Is the device connected
   Tmr_t             tComTimer;           //Timer for the communication
   uint8             u8RetryCnt;          //Counter for the Retries
   int               iPortNumber;         //Port number read from ini-file
   uint16            uiRecursDepth;       //How often has send long Message be called              
   uint32            ulBytesToSend;       //How long is the complete Message. only needed for long Data
   uint16            uiStoredCrc;         //CRC stored for use in last telegram
   float             fActComTimeout;      //actual timeout for the dev-ComPort
} sFv900xS;


sFv900Message_t taSendMessages[] = 
{  // Protid        ,Length ,Messagechar           ,Contentptr ,expectedAnswer        ,fTimeoutInSec ,
   {  FV900X_ID_KEY ,1      ,FV900X_MSG_KEY1       ,NULL       ,FV900X_ID_STATUS      ,0.1f  , },  //Sim_Key_1
   {  FV900X_ID_KEY ,1      ,FV900X_MSG_KEY2       ,NULL       ,FV900X_ID_STATUS      ,0.1f  , },  //Sim_Key_2
   {  FV900X_ID_KEY ,1      ,FV900X_MSG_KEY3       ,NULL       ,FV900X_ID_STATUS      ,0.1f  , },  //Sim_Key_3
   {  FV900X_ID_KEY ,1      ,FV900X_MSG_KEY4       ,NULL       ,FV900X_ID_STATUS      ,0.1f  , },  //Sim_Key_4
   {  FV900X_ID_NRM ,2      ,FV900X_MSG_KEY        ,NULL       ,FV900X_MSG_KEY        ,0.1f  , },  //ReadKey Command. If start or stop is made by content
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_BARD       ,NULL       ,FV900X_MSG_BARD       ,1.0f  , },  //Read BarD
   {  FV900X_ID_NRM ,2      ,FV900X_MSG_TAG        ,NULL       ,FV900X_MSG_TAG        ,65.0f , },  //Read Tag
   {  FV900X_ID_NRM ,6      ,FV900X_MSG_SETSER     ,NULL       ,FV900X_MSG_ACK        ,1.0f  , },  //Set Serial Number
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_GETSER     ,NULL       ,FV900X_MSG_GETSER     ,0.1f  , },  //Get Serial number
   {  FV900X_ID_NRM ,7      ,FV900X_MSG_SETTIME    ,NULL       ,FV900X_MSG_ACK        ,0.1f  , },  //Set Time and Date
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_GETTIME    ,NULL       ,FV900X_MSG_GETTIME    ,0.1f  , },  //Get Time and Date
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_VER        ,NULL       ,FV900X_MSG_VER        ,0.1f  , },  //Get SW-VErsion
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_ERR        ,NULL       ,FV900X_MSG_ERR        ,0.1f  , },  //Read Error Log
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_CLRERR     ,NULL       ,FV900X_MSG_ACK        ,0.1f  , },  //Clear Error Log
   {  FV900X_ID_NRM ,5      ,FV900X_MSG_FORMATSD   ,NULL       ,FV900X_MSG_ACK        ,2.0f  , },  //Format SD Card
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_FIELDMODE  ,NULL       ,FV900X_MSG_ACK        ,0.1f  , },  //Start Field Programming mode
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_POLL       ,NULL       ,FV900X_MSG_POLL       ,0.1f  , },  //Alive
   {  FV900X_ID_NRM ,2      ,FV900X_MSG_BUZZ       ,NULL       ,FV900X_MSG_ACK        ,12.0f , },  //Buzzer Test
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_TAGRAW     ,NULL       ,FV900X_MSG_TAGRAW     ,11.0f , },  //Read Tag Raw Mode
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_BARDID     ,NULL       ,FV900X_MSG_BARDID     ,0.1f  , },  //Get BarD ID.
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_READCALDAT ,NULL       ,FV900X_MSG_READCALDAT ,2.0f  , },  //Read the caldat from SD-Card.
   {  FV900X_ID_NRM ,1      ,FV900X_MSG_GETDATE    ,NULL       ,FV900X_MSG_GETDATE    ,0.1f  , },  //Get Date from Device.
   {  FV900X_ID_NRM ,0      ,FV900X_MSG_SETUP      ,NULL       ,FV900X_MSG_ACK        ,1.0f  , },  //Setup. a variable amount of bytes is beeing transfered, so Length is initial set to 0
   {  FV900X_ID_NRM ,0      ,FV900X_MSG_COPYCAL    ,NULL       ,FV900X_MSG_ACK        ,2.0f  , },  //Copy Caldat
};


/*******/
/* CRC */
/*******/
uint16 crclut16[256] = {
   0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
   0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
   0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
   0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
   0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
   0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
   0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
   0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
   0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
   0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
   0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
   0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
   0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
   0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
   0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
   0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
   0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
   0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
   0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
   0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
   0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
   0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
   0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
   0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
   0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
   0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
   0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
   0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
   0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
   0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
   0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
   0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};


//==============================================================================
// Static functions

int urAscii2Hex(char ucAscii)
{
   ucAscii &= 0xFF;
   if      ((ucAscii >= '0') && (ucAscii <= '9')) return (ucAscii - '0');
   else if ((ucAscii >= 'A') && (ucAscii <= 'F'))return(ucAscii - 'A' + 0x0A);
   else if ((ucAscii >= 'a') && (ucAscii <= 'f'))return(ucAscii - 'a' + 0x0A);
   else return(0);
} // Ascii2Hex


uint16 crc_byte16(uint8 *data, unsigned int bytecnt)
{
   uint16 crc = 0;

   while( bytecnt-- )
      crc = crclut16[(crc >> 8 ^ *(data++)) & 0xff] ^ (crc << 8);

   return crc;
}



//==============================================================================
// Global variables

//==============================================================================
// Global functions



//-----------------------------------------------------------------------------
// DESCRIPTION:
//    Receive a Message and verify it with a TableIdx
//    if a Answer is received, this is passed by reference
//    The Buffer must contain at least 61 Bytes
//
sregt Fv900x_srReceiveMsg(char * pcRecAnswer, uint8 * pu8ContentLength)
{
   char acRec[DEVCOM_MAXTELEGRAMLENGTH];
   uint8 u8ReceivedContent;
   uint8 u8Retries = 0;
   uint8 u8Size, u8Strlen;
   uint8 u8CRCPos;
   uint16 uiRecCrc, uiCalcedCrc;
   int iIdx;
   
   if(pu8ContentLength)
      *pu8ContentLength = 0;
      
   while(u8Retries < DEVICECOM_RETRIES)
   {
      memset(acRec, 0, sizeof(acRec));
      
      SetBreakOnLibraryErrors(0);      //CVIdebugging should not stop, just becaus the comm timed out.
      if((acRec[DEVMSG_BYTESPOS_PROTID] = ComRdByte(sFv900xS.iPortNumber)) >= 0)    //receive first char, should be 'S' or 'R'
      {
         SetBreakOnLibraryErrors(1);      //enable the library errors again
         switch(acRec[DEVMSG_BYTESPOS_PROTID])
         {
            case FV900X_ID_NRM:
            {
               
               if((acRec[DEVMSG_BYTESPOS_LENGTH] = ComRdByte(sFv900xS.iPortNumber)) >= 0)    //receive second char, this is the Length of the content
               {
                  if(acRec[DEVMSG_BYTESPOS_LENGTH] > 62)
                     return ERR;
                  if((u8ReceivedContent = ComRd(sFv900xS.iPortNumber, &acRec[DEVMSG_BYTESPOS_CONTENT], acRec[DEVMSG_BYTESPOS_LENGTH]+2)) == acRec[1]+2)    //read as much bytes from com-port as the length of the content is + CRC
                  {
                   //  dbg1((logfp, "Answer received:\r\n"));
                   //  for(iIdx = 0; iIdx < u8ReceivedContent+2; iIdx ++ )
                    //    dbg1((logfp, " %02X\r\n", (uchar)acRec[iIdx]));
                        
                     
                     //look if the received answer was the expected one
                     if(acRec[DEVMSG_BYTESPOS_CONTENT] == sFv900xS.tActRequest.tRequest.cExpectedAnswer)
                     {
                        u8CRCPos = acRec[DEVMSG_BYTESPOS_LENGTH]+2;
                        
                        uiRecCrc = ((uint16)acRec[u8CRCPos]<<8) | (((uint16)acRec[u8CRCPos+1]) & 0x00ff);
                           uiCalcedCrc = crc_byte16(&acRec[DEVMSG_BYTESPOS_CONTENT], acRec[DEVMSG_BYTESPOS_LENGTH]);
                        
                        if(uiRecCrc != uiCalcedCrc)
                           return E_CRC;
                           
                        if(pcRecAnswer)
                           memcpy(pcRecAnswer, &acRec[DEVMSG_BYTESPOS_REC_DATA], 61);
                           
                        if(pu8ContentLength)   
                           *pu8ContentLength = acRec[DEVMSG_BYTESPOS_LENGTH];
                           
                     

                        return OK;
                     }
                     else if(acRec[DEVMSG_BYTESPOS_CONTENT] == FV900X_MSG_ERRIND)
                     {
                        return E_COM_NACK;
                     }
                     else
                     {
                        return E_COM_WRONGANSWER;   
                     }
                  }
               }
               break;
            }
            case FV900X_ID_STATUS:
            {
               
               if((acRec[DEVMSG_BYTESPOS_LENGTH] = ComRdByte(sFv900xS.iPortNumber)) >= 0)    //receive second char, this is the Length of the content
               {
                  //empty the queue
                  if((u8ReceivedContent = ComRd(sFv900xS.iPortNumber, &acRec[DEVMSG_BYTESPOS_CONTENT], acRec[DEVMSG_BYTESPOS_LENGTH]+2)) != acRec[1]+2)    //read as much bytes from com-port as the length of the content is + CRC
                  {
                     return E_COM_WRONGANSWER;
                  }
               }
               return OK;
            }
            default:
               return E_COM_WRONGANSWER;
               break;
         }
      }
      else
      {
         SetBreakOnLibraryErrors(1);      //enable the library errors again
         u8Retries++;
      }
   }
   return E_COM_MAXRETRIES;
}


//-----------------------------------------------------------------------------
// DESCRIPTION:
//    on timeout while receiving a answer, a problem in the communication has occured
//    maybe the device lost some bytes. so the PC has to "fill" the rest of the telegram to 
//    make the device react on a telegram
//
sregt Fv900x_srHandleTimeout(void)
{
   sregt srRetVal = E_COM_MAXRETRIES;
   char cNull = 0;
   char szDummyStr[DEVCOM_MAXTELEGRAMLENGTH];
   Tmr_t tTimeout;
   
   SetComTime(sFv900xS.iPortNumber, DEVICECOM_PORTTIMEOUT);
   TMR_START(tTimeout);
   while(srRetVal == E_COM_MAXRETRIES)
   {
      ComWrt(sFv900xS.iPortNumber, &cNull, 1);
      Sleep(5);
      srRetVal = Fv900x_srReceiveMsg(szDummyStr, NULL);
      if(TMR_ELAPSED(tTimeout) > 5.0f)
         return E_COM_TIMEOUT;
   }//while
   
   SetComTime(sFv900xS.iPortNumber, sFv900xS.fActComTimeout);
   return srRetVal;
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
//    Send a Message by Table Index
//    Content pointer must point to a char array
//    which is at max 61 bytes long, and holds the binary Data for sending
//    Attention!!! u8ContentLength is only needed for long Contents. If messages with only one frame are passed this parameter is ignored
//
sregt Fv900x_srSendMessageByTableIdx(uint16 uiMsgTableIdx, char * pcContent, uint32 ulContentLength)
{
   char acSend[DEVCOM_MAXTELEGRAMLENGTH];
   uint8 u8BytesToAdd, iIdx, u8BytesSend, u8RetryCnt, u8Counter;
   char acDataToSendBuf[DEVCOM_MAXTELEGRAMLENGTH];
   char szDummyStr[DEVCOM_MAXTELEGRAMLENGTH];
   char *pcDataToSend;
   uint16 uiCalcedCrc;
   sregt srRetVal = OK;
   
   memset(acSend, 0, sizeof(acSend));
   u8RetryCnt = 0;
   
   //Add Protocol ID
   acSend[DEVMSG_BYTESPOS_PROTID] = taSendMessages[uiMsgTableIdx].cProtId;

   SetComTime(sFv900xS.iPortNumber, (sFv900xS.fActComTimeout = taSendMessages[uiMsgTableIdx].fTimeoutInSec));


   //Long Messages which needs multiple telegrams
   if(uiMsgTableIdx >= DEVMSG_SETUP)
   {
      uint16 uiDataLength;
      uint16 uiBytesToSend;
      char *pcData, *pcStart;
      
      if(!pcContent)  //should never happen
         return E_NULLPTR;
      
      
      sFv900xS.uiStoredCrc = crc_byte16(pcContent, ulContentLength);
      ulContentLength += 2;
      sFv900xS.ulBytesToSend = ulContentLength;

      //!!!! if return free pcdata again
      pcStart = pcData = (char *)calloc(ulContentLength, 1);
      
      memcpy(pcData, pcContent, ulContentLength-2); 
         
      acSend[DEVMSG_BYTESPOS_CONTENT] = taSendMessages[uiMsgTableIdx].cMessage;
      
      acSend[DEVMSG_BYTESPOS_LONGMSG_LENGTH+0]  = (sFv900xS.ulBytesToSend >> 0) & 0x000000FF;
      acSend[DEVMSG_BYTESPOS_LONGMSG_LENGTH+1]  = (sFv900xS.ulBytesToSend >> 8) & 0x000000FF;
      acSend[DEVMSG_BYTESPOS_LONGMSG_LENGTH+2]  = (sFv900xS.ulBytesToSend >> 16) & 0x000000FF;
      acSend[DEVMSG_BYTESPOS_LONGMSG_LENGTH+3]  = (sFv900xS.ulBytesToSend >> 24) & 0x000000FF;


      while(ulContentLength)
      {
         if(ulContentLength < 56)
         {
            acSend[DEVMSG_BYTESPOS_LENGTH] = 62 - (56 - ulContentLength);
            acSend[DEVMSG_BYTESPOS_LONGMSG_CONT] = 0x00;
         }
         else if((ulContentLength < 58)&&(ulContentLength >= 56))  
         {
			acSend[DEVMSG_BYTESPOS_LENGTH] = 60;
            acSend[DEVMSG_BYTESPOS_LONGMSG_CONT] = 0x01;
		 }
		 else
         {
            acSend[DEVMSG_BYTESPOS_LENGTH] = 62;
            acSend[DEVMSG_BYTESPOS_LONGMSG_CONT] = 0x01;
         }
         uiDataLength = acSend[DEVMSG_BYTESPOS_LENGTH]-6;
         memcpy(&acSend[DEVMSG_BYTESPOS_LONGMSG_DATA], pcData, uiDataLength); 

         if(!acSend[DEVMSG_BYTESPOS_LONGMSG_CONT])
         {
            acSend[DEVMSG_BYTESPOS_LONGMSG_DATA+(ulContentLength-2)] = (uchar) ((sFv900xS.uiStoredCrc >>8) & 0x00ff);
            acSend[DEVMSG_BYTESPOS_LONGMSG_DATA+(ulContentLength-1)] = (uchar) ((sFv900xS.uiStoredCrc) & 0x00ff);
         }

         //CRC
         uiCalcedCrc = crc_byte16(&acSend[DEVMSG_BYTESPOS_CONTENT], acSend[DEVMSG_BYTESPOS_LENGTH]);
   
         acSend[DEVMSG_BYTESPOS_CONTENT+acSend[DEVMSG_BYTESPOS_LENGTH]]   = (uchar) ((uiCalcedCrc >>8) & 0x00ff);
         acSend[DEVMSG_BYTESPOS_CONTENT+acSend[DEVMSG_BYTESPOS_LENGTH]+1] = (uchar) ((uiCalcedCrc) & 0x00ff);

         while(u8RetryCnt < DEVICECOM_RETRIES)
         {
            FlushInQ (sFv900xS.iPortNumber);
            uiBytesToSend = acSend[DEVMSG_BYTESPOS_LENGTH]+2+2;
            u8Counter = uiBytesToSend;
            u8BytesSend = 0;
            pcDataToSend = acSend;
            while(u8Counter)
            {
               u8BytesSend += ComWrtByte (sFv900xS.iPortNumber, *pcDataToSend);
               dbg1((logfp, "Byte sent: %02X\r\n", (uchar)*pcDataToSend));
               
               pcDataToSend++;
               u8Counter--;
               Sleep(5); // 12 funktioniert
            }//while
//             u8BytesSend = ComWrt(sFv900xS.iPortNumber, acSend, uiBytesToSend);

            if(u8BytesSend == uiBytesToSend)
            {
             
               //store the Message for verifying the received Message
               sFv900xS.tActRequest.tRequest = taSendMessages[uiMsgTableIdx];
            
               if(((srRetVal = Fv900x_srReceiveMsg(szDummyStr, NULL))!=OK))
               {
                  if(srRetVal == E_COM_MAXRETRIES) //correct answer was not received in time
                  {
                     if((srRetVal = Fv900x_srHandleTimeout()) != OK)
                     {
                        free(pcStart);
                        return srRetVal;
                     }
                  }
                  
                  if(u8RetryCnt >= DEVICECOM_RETRIES)
                  {
                     free(pcStart);
                     return srRetVal;
                  }
                  else
                  {
                     u8RetryCnt++;
                  }
               }
               else
               {
                  pcData += uiDataLength;          //Set pointer to correct next sending position
                  ulContentLength -= uiDataLength;    //recalculate the length of all data.
                  Sleep(100);   
                  break;
               }
            }
            else
            {
               u8RetryCnt++;
            }
            
            Sleep(100);  
         }
         
      }//while
      free(pcStart);
      return OK;
      
   }
   else  //"normal" Messages, only one telegram
   {
      if(taSendMessages[uiMsgTableIdx].cLength == 0)
         acSend[DEVMSG_BYTESPOS_LENGTH] = 1;
      else   
         acSend[DEVMSG_BYTESPOS_LENGTH] = taSendMessages[uiMsgTableIdx].cLength;
      
      acSend[DEVMSG_BYTESPOS_CONTENT] = taSendMessages[uiMsgTableIdx].cMessage;
   
      u8BytesToAdd = acSend[DEVMSG_BYTESPOS_LENGTH];
   
      if(u8BytesToAdd > 61)//should never happen
         u8BytesToAdd = 61;
   
      //Store content Ptr. Might be needed from answer fct.
      if(pcContent)
         taSendMessages[uiMsgTableIdx].pcContent = pcContent;
      
      //Data are set from contentpointer
      for(iIdx = 1; iIdx<u8BytesToAdd; iIdx++)
      {
         if(pcContent)
         {
            acSend[DEVMSG_BYTESPOS_CONTENT+iIdx] = *pcContent;
            pcContent++;
         }
         else
            break;   
      }
   
      //CRC
      uiCalcedCrc = crc_byte16(&acSend[DEVMSG_BYTESPOS_CONTENT], u8BytesToAdd);

      acSend[DEVMSG_BYTESPOS_CONTENT+u8BytesToAdd] = (uchar) ((uiCalcedCrc >>8) &0x00ff);
      acSend[DEVMSG_BYTESPOS_CONTENT+u8BytesToAdd+1] = (uchar) ((uiCalcedCrc) & 0x00ff);
        
      //store the Message for verifying the received Message
      sFv900xS.tActRequest.tRequest = taSendMessages[uiMsgTableIdx];
   
    

      while(u8RetryCnt < DEVICECOM_RETRIES)
      {
         FlushInQ (sFv900xS.iPortNumber);   
         u8Counter = acSend[DEVMSG_BYTESPOS_LENGTH]+2+2;
         u8BytesSend = 0;
         pcDataToSend = acSend;
         while(u8Counter)
         {
            u8BytesSend += ComWrtByte (sFv900xS.iPortNumber, *pcDataToSend);
           // dbg1((logfp, "Byte sent: %02X\r\n", (uchar)*pcDataToSend));
            
            pcDataToSend++;
            u8Counter--;
            Sleep(5);
         }//while
//         u8BytesSend = ComWrt(sFv900xS.iPortNumber, acSend, /*strlen(acSend)*/acSend[DEVMSG_BYTESPOS_LENGTH]+2+2);
   
         if(u8BytesSend == /*strlen(acSend)*/acSend[DEVMSG_BYTESPOS_LENGTH]+2+2)
            return OK;
         else
            u8RetryCnt++;
         Sleep(100);   
      }
      return E_COM_TIMEOUT;
   }
   
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
//    Init the communication
//
sregt Fv900x_srInitCom(void)
{
   int iRetVal;
   uregt urRetry = 0;
  
   sFv900xS.iPortNumber = DEVICE_CP_DEFAULTPORTNUMBER;
      
   while((iRetVal = OpenComConfig (sFv900xS.iPortNumber, "", DEVICE_CP_BAUD, DEVICE_CP_PARITY, 
                                   DEVICE_CP_DATABITS, DEVICE_CP_STOPBITS, DEVICE_CP_QUEUESIZE, 
                                   DEVICE_CP_QUEUESIZE)) != 0)
   {
      ERR_ (( logfp,"Error Configuring Device Com Port %d for the %d time\n",(int)sFv900xS.iPortNumber,urRetry+1 ));
     // MessagePopup(MSG_POPUP_ERR, MSG_POPUP_CP);
      urRetry++;
      if(urRetry > DEVICECOM_RETRIES)
      {
         return E_COM_INIT_ERR;
      }
   }
   SetComTime(sFv900xS.iPortNumber, DEVICECOM_PORTTIMEOUT);
   sFv900xS.fActComTimeout = DEVICECOM_PORTTIMEOUT;
   sFv900xS.srComState = DEVCOM_STATE_PREPARED;
   return (sregt)iRetVal;
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
//    Uninit the communication
//
sregt Fv900x_srUinitCom(void)
{
   int iRetVal;
   uregt urRetry = 0;
   //if(!Ini_iGetUint32(sIniE.szIniFilePath, INI_SEC_PORTS, INI_KEY_DEVICEPORT, &sFv900xS.iPortNumber))
   sFv900xS.iPortNumber = DEVICE_CP_DEFAULTPORTNUMBER;
      
   while((iRetVal = CloseCom (sFv900xS.iPortNumber)) != 0)
   {
      ERR_ (( logfp,"Error closing Port %d for the device for the %d time\n",(int)sFv900xS.iPortNumber,urRetry+1 ));
      //MessagePopup(MSG_POPUP_ERR, MSG_POPUP_CP);
      urRetry++;
      if(urRetry > DEVICECOM_RETRIES)
      {
         return E_COM_INIT_ERR;
      }
   }
   return (sregt)iRetVal;
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
//    Returns if the device is connected, or not.
//    It is looked after the device by sending a alive signal 
//
bool Fv900x_bDeviceConnected(void)
{
   //Send Alive Signal
   Fv900x_srSendMessageByTableIdx(DEVMSG_ALIVE, NULL, 0);

   //Receive Alive Signal
   if(Fv900x_srReceiveMsg(NULL, NULL) == OK)
      return TRUE;
   return FALSE;   
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
//    init for module
//
sregt Fv900x_srInit(void)
{
   memset (&sFv900xS, 0, sizeof(sFv900xS));
   sFv900xS.cMessageRequested = -1;       //no request at the beginning
   return OK;
}
