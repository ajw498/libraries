/****************************************************************
** Title  :   SupportLib.h.ToolboxTypes
**
** Purpose:   Provides translation for ToolboxLib names to OSLib names
**
** Copyright:   ©1997 Control Computer Consultants
**
** History:     970709  created
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

#if !defined toolboxtypes_H
  #define toolboxtypes_H

#if !defined( toolbox_H )
  #include "oslib/toolbox.h"
#endif

  typedef toolbox_block     	    IdBlock;
    #define self_id                this_obj
    #define self_component         this_cmp
    #define parent_id              parent_obj
    #define parent_component       parent_cmp
    #define ancestor_id            ancestor_obj
    #define ancestor_component     ancestor_cmp

  typedef toolbox_o 	      	    ObjectId;
  typedef toolbox_c 	      	    ComponentId;

  typedef toolbox_action          ToolboxEvent;


#endif



/*** END ***/
