/****************************************************************
** Title  :     SysTypes.h
**
** Purpose:     Define type names for compatibility between OSLib and TboxLibs
**
** Copyright:   ©1995 Control Computer Consultants
**
** History:     951028  created
**
*****************************************************************/
#if !defined( SysTypes_H )
  #define SysTypes_H

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

/* This header provides a number of definitions in its own right,
** but its prime purpose is to provide compatibility between the library
** provided with the toolbox - ToolboxLib, and the corresponding library
** in OSLib - OSLib.Toolbox
**
** If any of WIMP_H, TOOLBOX_H, WINDOW_H or MESSAGETRANS_H are #defined,
**  then the corresponding OSLib header is loaded, and the equivalent ToolboxLib
**  names are typdef'd or #defined as appropriate.  This allows old toolbox.h
**  programs to be recompiled using OSLib.
**  if TOOLBOX_H is enabled then GADGET_H may be #defined to allow translation of
**    gadget names, and also the gadget structure to be typedef'd
**  A good many - but by no means all - toolboxlib names are translated.
**
** The only other thing to remember is to explicitly call the x-form of the SWIs,
**  which would be assumed by ToolboxLib.
*/

#define SUPPLANTED 1    // supplanted code flag

#define SIZEOF_WIMPMESSAGE_HDR	20  /* a bit naff, but OSLib doesn'y declare the header
      	      	      	      	    **	for a wimp message, so can't take sizeof() it */
////////////////////////////////////////////////////////////////
// os
#if !defined( os_H )
  #include "oslib/os.h"
#endif

#if !defined BOOL
  #define BOOL bool
#endif

#if !defined NULL
  #define NULL ((void*)0)
#endif

// some useful typedefs
typedef unsigned int uint;
typedef unsigned char uchar;

typedef os_coord TopLeft;   // from tboxlibs.h.toolbox

typedef os_box BBox;  	// from tboxlibs.h.wimp
#define xmin x0
#define ymin y0
#define xmax x1
#define ymax y1


////////////////////////////////////////////////////////////////
// old _kernel stuff
#if !defined( _kernel_h )
 typedef os_error _kernel_oserror;  // from kernel.h
#endif


////////////////////////////////////////////////////////////////
// wimp
#if defined( WIMP_H )
 #if !defined wimptypes_H
   #include "WimpTypes.h"
 #endif
#endif

////////////////////////////////////////////////////////////////
// toolbox
#if defined( TOOLBOX_H )

  #if !defined toolboxtypes__H
    #include "Toolboxtypes.h"
  #endif

  #if defined GADGETS_H && !defined gadgettypes_h
    // gadgets aren't too well defined by OSLib - so do it ourselves
    #include "GadgetTypes.h"
  #endif
#endif

////////////////////////////////////////////////////////////////
// window
#if defined( WINDOW_H )
  #if !defined( window_H )
    #include "oslib/window.h"
  #endif
  #if !defined( window__H )
    #define window__H

    typedef window_action_show_object WindowShowObjectBlock;

  #endif
#endif


////////////////////////////////////////////////////////////////
// messageTrans
#if defined( MESSAGETRANS_H )
 #if !defined( messagetrans_H )
  #include "oslib/messagetrans.h"
 #endif
 #if !defined messagetrans__H
  #define messagetrans__H

  typedef messagetrans_control_block MessagesFD;

 #endif
#endif

#endif


/**** End ****/

