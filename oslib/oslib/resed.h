#ifndef resed_H
#define resed_H

/* C header file for ResEd
 * written by DefMod (Dec 12 2000) on Tue Dec 12 19:34:02 2000
 * Anon
 */

/*OSLib---efficient, type-safe, transparent, extensible,
   register-safe A P I coverage of RISC O S*/
/*Copyright © 1994 Jonathan Coxhead*/

/*
      OSLib is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

      OSLib is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
   along with this programme; if not, write to the Free Software
   Foundation, Inc, 675 Mass Ave, Cambridge, MA 02139, U S A.
*/

#ifndef types_H
#include "oslib/types.h"
#endif

#if defined NAMESPACE_OSLIB
  namespace OSLib {
#endif

/************************
 * Constant definitions *
 ************************/
#define message_RES_ED_OBJECT_LOAD              0x83340u
#define message_RES_ED_OBJECT_LOADED            0x83341u
#define message_RES_ED_OBJECT_SEND              0x83342u
#define message_RES_ED_OBJECT_SENDING           0x83343u
#define message_RES_ED_OBJECT_RENAMED           0x83344u
#define message_RES_ED_OBJECT_DELETED           0x83345u
#define message_RES_ED_OBJECT_MODIFIED          0x83346u
#define message_RES_ED_OBJECT_CLOSED            0x83347u
#define message_RES_ED_SPRITES_CHANGED          0x83348u
#define message_RES_ED_OBJECT_NAME_REQUEST      0x83349u
#define message_RES_ED_OBJECT_NAME              0x8334Au
#define message_RES_ED_KEYCUT_DETAILS           0x8334Bu

#if defined NAMESPACE_OSLIB
  } 
#endif

#endif
