//==============================================================================
//
// Title:		Yao_Reader
// Purpose:		A short description of the application.
//
// Created on:	06.12.2017 at 11:18:36 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <rs232.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Yao_Reader.h"
#include "toolbox.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle = 0;
static int iOpenComPortStatus =0;
static int iOpenedComPort;

//==============================================================================
// Static functions



//==============================================================================
// Global variables




//==============================================================================
// Global functions

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
	int error = 0;
	
	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "Yao_Reader.uir", PANEL));
	
	/* display the panel and run the user interface */
	errChk (DisplayPanel (panelHandle));
	errChk (RunUserInterface ());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.

int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			QuitUserInterface(0);	   // Quit the whole Software and close the window

			break;
	}
	return 0;
}

int CVICALLBACK OnCloseComPortPressed (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	int iCloseComPortError =0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(iOpenComPortStatus==1)
			{
				
				iCloseComPortError = CloseCom(iOpenedComPort);
				 
				
				if(iCloseComPortError>=0)
				{
					//Com Port close success 
					iOpenComPortStatus =0;
					SetCtrlVal(PANEL,PANEL_sTBComPortStatus,"Com Port Closed\r\n");
					SetCtrlAttribute(PANEL,PANEL_iBComPortOpen,ATTR_DIMMED,0);
					SetCtrlAttribute(PANEL,PANEL_iBcomPortClose,ATTR_DIMMED,1); 
					
				}
				else
				{
					//com Port close fail
					SetCtrlVal(PANEL,PANEL_sTBComPortStatus,"Fail to close Com Port\r\n");
					SetCtrlVal(PANEL,PANEL_sTBComPortStatus,GetRS232ErrorString(iCloseComPortError));   
				}
			}

			break;
	}
	return 0;
}

int CVICALLBACK OnOpenComPortPressed (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	int iSelectedComPort =0;
	int iComPortOpenError = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (PANEL, PANEL_iLBComPortList, &iSelectedComPort);
		
			
			if(iComPortOpenError>=0)
			{
				//success
				SetCtrlVal(PANEL,PANEL_sTBComPortStatus,"Com Port opened\r\n");
				iOpenComPortStatus =1;
				SetCtrlAttribute(PANEL,PANEL_iBComPortOpen,ATTR_DIMMED,1);
				SetCtrlAttribute(laPANEL,PANEL_iBcomPortClose,ATTR_DIMMED,0);  
				iOpenedComPort= iSelectedComPort;
			}
			else
			{
				//com port open fail
				SetCtrlVal(PANEL,PANEL_sTBComPortStatus,"Fail to open Com Port\r\n");
				SetCtrlVal(PANEL,PANEL_sTBComPortStatus,GetRS232ErrorString(iComPortOpenError));
			}

			break;
	}
	return 0;
}

