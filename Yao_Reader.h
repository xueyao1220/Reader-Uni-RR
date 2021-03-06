/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2018. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitCallback */
#define  PANEL_DECORATION                 3       /* control type: deco, callback function: (none) */
#define  PANEL_sTBProductionStatus        4       /* control type: textBox, callback function: (none) */
#define  PANEL_DECORATION_2               5       /* control type: deco, callback function: (none) */
#define  PANEL_sSerialNr                  6       /* control type: string, callback function: (none) */
#define  PANEL_sAsicID                    7       /* control type: string, callback function: (none) */
#define  PANEL_iAskID                     8       /* control type: command, callback function: AskIDPressed */
#define  PANEL_STARTBUTTON                9       /* control type: command, callback function: StartCallback */
#define  PANEL_sLTProductionRecord        10      /* control type: listBox, callback function: (none) */
#define  PANEL_TEXTMSG                    11      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AskIDPressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
