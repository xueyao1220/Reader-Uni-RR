//==============================================================================
//
// Title:		Gui.c
// Purpose:		A short description of the implementation.
//
// Created on:	12.01.2018 at 14:12:18 by  .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <utility.h>
#include <userint.h>
#include "Gui.h"



//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables



static struct
{
   char caLoggedInUser[MAIN_USERNAMELENGTH];          //username of the logged in User
   char caPswd[MAIN_MAXUSERS][MAIN_PSWDLENGTH];       //Array of all Passwords
   char caUser[MAIN_MAXUSERS][MAIN_USERNAMELENGTH];   //Array of all Usernames
   int iIndexOfActualChosenUser;                      //Actual chosen Userindex
   int iStatus;                                       //Status of the Module. GUI_USERSETUP_....
   uint16 uiCntWrongPswds;                            //How often have wrong passwords been entered in one Row
   uint16 uiNumUsers;                                 //Number of Users
   uint16 uiNumDelUsers;                              //Number fo Users to delete
   int iGuiLock;
   uint8 u8ActBarIdx;                                 //which is the actual BarIdx
   uint16   uiActRunningTest;                         //index of the actual running test
   uint16   uiShowMsgBox;                             //indicates if, and which Msg-Box should be shown;
   const char *pcHeader;                              //Header of Messagebox
   const char *pcMessage;                             //Message in messagebox
   sregt srConfirmBoxButPressed;                      //return code depending on the Button that has been pressed in the confirmation Popup
   int  iEnterBoxButtonPressed;                       //return code depending on the Button that has been pressed in the confirmation Popup
   char szIdEntered[16];                              //which id has been entered
   uint32 ulEnteredId;                                //Number from the string above
}sGuiS;



//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?


void Gui_vSetInfoText(const char * pcTimeString)
{
   CmtGetLock(sGuiS.iGuiLock);       //be sure that only this function got the right to act on this value
   SetCtrlVal(iTestWndPanel, MAINWND_INFO, pcTimeString);
   CmtReleaseLock(sGuiS.iGuiLock);
}


void Gui_vCallMsgBox(const char *pcHead, const char *pcMessage)
{
   Gui_vCallBox(pcHead, pcMessage, GUI_DEF_MSGBOX);
}
