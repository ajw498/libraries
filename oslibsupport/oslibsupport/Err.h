/****************************************************************
** Title  : Err.h
**
** Purpose: provide error reporting facilities for wimp programs
**      (replaces wimpt_complain from RiscOSLib)
** History: 941110      created
 *
 ****************************************************************/
#if !defined( Err_H )
  #define Err_H

#if !defined( os_H )
  #include "oslib/os.h"
#endif

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
#ifdef __cplusplus
extern "C"
{
#endif



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
os_error *Err_OsErrorReport( os_error *pxErrorBlock );


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
os_error *Err_OsErrorFatal( os_error *pxErrorBlock );


/***************************************************************
** Description:   Display a (possibly fatal) error message in a pop-up
**                dialogue box.
**                Assumes Application Name to be that registered by
**                wimp_initialise; application sprite name to be that name
**                prefixed by !.
**
** Parameters:    BOOL bFatal    -- non-zero indicates fatal error; exit() is called
**                                      after message is acknowledged.
**                char* zFormat  -- printf-style format string
**                ...            -- variable arg list of message to be printed
**
** Returns:       void.
**
** Processing:  formats the error string using sprintf() formatting
**              calls Task_GetName to obtain a name (or "Unknown" if not found)
**              calls SWI Wimp_ReportError with errnum = 0.
**                      if not bFatal, then provide 'information' icon and 'Continue' button
**                      else provide ''error' icon and 'Quit' button (RO3.5 and above)
**              calls exit(1) if bFatal
**
*****************************************************************/
#define Err_FATAL TRUE
void Err_ReportError( bool bFatal, char* zFormat, ...);


/***************************************************************
** Description: Build an error message via MessageTrans if appropriate, and
**              return a pointer to an error block containing the message
**
** Passed:      iErrNum         - error number
**              zMessage        - error message to be passed to MessageTrans

** Returns:     pointer to MessageTrans buffer containing error message
**
** Processing:  Gets Application Messages file from Toolbox;
**              If valid, then passes it to MessageTrans with zMessage for lookup
**
*****************************************************************/
os_error *Err_MakeError( int iErrNum, char *zMessage );


/***************************************************************
** Description:   check for failure to obtain memory and display an error box if true
**
** Parameters:    void *vMemory --      pointer returned from a Malloc call
**                                      NULL implies no memory available
** Returns:       void *vMemory
**
**
** Processing:    if vMemory == NULL
**                      calls Err_OsErrorReport() with appropriate message
**
*****************************************************************/
void *Err_NoMem( void *vMemory );
void *Err_NoMemFatal( void *vMemory );



#ifdef __cplusplus
}
#endif

#endif
/* end */
