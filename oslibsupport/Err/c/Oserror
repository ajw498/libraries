/*
 * Title  : Err.OsError.c
 * Purpose: provide error reporting for OS calls in wimp programs
 *      (replaces wimpt_complain from RiscOSLib)
 * History:     941103  created
 *              951026  SysLib2 now calls OSLib rather than _kernel
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
#define DEBUG 0

#include <stdlib.h>

#if !defined( os_H )
  #include "oslib/os.h"
#endif

#if !defined( Task_H )
  #include "Task.h"
#endif

#if !defined( wimp_H )
  #include "oslib/wimp.h"
#endif

#include "Err.h"

#define BUFSIZ 64

// forward reference
static os_error* Err__OsError( os_error* pxErrorBlock, wimp_error_box_flags iFlags );


/***************************************************************
** Description: Display a system error message in a pop-up dialogue box.
**              Assumes Application Name to be that registered by
**              wimp_initialise; application sprite name to be that name
**              prefixed by !.
**              Useful for wrapping up kernel function calls which may fail
**
** Parameters:  pxErrorBlock  -- pointer to standard kernel error block
**
** Processing:  If pxErrorBlock != NULL, then
**              (i)     Calls Task_GetName to obtain the name ("Unknown" if not found )
**              (ii)    calls Wimp_ReportError to report the error.
**                      Buttons are provided in accordance with PRM03 p3-179
**                      for flags = 1<<1 | 1<<8 | 2<<9.
**
*****************************************************************/
os_error* Err_OsErrorReport( os_error* pxErrorBlock )
  {
  wimp_error_box_flags iFlags = 1<<0 | 1<<8 | 2<<9;   /* new (RO3.5) style call */

   if( pxErrorBlock != NULL )
    {
    Err__OsError( pxErrorBlock, iFlags );
    }

  return pxErrorBlock;
  }


/***************************************************************
** Description: Display a system error message in a pop-up dialogue box
**              and terminate application.
**              Assumes Application Name to be that registered by
**              wimp_initialise; application sprite name to be that name
**              prefixed by !.
**              Useful for wrapping up kernel function calls which may fail
**
** Parameters:  pxErrorBlock  -- pointer to standard kernel error block
**
** Processing:  If pxErrorBlock != NULL, then
**              (i)     Calls Task_GetName to obtain the name ("Unknown" if not found )
**              (ii)    calls Wimp_ReportError to report the error.
**                      Buttons are provided in accordance with PRM03 p3-179
**                      for flags = 1<<1 | 1<<8 | 3<<9.
**              (iii)   fanally calls exit().
*****************************************************************/
os_error* Err_OsErrorFatal( os_error* pxErrorBlock )
  {
  wimp_error_box_flags iFlags = 1<<0 | 1<<8 | 3<<9;   /* new (RO3.5) style call */

   if( pxErrorBlock != NULL )
    {
    Err__OsError( pxErrorBlock, iFlags );  // RO3.5 won't return
    exit( 1 );  /* in case of R03.1 return */
    }

  return pxErrorBlock;
  }

/****************************************************************/
static os_error* Err__OsError( os_error* pxErrorBlock, wimp_error_box_flags iFlags )
  {
  char acTaskName[BUFSIZ];
  wimp_error_box_selection xClick;
  char* zName;

#if DEBUG
  Err_ReportError( !Err_FATAL, "pxErrorBlock = %p", pxErrorBlock );
#endif

 if( Task_GetName( acTaskName, BUFSIZ ) == NULL && *acTaskName != '\0' )
    {
    zName = acTaskName;        /* pointer to task name */
    }
  else
    {
    zName = "???";     /* default */
    }


  /* Make the report - no return on RO3.5 fatal error */
  xwimp_report_error_by_category( pxErrorBlock,
                                  iFlags,
                                  zName,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &xClick);

  return pxErrorBlock;
  }

/* end */
