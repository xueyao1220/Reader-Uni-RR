//==============================================================================
//
// Title:		mystring.c
// Purpose:		A short description of the implementation.
//
// Created on:	08.12.2017 at 16:03:48 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "mystring.h"

//==============================================================================
// Constants

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
// this is the standard stpcpy() function:
// the difference to strcpy() is that it returns a pointer to the end of the
// string (=to the terminator), ideal for efficient concatenation of strings.
char *stpcpy(char *dest, const char *src)
{
   while((*dest++ = *src++));
   return dest-1;
}


//
//   Copy max (num-1) characters from src to dest.
//   The resulting string dest is always NUL-terminated.
//   num is the size of the destination char array (incl. terminator).
//   if num <=0 then it doesn't copy anything and returns dest.
//   returns pointer to string terminator of dest string.
//
char *strncpynul(char *dest, const char *src, int num)
{
   if(num > 0)
   {
      char *destmax = dest+num-1; // last char in dest array
      while(dest < destmax)
         if(!(*dest++ = *src++))  // copy and test if terminator
            return dest-1;        // terminator copied -> return pointer to terminator
      // we stopped because we reached max length -> add terminator
      *dest = '\0';
   }
   return dest; // return pointer to string terminator
}


//
//   Copy max (num-1) characters from src to dest, and fill the rest of dst
//   with NUL characters.
//   The resulting string dest is always NUL-terminated
//   num is the size of the destination char array (incl. terminator)
//
void strncpynulset(char *dest, const char *src, int num)
{
   if(num > 0)
   {
      char *destmax = dest+num-1; // points to last char in dest array
      while(dest < destmax && (*dest++ = *src++))
         ;
      ++destmax;
      while(dest < destmax)
         *dest++ = '\0';
   }
}
