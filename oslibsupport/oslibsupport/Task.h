/****************************************************************
 * Title  : Task.h
 * Purpose: Interface with the Task Manager
 * History: 941110      created
 *
 ****************************************************************/
#if !defined( Task_H )
#define Task_H

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
**      Task_GetName
**
**      passed: char* pacBuff   pointer to the buffer in which to place the result
**              int iBufSize    size of the buffer.  If task name is too long, then it is truncated.
**
**      output: buffer contains taskname string, or empty sting if no task name found.
**
**      returns: standard OS error pointer
**
**      processing:     Calls Toolbox to get task name.
**                      This assumes that the Task Name was registered by Wimp_initialise, AND that
**                      at least one call to Wimp_poll has been made.  If this assumption is not valid,
**                      a null string is output.
**                      Standard Error pointer is returned on error.
**
*****************************************************************/

#include "oslib/os.h"

#ifdef __cplusplus
extern "C"
{
#endif

os_error* Task_GetName( char* pacBuff, int iBufSize );

#ifdef __cplusplus
}
#endif

#endif

/* end */
