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
#ifndef event_H
#define event_H

#ifndef wimp_H
#include "wimp.h"
#endif

#ifndef toolbox_H
#include "oslib/toolbox.h"
#endif

#define event_ANY ((toolbox_o) -1)
#define action_ANY ((bits)0xFFFFFFFFu)

typedef bool event_wimp_handler (wimp_event_no event_code,
      wimp_block *block, toolbox_block *id_block,
      void *handle);

typedef bool event_toolbox_handler (bits event_code,
      toolbox_action *action, toolbox_block *id_block,
      void *handle);

typedef bool event_message_handler (wimp_message *message,
      void *handle);

typedef struct event_wimp_handler_item event_wimp_handler_item;

struct event_wimp_handler_item
   {  event_wimp_handler_item *next;
      toolbox_o               object_id;
      wimp_event_no                     event_code;
      event_wimp_handler      *handler;
      void                    *handle;
   };


typedef struct event_toolbox_handler_item event_toolbox_handler_item;

struct event_toolbox_handler_item
   {  event_toolbox_handler_item *next;
      toolbox_o                  object_id;
      bits                        event_code;
      event_toolbox_handler      *handler;
      void                       *handle;
   };

typedef struct event_message_handler_item event_message_handler_item;

struct event_message_handler_item
   {  event_message_handler_item *next;
      int                        msg_no;
      event_message_handler      *handler;
      void                       *handle;
   };

#ifdef __cplusplus
extern "C"
{
#endif

  extern void event_poll (wimp_event_no *event_code, wimp_block *poll_block,
      void *poll_word);

extern void event_poll_idle (wimp_event_no *event_code, wimp_block *poll_block,
      os_t earliest, void *poll_word);

extern void event_register_wimp_handler (toolbox_o object_id,
      wimp_event_no event_code, event_wimp_handler *handler, void *handle);

extern void event_deregister_wimp_handler (toolbox_o object_id,
      wimp_event_no event_code, event_wimp_handler *handler, void *handle);

extern void event_register_toolbox_handler (toolbox_o object_id,
      bits event_code, event_toolbox_handler *handler, void *handle);

extern void event_deregister_toolbox_handler (toolbox_o object_id,
      bits event_code, event_toolbox_handler *handler, void *handle);

extern void event_register_message_handler (bits msg_no,
      event_message_handler *handler, void *handle);

extern void event_deregister_message_handler (bits msg_no,
      event_message_handler *handler, void *handle);

extern void event_set_mask (wimp_poll_flags mask);

extern void event_get_mask (wimp_poll_flags *mask);

extern void event_initialise (toolbox_block *id_block);

#ifdef __cplusplus
}
#endif

#endif
