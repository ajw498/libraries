#ifndef adjuster_H
#define adjuster_H

/* C header file for Adjuster
 * written by DefMod (Dec 12 2000) on Tue Dec 12 19:34:19 2000
 * Jonathan Coxhead, jonathan@doves.demon.co.uk, 5 Sept 1995
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

#ifndef toolbox_H
#include "oslib/toolbox.h"
#endif

#ifndef gadget_H
#include "oslib/gadget.h"
#endif

#if defined NAMESPACE_OSLIB
  namespace OSLib {
#endif

/************************************
 * Structure and union declarations *
 ************************************/
typedef struct adjuster_gadget                  adjuster_gadget;
typedef struct adjuster_action_clicked          adjuster_action_clicked;
typedef struct aduster_action_clicked_block     aduster_action_clicked_block;

/********************
 * Type definitions *
 ********************/
struct adjuster_gadget
   {  int reserved;
   };

typedef gadget_object_base adjuster_object;

/* ------------------------------------------------------------------------
 * Type:          adjuster_action_clicked
 *
 * Description:   Prefer Aduster_ActionClickedBlock
 */

struct adjuster_action_clicked
   {  osbool up;
   };

struct aduster_action_clicked_block
   {  toolbox_ACTION_HEADER_MEMBERS
      osbool up;
   };

/************************
 * Constant definitions *
 ************************/
#define class_ADJUSTER                          ((toolbox_class) 0x300u)
#define adjuster_INCREMENT                      ((gadget_flags) 0x1u)
#define adjuster_VERTICAL                       ((gadget_flags) 0x2u)
#define action_ADJUSTER_CLICKED                 0x8288Cu

#if defined NAMESPACE_OSLIB
  } 
#endif

#endif
