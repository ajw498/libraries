/*
 * Title  : Err.NoMem.c
 * Purpose: provide error reporting failure to obtain memory
 * History:     941112  created
 *              951026  SysLib2 now uses OsLib calls in preference to _kernel.
 *
 */
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

#include "Err.h"

#if !defined( os_H )
  #include "oslib/os.h"
#endif

/***************************************************************
** Description:   check for failure to obtain memory and display an error box if true
**
** Parameters:    void *vMemory --      pointer returned from a Malloc call
**                                      NULL implies no memory available
** Returns:       void *vMemory
**
**
** Processing:    if vMemory == NULL
**                      calls Err_ReportError() with appropriate message
**
** Useage:     int *ptr = (int*)Err_NoMem( malloc( sizeof( int ) ) );
**             int *ptr = (int*)Err_NoMemFatal( malloc( sizeof( int ) ) );
**
*****************************************************************/
static char* zToken = "Err_NoMem";

void *Err_NoMem( void *vMemory )
  {
  if( vMemory == NULL )
    {
    Err_OsErrorReport( Err_MakeError( 0, zToken ) );
    }

  return vMemory;
  }

void *Err_NoMemFatal( void *vMemory )
  {
  if( vMemory == NULL )
    {
    Err_OsErrorFatal( Err_MakeError( 0, zToken ) );
    }

  return vMemory;
  }

/*** End ***/
