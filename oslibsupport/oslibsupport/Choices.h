/****************************************************************
** Title  :   	SupportLib.Choices.h.Choices
**
** Purpose:   	Give standard interface to application choices file
**
** Copyright:   ©1997 Control Computer Consultants
**
** History:     970820  created
**
*****************************************************************/
/*
      OSLibSupport is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

      OSLibSupport is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
   along with this programme; if not, write to the Free Software
   Foundation, Inc, 675 Mass Ave, Cambridge, MA 02139, U S A.
*/

/****************************************************************
**  The application choices file is a file specified by system variable
**  <AppName>$Choices, where <AppName> is the name of the of the application
**  as passed to toolbox_initialize.
**
**  The format of the application choices file consists of one line per choice,
**  prefixed by a tag which is seperated from the data by a colon.
**  Multiple instances of a tag are allowed, but only the first occurance will be returned.
**
**  Any line starting with a # is regarded as a comment and will be ignored.
**
****************************************************************/
#if !defined Choices_H
#define Choices_H

#include "oslib/types.h"

/****************************************************************
** Definitions
****************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************
** Global Interface
****************************************************************/

//  Returns TRUE if zTag exists in choices file
extern bool Choices_Exists( const char* zTag );

//  Reads the string associated with zTag from the application choices file
//  Returns:  string length
//  Outputs:  if acString != NULL: at most iBufSiz chars into acString.
//    	      else just returns string length (required buffer size - 1).
//    	      Outputs zDefault if tag not found
extern int Choices_GetString( const char* zTag,
                              char* acString,
                              int iBufSize,
                              const char* zDefault
                            );

// Reads the integer associated with zTag from the application choices file
//  Returns:  integer value
//  Returns iDefault if tag not found
extern int Choices_GetInt( const char* zTag, int iDefault );

// set the string at zTag to zString
// if zTag is not found, then it is created at end of file
// throws exception on file error
extern void Choices_SetString( const char* zTag, const char* zString );

// set the int at zTag to iInt
// if zTag is not found, then it is created at end of file
// throws exception on file error
extern void Choices_SetInt( const char* zTag, int iInt );

#ifdef __cplusplus
}
#endif

#endif
/*** END ***/
