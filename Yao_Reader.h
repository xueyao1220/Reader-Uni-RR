/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
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
#define  PANEL_iLBComPortList             4       /* control type: listBox, callback function: (none) */
#define  PANEL_iBcomPortClose             5       /* control type: command, callback function: OnCloseComPortPressed */
#define  PANEL_iBComPortOpen              6       /* control type: command, callback function: OnOpenComPortPressed */
#define  PANEL_sTBComPortStatus           7       /* control type: textBox, callback function: (none) */
#define  PANEL_DECORATION_2               8       /* control type: deco, callback function: (none) */
#define  PANEL_sSerialNr                  9       /* control type: string, callback function: (none) */
#define  PANEL_sAsicID                    10      /* control type: string, callback function: (none) */
#define  PANEL_iAskID                     11      /* control type: command, callback function: (none) */
#define  PANEL_TEXTMSG                    12      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnCloseComPortPressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnOpenComPortPressed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
