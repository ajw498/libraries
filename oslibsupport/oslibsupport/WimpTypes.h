/****************************************************************
** Title  : SupportLib.h.WimpTypes
**
** Purpose: provides translation of ToolboxLib names to OSLib names
**
** Copyright:   ©1995 Control Computer Consultants
**
** History:     970708  created
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

#if !defined wimptypes_h
  #define wimptypes__H

#if !defined( wimp_H )
  #include "oslib/wimp.h"
#endif


  // wimp poll mask
  #define Wimp_Poll_NullMask  	      	      wimp_MASK_NULL
  #define Wimp_Poll_RedrawWindowRequestMask   wimp_QUEUE_REDRAW
  #define Wimp_Poll_PointerLeavingWindowMask  wimp_MASK_LEAVING
  #define Wimp_Poll_PointerEnteringWindowMask wimp_MASK_ENTERING
  #define Wimp_Poll_MouseClickMask    	      wimp_QUEUE_MOUSE
  #define Wimp_Poll_KeyPressedMask    	      wimp_QUEUE_KEY
  #define Wimp_Poll_LoseCaretMask     	      wimp_MASK_LOSE
  #define Wimp_Poll_GainCaretMask     	      wimp_MASK_GAIN
  #define Wimp_Poll_PollWordNonZeroMask       wimp_MASK_POLLWORD
  #define Wimp_Poll_UserMessageMask   	      wimp_MASK_MESSAGE
  #define Wimp_Poll_UserMessageRecordedMask   wimp_MASK_RECORDED
  #define Wimp_Poll_UserMessageAcknowledgeMask wimp_MASK_ACKNOWLEDGE
  #define Wimp_Poll_PollWord                  wimp_GIVEN_POLLWORD
  #define Wimp_Poll_PollWordHighPriority      wimp_POLL_HIGH_PRIORITY
  #define Wimp_Poll_SaveFPRegs	      	      wimp_SAVE_FP

  // Wimp Open Window block
  typedef wimp_open   	      	      	      WimpOpenWindowBlock;
    #define window_handle     	      	      w
    #define visible_area      	      	      visible
    #define behind    	      	      	      next

  // Wimp Message structure
  typedef wimp_block  	      	      	      WimpPollBlock;   	      	// from tboxlibs.h.wimp

  typedef wimp_message 	      	      	      WimpMessage;    	      	// from tboxlibs.h.wimp
  typedef wimp_message	      	      	      WimpSendMessageBlock;

  typedef wimp_message_data_xfer      	      WimpDataSaveMessage;     	  // 1
  typedef wimp_message_data_xfer      	      WimpDataSaveAckMessage;     // 2
  typedef wimp_message_data_xfer      	      WimpDataLoadMessage;        // 3
  typedef wimp_message_data_xfer      	      WimpDataLoadAckMessage;     // 4
// typedef data_open   	      	      	      WimpDataOpen;    	      	  // 5
  typedef wimp_message_ram_xfer	      	      WimpRAMFetchMessage;        // 6
  typedef wimp_message_ram_xfer	      	      WimpRAMTransmitMessage;     // 7

  typedef wimp_message_save_desktop   	      WimpSaveDesktopMessage;     // 10
  typedef wimp_message_data_saved             WimpDataSavedMessage;       // 13
  typedef wimp_message_shutdown	      	      WimpShutdownMessage;     	  // 14

// typedef help_request	      	      	      WimpHelpRequestMessage;     // 0x502
// typedef help_reply  	      	      	      WimpHelpReplyMessage;    	  // 0x503

  // structure for getting a window's state using SWI Wimp_GetWindowState
  typedef wimp_window_state   	      	      WimpGetWindowStateBlock;

#endif

/*** END ***/
