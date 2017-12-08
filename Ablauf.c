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

//#include "Ablauf.h"

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
   char     szPopupTxt[ABL_POPUPSTRINGLENGTH]; //Textbuffer for the User Message
   bool     bCancel;             //TRUE if the User aborts the Tests
   uint32   ulAsicId;            //Asic Id of the currently read ASIC
   uint32   ulSerialNr;          //Serial Number Id of the currently read ASIC
   uint32   ulSdCardGenCounter;  //how many sdcards where generated - needed in Test6 and stored again in Test7
   FILE     *pfCaldatFile;       //File pointer to caldat file
   int16    iEEPromBuf[32];      //image of the TAG-EEPROM
   char     szCaldat[CALDAT_SIZE_IN_BYTES];       //image of the caldat data on the SD-card
   uint32   ulSdCaldatAsicId;    //Asic Id stored on the SD-Card
   uint8    u8SingleTest7Running;   //Is The test 7 running
   bool     bDummyPrintSucceeded;   //has a dummy label been printed successfully
   tPLUTT2Table sPLUTT2TableRdFromCaldat;
}sAblS;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
bool Abl_bCancelFlag(void)
{
   bool bRetVal;
   CmtGetLock(sAblS.iAblLock);       //be sure that only this function got the right to act on this value
   bRetVal = sAblS.bCancel;
   CmtReleaseLock(sAblS.iAblLock);
   return bRetVal;
}



