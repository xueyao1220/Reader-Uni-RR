//==============================================================================
//
// Title:		timer.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 14:17:37 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __timer_H__
#define __timer_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "feotypes.h"

//==============================================================================
// Constants

//==============================================================================
// Types
		
		

// Double used for CVI
typedef double Tmr_t;
#define TMR_START         TMR_START32
#define TMR_DIFF          TMR_DIFF32
#define TMR_ELAPSED       TMR_ELAPSED32
#define TMR_ADD           TMR_ADD32
#define TMR_SLOW_START    TMR_START32
#define TMR_SLOW_DIFF     TMR_DIFF32
#define TMR_SLOW_ELAPSED  TMR_ELAPSED32
#define Tmr_GetTicker     Tmr_ulGetTicker32
#define Tmr_GetSlowTicker Tmr_ulGetSlowTicker32

typedef struct {
   volatile Tmr_t tTicker;            // the Ticker counts upwards - read with Tmr_GetTicker()!!             
   volatile Tmr_t tSlowTicker;        // the Slow Ticker counts upwards - read with Tmr_GetSlowTicker()!!    
   volatile uint uTickerOverflow;     // counts Ticker ISR overflows (Ticker tasks too slow)                 
   volatile uint uSlowTickerOverflow; // counts SlowTicker overflows (SlowTicker tasks too slow)                       
} sTmrE_t;
extern sTmrE_t sTmrE;


//==============================================================================
// External variables

// start 32-bit Timer
#define TMR_START32(_timer)         (_timer=Timer())
#define TMR_SLOW_START32(_timer)    (_timer=Timer())
// get 32-bit difference between 2 timer values
#define TMR_DIFF32(_later,_earlier) ((double)((double)(_later)-(double)(_earlier)))
// increment a timer by a given number of ticks, with correct overflow handling
#define TMR_ADD32(_timer, _inc)     (_timer=(double)((double)(_timer)+(double)(_inc)))

#define TMR_ELAPSED32(_timer)       TMR_DIFF32(Timer(),_timer)

//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);
void Tmr_vInit(void);   
void Tmr_vDelay(Tmr_t tTicks);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __timer_H__ */
