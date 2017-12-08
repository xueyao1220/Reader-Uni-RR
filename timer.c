//==============================================================================
//
// Title:		timer.c
// Purpose:		A short description of the implementation.
//
// Created on:	08.12.2017 at 14:17:37 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "timer.h"

#include <utility.h> // for Timer()






//==============================================================================
// Constants

sTmrE_t sTmrE;

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
void Tmr_vInit(void)
{
   sTmrE.tTicker = 0.0f;
   sTmrE.tSlowTicker = 0.0f;
   sTmrE.uTickerOverflow = 0;
   sTmrE.uSlowTickerOverflow = 0;
}

void Tmr_vDelay(Tmr_t tTicks)
{
   Tmr_t tTimer;
   
   TMR_START(tTimer);
   while(TMR_ELAPSED(tTimer) < tTicks);
}
