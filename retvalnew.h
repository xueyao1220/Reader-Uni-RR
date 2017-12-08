//==============================================================================
//
// Title:		retvalnew.h
// Purpose:		A short description of the interface.
//
// Created on:	08.12.2017 at 14:54:55 by Yao Xue.
// Copyright:	Christoph Miethke GmbH & Co. KG. All Rights Reserved.
//
//==============================================================================

#ifndef __retvalnew_H__
#define __retvalnew_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

#define _E(_e) ((sregt)(_e))
		
#define OK                       _E(   0) // no error
#define ERR                      _E(  -1) // general error
#define ERR_ILLEGAL_CASE         _E(  -2) // illegal case state in graph
#define ERR_ILLEGAL_ACT          _E(  -3) // illegal action state in graph
#define E_CANCEL                 _E(  -4) // Aborted by User
#define E_CONFIRM                _E(  -5) // The user didn't see/hear the expected behaviour of the device
#define ERR_ILLEGAL_TEST         _E(  -6) // Function is not called while test 7 is running

#define E_ADCTC_BUSY             _E( -10) // attempt to start conversion while ADC is still busy

#define E_NULLPTR                _E( -20) // attempt to read from a Null Pointer
#define E_CRC                    _E( -21) // CRC Error
#define E_SECONDCALDATEXISTS     _E( -22) // two caldats with the same AsicId exists on the server
#define E_READ_EEPROM            _E( -23) // Error reading eeprom Data

#define E_MKDIR                  _E( -30) // Directory already exists

#define E_COM_INIT_ERR           _E( -40) // Error initialising a comport
#define E_COM_TIMEOUT            _E( -41) // Timeout Error on comport
#define E_COM_NACK               _E( -42) // NACK received
#define E_COM_MAXRETRIES         _E( -43) // Retries exeded
#define E_COM_WRONGANSWER        _E( -44) // Wrong answer received

#define E_FILE_CREATE            _E( -50) // File could not b created
#define E_FILE_CNTRTOHIGH        _E( -51) // The counter of the Protocoll, error or Workflow-file is to high
#define E_FILE_NOTEXISTS         _E( -52) // File does not exist
#define E_FILE_REFNOTEXISTS      _E( -53) // Ref File doesnt exist
#define E_FILE_WRITE             _E( -54) // error while writing to file
#define E_FILE_CNTEXCEEDED       _E( -55) // Filecnt exceeds the 99 possible files
#define E_FILE_RENAME            _E( -56) // Error while renaming a file
#define E_FILE_CLOSE             _E( -57) // Error while closing a file

#define E_PRINT_NEWLABEL         _E( -60) // Error getting label memory
#define E_PRINT_OPENLABEL        _E( -61) // Error opening label
#define E_PRINT_GETLABELOBJ      _E( -62) // Error getting the object from a Label
#define E_PRINT_SETMATRIXCODE    _E( -63) // Error setting a new matrix code
#define E_PRINT_SETSERNR         _E( -64) // Error setting a new matrix code
#define E_PRINT_SETASICID        _E( -65) // Error setting a new matrix code
#define E_PRINT_NOMATRIX_OBJ     _E( -66) // No matrix object found
#define E_PRINT_NOSERNR_OBJ      _E( -67) // No sernr object found
#define E_PRINT_NOASICID_OBJ     _E( -68) // No asicid object found

#define E_VALSNOTEQUAL           _E( -70) // given Values are not equal
#define E_VALUEOUTOFRANGE        _E( -71) // given Value is out of Range

#define E_SCAN_CALIBFAILED       _E( -80) // Calibration of the scanner failed
#define E_SCAN_NODATAMATRIXFOUND _E( -81) // No Datamatrix found
#define E_SCAN_NOASICIDRECEIVED  _E( -82) // No Valid Asic Id has been received

#define E_EEPROM_INCOMPLETE      _E( -90) // EEPROM has not been transfered completely

#define E_INVALID_POS            _E(-100) // Invalid Position chosen for Stepper




#define E_LAST_ERROR              ( -100)

#if(NBITS_CPUREG==8 && E_LAST_ERROR<-128)
#error too many errror codes!
#endif


//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __retvalnew_H__ */
