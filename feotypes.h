//==============================================================================
//
// Title:		feotypes.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 14:31:52 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __feotypes_H__
#define __feotypes_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
		
#ifndef _FEOTYPES_INCLUDED
#define _FEOTYPES_INCLUDED

//*****************************************************************************
// COMPANY      Feo Elektronik GmbH, Zwergerstrasse 15, 88214 Ravensburg
//              www.feo-elektronik.de
//
// PROJECT      any
//
// MODULE       feotypes.h
//
// DESCRIPTION  portable, target device and compiler independent integer types
//
//-----------------------------------------------------------------------------
// TARGET       any
//
// COMPILER     any
//
//-----------------------------------------------------------------------------
// VERSION DATE      AUTHOR     CHANGES
//  1.0    25.06.02  W.Reich    creation
//         28.10.02  W.Reich    added __C51__
//         18.11.02  W.Reich    added type bool
//         14.01.03  W.Reich    added __CPU_16LX__
//         17.01.03  D.Clus     added __C166__
//         02.06.03  D.Clus     added __CVI__
//         16.09.03  W.Reich    added __CPU_FR__
//         09.01.04  D.Clus     added __m56800__
//         08.06.04  W.Reich    added __GNUC__ with __ARM_ARCH_4T__
//         17.06.04  W.Reich    changed __ARM_ARCH_4T__ to (__arm__ || __thumb__)
//         23.06.04  W.Reich    corrected CALL_ADDR
//         08.12.05  W.Reich    added ATOMIC_MEMxxx32 macros
//         25.01.06  W.Reich    added POINTER_INT (useful for pointer aligning)
//         07.02.06  W.Reich    added uint64, int64, HAVE_INT64 for gcc/ARM
//         28.03.06  D.Clus     added mwerks hc08
//         20.08.06  D.Clus     added TI dsps
//         25.08.06  W.Reich    added _BIG-/_LITTLE_ENDIAN (MSP430, ARM, TI DSP) 
//         08.06.07  W.Reich    __CPU_16LX__: POINTER_INT, _LITTLE/_BIG_ENDIAN
//         06.12.07  WR         __TMS320C28XX__: int64, uint64, HAVE_INT64
//         18.03.08  A.Fertl    added mwerks hcs08
//         02.06.08  WR         added int64 for LabWindows/CVI
//         20.06.08  WR         added BYTES_PER_CHAR, BITS_PER_CHAR
//*****************************************************************************


// determine compiler and CPU
// feel free to add any compilers/CPUs not yet supported!

#ifndef __TID__
#define __TID__ 0 //metrowerks hc08 is a bit picky
#endif

#if (defined(__IAR_SYSTEMS_ICC)&&(((__TID__>>8)&0x7F)==43)) || defined(__ARCHELON__) // Texas Instruments MSP430
 #define _LITTLE_ENDIAN 1     // LSByte first
 #define _BIG_ENDIAN    0     // MSByte first
 #define NBITS_CPUREG 16      // 16 bit register width
 #define NBITS_MEMORY 16      // 16 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint16  // integer that can hold a data pointer

#elif defined(_C88)           // Epson S1C88xxx
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 8       // 8 bit register width
 #define NBITS_MEMORY 8       // 8 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint16  // integer that can hold a data pointer

#elif (defined(M16C)) && (defined(NC30))  // Mitsubishi/Renesas M16C6N
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 16      // 16 bit register width
 #define NBITS_MEMORY 16      // 16 bit memory data bus width
 typedef unsigned char bool;  // has special boolean type '_Bool' (==8 bit unsigned) which causes compiler crash... >-/
 #define POINTER_INT TODO: depends on memory model? // integer that can hold a data pointer

#elif (defined(__C51__))      // Keil C51
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 8       // 8 bit register width
 #define NBITS_MEMORY 8       // 8 bit memory data bus width
 typedef bit bool;            // C51 supports a 'bit' data type
 #define POINTER_INT TODO: depends on memory model! // integer that can hold a data pointer

#elif (defined(__CPU_16LX__)) // Fujitsu 16LX
 #define _LITTLE_ENDIAN 1     // LSByte first
 #define _BIG_ENDIAN    0     // MSByte first
 #define NBITS_CPUREG 16      // 16 bit register width
 #define NBITS_MEMORY 16      // 16 bit memory data bus width
 #define ATOMIC_MEMRD32  1    // has atomic 32-bit memory read access
 #define ATOMIC_MEMWR32  1    // has atomic 32-bit memory write access
 #define ATOMIC_MEMINC32 1    // has atomic 32-bit memory inc/dec
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #if _MEMMODEL_LARGE   // this must be #defined in 'project.h' before including 'feotypes.h'
  #define POINTER_INT uint32  // integer that can hold a data pointer
 #elif _MEMMODEL_SMALL  // this must be #defined in 'project.h' before including 'feotypes.h'
  #define POINTER_INT uint16  // integer that can hold a data pointer
 #endif

#elif (defined(__C166__))     // Keil C166
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 16      // 16 bit register width
 #define NBITS_MEMORY 16      // 16 bit memory data bus width
 typedef bit bool;            // C166 supports a 'bit' data type
 #define POINTER_INT TODO: depends on memory model? // integer that can hold a data pointer

#elif (defined(__CVI__) || defined(_CVI_))  // LabWindows/CVI
 #define _LITTLE_ENDIAN 1     // LSByte first
 #define _BIG_ENDIAN    0     // MSByte first
 #define NBITS_CPUREG 32      // 32 bit register width
 #define NBITS_MEMORY 32      // 32 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint32  // integer that can hold a data pointer
 typedef unsigned __int64 uint64; // need to suppress diagnostic # 452 'long long is nonstandard'
 typedef __int64 int64;
 #define HAVE_INT64 1         // uint64/int64 is available

#elif (defined(__CPU_FR__))   // Fujitsu FR
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 32      // 32 bit register width
 #define NBITS_MEMORY 32      // 32 bit memory data bus width
 #define ATOMIC_MEMINC32 1    // has atomic 32-bit memory inc/dec
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint32  // integer that can hold a data pointer

#elif (defined(__MWERKS__)&&(defined(__m56800__))) // Motorola/Freescale M56800 DSP
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 16      // 16 bit register width
 #define NBITS_MEMORY 16      // 16 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint16  // integer that can hold a data pointer

#elif (defined(__MWERKS__)&&(defined(__HC08__))) // Motorola/Freescale 68HC08
 #define _LITTLE_ENDIAN ?     // LSByte first
 #define _BIG_ENDIAN    ?     // MSByte first
 #define NBITS_CPUREG 8       // 8 bit register width
 #define NBITS_MEMORY 8       // 8 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint16  // integer that can hold a data pointer

#elif (defined(__MWERKS__)&&(defined(__HCS08__))) // Motorola/Freescale HCS08
 #ifdef __LITTLE_ENDIAN__      // compiler-predefined
  #define _LITTLE_ENDIAN 1     // LSByte first
  #define _BIG_ENDIAN    0     // MSByte first
 #elif defined(__BIG_ENDIAN__) // compiler-predefined
  #define _LITTLE_ENDIAN 0     // LSByte first
  #define _BIG_ENDIAN    1     // MSByte first
 #else
  #define _LITTLE_ENDIAN ?     // LSByte first
  #define _BIG_ENDIAN    ?     // MSByte first
 #endif
 #define NBITS_CPUREG 8      // 8 bit register width
 #define NBITS_MEMORY 8      // 8 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint16  // integer that can hold a data pointer

#elif (defined(__GNUC__)&&(defined(__arm__)||defined(__thumb__))) // GNU gcc for ARM (e.g. ARM7 Hynix HMS30C7202)
 #define _LITTLE_ENDIAN 1     // LSByte first
 #define _BIG_ENDIAN    0     // MSByte first
 #define NBITS_CPUREG 32      // 32 bit register width
 #define NBITS_MEMORY 32      // 32 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint32  // integer that can hold a data pointer
 typedef unsigned long long uint64;
 typedef signed long long int64;
 #define HAVE_INT64 1         // uint64/int64 is available

#elif (defined(__TMS320C28XX__)) // TI DSP
 #define _LITTLE_ENDIAN 1     // LSByte first
 #define _BIG_ENDIAN    0     // MSByte first
 #define NBITS_CPUREG 32      // 32 bit register width
 #define NBITS_MEMORY 32      // 32 bit memory data bus width
 typedef unsigned char bool;  // no bit type available -> boolean = uchar
 #define POINTER_INT  uint32  // integer that can hold a data pointer
 typedef unsigned long long uint64; // need to suppress diagnostic # 452 'long long is nonstandard'
 typedef signed long long int64;
 #define HAVE_INT64 1         // uint64/int64 is available

#else
 #error Unknown CPU or compiler!

#endif 


//-----------------------------------------------------------------------------
// Data types sregt and uregt represent CPU register type: 8/16/32 bit, depending
// on architecture. Use for small loops, array etc. to avoid the following:
// - unnecessary bit masking or sign/zero extension when using char resp. short
//   on 16 resp. 32-bit machines
// - inefficient coding when using 16-bit int on 8-bit machines
#ifndef NBITS_CPUREG
 #error Undefined NBITS_CPUREG!
#else
 #if NBITS_CPUREG == 8
  typedef signed char    sregt;    // srVarname
  typedef unsigned char  uregt;    // urVarname
 #elif NBITS_CPUREG == 16
  typedef signed short   sregt;
  typedef unsigned short uregt;
 #elif NBITS_CPUREG == 32
  typedef signed long    sregt;
  typedef unsigned long  uregt;
  // all 32-bitters have atomic R/W access, but not necessarily INC/DEC access (ARM)
  #ifndef ATOMIC_MEMRD32
   #define ATOMIC_MEMRD32  1
  #endif
  #ifndef ATOMIC_MEMWR32
   #define ATOMIC_MEMWR32  1
  #endif
 #else
  #error Illegal NBITS_CPUREG!
 #endif
#endif // NBITS_CPUREG

#ifndef ATOMIC_MEMRD32
 #define ATOMIC_MEMRD32  0    // hasn't atomic 32-bit memory read access
#endif
#ifndef ATOMIC_MEMWR32
 #define ATOMIC_MEMWR32  0    // hasn't atomic 32-bit memory write access
#endif
#ifndef ATOMIC_MEMINC32
 #define ATOMIC_MEMINC32 0    // hasn't atomic 32-bit memory inc/dec
#endif


//-----------------------------------------------------------------------------
// Data types smemt and umemt represent memory data bus width: 8/16/32 bit, depending on architecture
// - for efficient coding of memory copy routines,
// - word alignment (conditional defines), etc.
#ifndef NBITS_MEMORY
 #error Unknown NBITS_MEMORY!
#else
 #if NBITS_MEMORY == 8
  typedef signed char    smemt;
  typedef unsigned char  umemt;
 #elif NBITS_MEMORY == 16
  typedef signed short   smemt;
  typedef unsigned short umemt;
 #elif NBITS_MEMORY == 32
  typedef signed long    smemt;
  typedef unsigned long  umemt;
 #else
  #error Illegal NBITS_MEMORY!
 #endif
#endif // NBITS_MEMORY

// 8 Bit: avoid using char, as it can be signed or unsigned, depending on compiler!
typedef signed   char  schar;    // scVarname
typedef unsigned char  uchar;    // ucVarname
typedef signed   char  int8;
typedef unsigned char  uint8;

// 16 Bit signed/unsigned
#if (!(defined(__TMS320C28XX__))) // F28xx defines this also
typedef signed   short int16;    // iVarname
#endif
typedef unsigned short uint16;   // uiVarname

// 32 Bit signed/unsigned
#if (!(defined(__TMS320C28XX__))) // F28xx defines this also
typedef signed   long  int32;    // lVarname
#endif
typedef unsigned long  uint32;   // ulVarname

// 16-32 bit signed/unsigned
//for signed 16-32 bit use int   // iVarName
typedef unsigned int   uint;     // uVarName


// char                          // cVarname
// type* (pointer to type x)     // p<type x>Varname
// void                          // vVarname
// char* (string)                // sVarname


#ifndef TRUE
 #define TRUE  1
#endif

#ifndef FALSE
 #define FALSE 0
#endif

#ifndef ON
 #define ON  1
#endif

#ifndef OFF
 #define OFF 0
#endif

#ifndef NULL
 #define NULL ((void*)0)
#endif

#ifndef NULL_VECT
 #define NULL_VECT ((void(*)(void))0)
#endif


// calls a function at given address; return value: void; parameters: void
#define CALL_ADDR(_funcaddr) ((void(*)(void))(_funcaddr))()

// calls a vector at given address; return value: void; parameters: void
// note: this is an indirect call - the address given is the address of a vector containing the actual function address
#define CALL_VECT(_vectaddr) (*(void(**)(void))(_vectaddr))()

// gets number of elements of an array
// example: uint32 sometable[] = {123,234,345,456,567,};
//          if(index >= numberof(sometable))
//             error("index out of range");
#define numberof(_p)  (sizeof(_p)/sizeof(*(_p)))

// some CPUs have more than 8 bits for data type "char", e.g. TMS320F28xx
#define BYTES_PER_CHAR (4/sizeof(int32))  // number of 8-bit bytes in data type "char"
#define BITS_PER_CHAR (32/sizeof(int32))  // number of bits in data type "char"


// generic bit masks
#ifndef BIT0  // already defined somewhere else?
 #define BIT0  0x01u
 #define BIT1  0x02u
 #define BIT2  0x04u
 #define BIT3  0x08u
 #define BIT4  0x10u
 #define BIT5  0x20u
 #define BIT6  0x40u
 #define BIT7  0x80u
 #define BIT8  0x0100u
 #define BIT9  0x0200u
#endif // BIT0
#ifndef BIT10
 #define BIT10 0x0400u
 #define BIT11 0x0800u
 #define BIT12 0x1000u
 #define BIT13 0x2000u
 #define BIT14 0x4000u
 #define BIT15 0x8000u
#endif // BIT10
#ifndef BIT16
 #define BIT16 0x00010000ul
 #define BIT17 0x00020000ul
 #define BIT18 0x00040000ul
 #define BIT19 0x00080000ul
 #define BIT20 0x00100000ul
 #define BIT21 0x00200000ul
 #define BIT22 0x00400000ul
 #define BIT23 0x00800000ul
 #define BIT24 0x01000000ul
 #define BIT25 0x02000000ul
 #define BIT26 0x04000000ul
 #define BIT27 0x08000000ul
 #define BIT28 0x10000000ul
 #define BIT29 0x20000000ul
 #define BIT30 0x40000000ul
 #define BIT31 0x80000000ul
#endif // BIT16
#ifndef BITA
 #define BITA  BIT10
 #define BITB  BIT11
 #define BITC  BIT12
 #define BITD  BIT13
 #define BITE  BIT14
 #define BITF  BIT15
#endif // BITA


#endif // _FEOTYPES_INCLUDED


//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __feotypes_H__ */
