/****************************************************************
 * Title  : Task.GetName.c
 * Purpose: Obtain the name of the current task from the Wimp
 * History:     941103  created
 *              951027  SysLib2 now calls osLib in preference to _kernel
 *
 ****************************************************************/

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

#define WIMPSWITCH 0


#ifndef os_H
  #include "oslib/os.h"
#endif

#if WIMPSWITCH
  #if !defined( wimpreadsysinfo_H )
    #include "oslib/wimpreadsysinfo.h"
  #endif

  #if !defined( taskmanager_H )
    #include "oslib/taskmanager.h"
  #endif

#else
  #if !defined( toolbox_H )
    #include "oslib/toolbox.h"
  #endif
#endif

#ifndef __string_h
  #include <string.h>
#endif

#include "Task.h"


/****************************************************************
**      Tassk_GetName
**
**      passed: char* pacBuff   pointer to the buffer in which to place the result
**              int iBufSize    size of the buffer.  If task name is too long, then it is truncated.
**
**      output: buffer contains taskname string, or empty sting if not found.
**
**      returns:pointer to standard kernel error block
**
*****************************************************************/
os_error* Task_GetName( char* pacBuff, int iBufSize )
  {
  os_error* pxError;

#if WIMPSWITCH   /* get the task handle/name from the wimp */
  wimp_t xTask;
  wimp_version_no xVersion;
  char *zName;
#else
  int iBytes;
#endif


  /* find the task handle and translate it into the name */
  if( pacBuff != NULL )
    {
    *pacBuff = '\0';

    if( iBufSize > 0 )
      {
      #if WIMPSWITCH   /* get the task handle/name from the wimp */
      pxError = xwimpreadsysinfo_task( &xTask, &xVersion);
      if( !pxError )
        {
        pxError = xtaskmanager_task_name_from_handle( xTask, &zName );
        if( !pxError )
          {
          strncpy( pacBuff, zName, iBufSize );            // copy task name
          *( pacBuff + iBufSize - 1 ) = '\0';             // string terminator, just in case..
          }
        }
      #else   /* get the task name from the toolbox */
      pxError = xtoolboxgetsysinfo_task_name( pacBuff, iBufSize, &iBytes );
      #endif
      }
    }

  return pxError;
  }

/* end */
