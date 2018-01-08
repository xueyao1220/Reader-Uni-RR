//==============================================================================
//
// Title:		Ablauf.c
// Purpose:		A short description of the implementation.
//
// Created on:	08.12.2017 at 13:54:53 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <windows.h>     
#include <utility.h>


#include <userint.h>
#include <ansi_c.h>
#include <rs232.h>


#include "Ablauf.h"
#include "feotypes.h"   
#include "fv900x.h"
#include "DebugPrintf.h"
#include "retvalnew.h"   
#include "ini.h"


//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static struct
{
   Tmr_t    tComTimer;           //Timer for the communication with the Device
   char     cMessageRequested;   //is a new Message from Device requested
   int      iDevicePortNumber;   //Number of the Com Port of the device
   sregt    srComState;          //in which state is the comport
   uint8    u8RetryCntr;         //counts the retries
   uchar    ucGraphState;        //Actual Graphstate
   Tmr_t    tGraphTimer;         //how long will it take to run though the thread again [s]
   bool     bThreadRunning;      //Indicates if the Thread is running. setting it to FALSE will stop the Tread
   bool     bRequestNewRefFile;  //is Set, if the ArtNr is new selected
   int      iAblLock;            //Lock for the Ablauf Thread
   bool     bSingleTest;         //Flag for indicating is one Test, or all tests Shall be made
   uint16   uiTestIndex;         //Index of the Test todo.
   bool     bTestsStarted;       //Flag for the Tests
   char     szArtNr[64];          //ArtNrString
   sregt    srRetVal;            //RetVal for
 //  char     szPopupTxt[ABL_POPUPSTRINGLENGTH]; //Textbuffer for the User Message
   bool     bCancel;             //TRUE if the User aborts the Tests
   uint32   ulAsicId;            //Asic Id of the currently read ASIC
   uint32   ulSerialNr;          //Serial Number Id of the currently read ASIC
   uint32   ulSdCardGenCounter;  //how many sdcards where generated - needed in Test6 and stored again in Test7
   FILE     *pfCaldatFile;       //File pointer to caldat file
   int16    iEEPromBuf[32];      //image of the TAG-EEPROM
 //  char     szCaldat[CALDAT_SIZE_IN_BYTES];       //image of the caldat data on the SD-card
   uint32   ulSdCaldatAsicId;    //Asic Id stored on the SD-Card
   uint8    u8SingleTest7Running;   //Is The test 7 running
   bool     bDummyPrintSucceeded;   //has a dummy label been printed successfully
  // tPLUTT2Table sPLUTT2TableRdFromCaldat;
}sAblS;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions





sregt Abl_srGetAsicIdFromTag(void)
{
   sregt srRetVal = OK;
   uint16 uiCntPackets =0;
   char szRecAnswer[ABL_DEFSTRINGLENGTH];
   char szPopupStr[ABL_DEFSTRINGLENGTH];
   int16 iEEPromBuf[32];
   uint16 uiRetry = 0;
   
   // send read Raw Tag
   Fv900x_srSendMessageByTableIdx(DEVMSG_READRAWTAG, NULL, 0);
   // receive first msg.
   while((srRetVal = Fv900x_srReceiveMsg(szRecAnswer, NULL)) != OK)
   {
      Fv900x_srSendMessageByTableIdx(DEVMSG_READRAWTAG, NULL, 0);
      uiRetry++;
      
      if(uiRetry >= 3)
         //CHKERRRET(srRetVal , MSG_ERR_ANSW_RAWTAG);
		 break;
   }//while
   
   memset(iEEPromBuf, -1, 32*2);
   for(uiRetry = 0; uiRetry < 3; uiRetry++)
   {
      // while retval == OK
      while(sAblS.srRetVal == OK)
      {
         // add recMsg to AnserStr
         if(szRecAnswer[0] >= 0x20)
            iEEPromBuf[szRecAnswer[0] - 0x20] = (uchar)szRecAnswer[1];
         
         // get Msgs   
         Fv900x_srReceiveMsg(szRecAnswer, NULL);
         uiCntPackets++;
         if(szRecAnswer[0] == 2)
            break;
      }
   
      // Parse ASIC-ID from EEPROM Image
      // Attention. Bytes are in correct order.
      if((iEEPromBuf[8 ]>=0) &&
         (iEEPromBuf[9 ]>=0) &&
         (iEEPromBuf[10]>=0) &&
         (iEEPromBuf[11]>=0))
      {
         sAblS.ulAsicId =  ((uchar)iEEPromBuf[8 ])<<24 | 
                           ((uchar)iEEPromBuf[9 ])<<16 |
                           ((uchar)iEEPromBuf[10])<<8 |
                           ((uchar)iEEPromBuf[11]) ;
         //AssicId received
         //break for
         break;
      }
      else
      {
         if(uiRetry == 2)
         {
            break;
         }
         else
         {
            uiCntPackets = 0;
            Fv900x_srSendMessageByTableIdx(DEVMSG_READRAWTAG, NULL, 0);
         }
      }
   }//for
   sprintf(szPopupStr, "Fehler beim Ermitteln der Seriennummer\nEvtl. existiert keine gueltige, oder zu viele Caldat-Dateien!\nAsic-ID: 0x%08X",sAblS.ulAsicId );
   //CHKERRRET(Abl_srGetSerNr(), szPopupStr);
   
  // if(iEEProm)
   //   memcpy (iEEProm, iEEPromBuf, 32*2);
   Abl_srGetSerNr();
   
   return  sAblS.ulSerialNr;
}


sregt Abl_srGetSerNr(void)
{
   HANDLE hSearchHandle;
   WIN32_FIND_DATA sFind, sDummyFind;
   char szCaldatFilePath[ABL_DEFSTRINGLENGTH];
   char szAllgArtNr[64];
   char szCaldatName[64];
   char *pcSerNr;


   // Search Caldat-file on server (find first)
   Ini_iGetString(sIniE.szIniFilePath, INI_SEC_FOLDERS, INI_KEY_CALDATFOLDER, ABL_DEFSTRINGLENGTH, szCaldatFilePath);
   //Build Complete path with filename
//   sprintf(szCaldatFilePath,"%s%s_0x%08x_??????????_PASS.CAL", szCaldatFilePath, sAblS.szArtNr, sAblS.ulAsicId);
   Ini_iGetString(sIniE.szIniFilePath, INI_SEC_FOLDERS, INI_KEY_ARTNUMCALDAT, ABL_DEFSTRINGLENGTH, szCaldatName);
   strcpy(szAllgArtNr, szCaldatName);
   szAllgArtNr[strlen(szAllgArtNr)-1] = 'X';
   sprintf(szCaldatFilePath,"%s%s_0x%08x_??????????_PASS.CAL", szCaldatFilePath, szAllgArtNr, sAblS.ulAsicId);
   // wenn fehler
   if((hSearchHandle = FindFirstFile(szCaldatFilePath, &sFind)) == INVALID_HANDLE_VALUE)
      return E_FILE_NOTEXISTS;
   
   // wenn findnext == was gefunden
   if(FindNextFile(hSearchHandle, &sDummyFind))
      return E_SECONDCALDATEXISTS;   
   
   // ausparsen der seriennummer aus dem filenamen.
   pcSerNr = strchr(sFind.cFileName, '_');  //search filename from the back (rear)
   pcSerNr++;
   pcSerNr = strchr(pcSerNr , '_');  //search filename from the back (rear)
   pcSerNr++;  //set pointer to the number
   sAblS.ulSerialNr = (uint32)strtoul(pcSerNr, NULL, 10);
   return sAblS.ulSerialNr;
}



