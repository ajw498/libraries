/****************************************************************
** Title  :	SupportLib.h.GadgetTypes
**
** Purpose:	Provides translation from ToolboxLib names to OSLib names
**
** Copyright:   ©1997 Control Computer Consultants
**
** History:     970705  created
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
#if !defined gadgettypes_H
  #define gadgettypes_H

#if !defined toolbox_H
  #include "oslib/toolbox.h"
#endif

#if !defined( draggable_H )
  #include "oslib/draggable.h"
#endif

// define the gadget header - has no equivalent in OSLib
  typedef struct gadget_header_t
  {
    unsigned int    flags;
    int             type;
    os_box          box;
    toolbox_c       component_id;
    char            *help_message;
    int             max_help;
  } gadget_header;


// define the gadget structure.  This must be cast into a gadget_object for OSLib
  typedef struct gadget_t
  {
    gadget_header hdr;
    union
    {
//        ActionButton      action_button;
//        OptionButton      option_button;
//        LabelledBox       labelled_box;
//        Label             label;
//        RadioButton       radio_button;
//        DisplayField      display_field;
//        WritableField     writable_field;
//        Slider            slider;
        draggable_gadget         draggable;
//        PopUp             popup;
//        Adjuster          adjuster;
//        NumberRange       number_range;
//        StringSet         string_set;
//        Button            button;
    } data;
  } gadget;
  typedef gadget Gadget;

  // common names
  #if !defined max_text_len
    #define max_text_len      text_limit
  #endif
  #if !defined sprite
    #define sprite    	      sprite_name
  #endif
  #if !defined max_sprite_len
    #define max_sprite_len    sprite_limit
  #endif

  ////////////////////////////////////////////////////////////////
  // convert the draggable gadget
////////////////////////////////////////////////////////////////
  typedef draggable_gadget    	      	      	Draggable;

  #define Draggable_Base      	      	      	class_DRAGGABLE

  #define Draggable_GenerateDragStarted         draggable_GENERATE_DRAG_STARTED
  #define Draggable_Sprite                      draggable_SPRITE
  #define Draggable_Text                        draggable_TEXT
  #define Draggable_TypeMask                    draggable_TYPE
  #define Draggable_TypeShift                   draggable_TYPE_SHIFT
  #define Draggable_ToolboxIds                  draggable_USE_TOOLBOX_IDS
  #define Draggable_HasDropShadow               draggable_DROP_SHADOW
  #define Draggable_NotDithered                 draggable_NO_DITHER


  /*-- draggable events --*/

  #define Draggable_DragStarted               	action_DRAGGABLE_DRAG_STARTED
  #define Draggable_DragEnded                 	action_DRAGGABLE_DRAG_ENDED

  #define Draggable_DragStarted_Adjust        	draggable_DRAG_STARTED_ADJUST
  #define Draggable_DragStarted_Select        	draggable_DRAG_STARTED_SELECT
  #define Draggable_DragStarted_Shift         	draggable_DRAG_STARTED_SHIFT
  #define Draggable_DragStarted_Ctrl          	draggable_DRAG_STARTED_CTRL

  #define Draggable_DragEndedOnToolboxWindow    0x00000001u



#endif


/*** END ***/
