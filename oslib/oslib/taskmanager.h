#ifndef taskmanager_H
#define taskmanager_H

/* C header file for TaskManager
 * written by DefMod (Dec 12 2000) on Tue Dec 12 20:08:57 2000
 * Jonathan Coxhead, jonathan@doves.demon.co.uk, 22 May 1995
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

#ifndef os_H
#include "oslib/os.h"
#endif

#ifndef wimp_H
#include "oslib/wimp.h"
#endif

#if defined NAMESPACE_OSLIB
  namespace OSLib {
#endif

/**********************************
 * SWI names and SWI reason codes *
 **********************************/
#undef  TaskManager_TaskNameFromHandle
#define TaskManager_TaskNameFromHandle          0x42680
#undef  XTaskManager_TaskNameFromHandle
#define XTaskManager_TaskNameFromHandle         0x62680
#undef  TaskManager_EnumerateTasks
#define TaskManager_EnumerateTasks              0x42681
#undef  XTaskManager_EnumerateTasks
#define XTaskManager_EnumerateTasks             0x62681
#undef  TaskManager_Shutdown
#define TaskManager_Shutdown                    0x42682
#undef  XTaskManager_Shutdown
#define XTaskManager_Shutdown                   0x62682
#undef  TaskManager_StartTask
#define TaskManager_StartTask                   0x42683
#undef  XTaskManager_StartTask
#define XTaskManager_StartTask                  0x62683

/************************************
 * Structure and union declarations *
 ************************************/
typedef struct taskmanager_task                 taskmanager_task;

/********************
 * Type definitions *
 ********************/
typedef bits taskmanager_flags;

struct taskmanager_task
   {  wimp_t task;
      char *name;
      int slot_size;
      taskmanager_flags flags;
   };

typedef bits taskmanager_shutdown_flags;

/************************
 * Constant definitions *
 ************************/
#define taskmanager_NAME_LIMIT                  32
#define taskmanager_MODULE_TASK                 ((taskmanager_flags) 0x1u)
#define taskmanager_DRAGGABLE_SLOT              ((taskmanager_flags) 0x2u)
#define taskmanager_SHUTDOWN_EXIT_ONLY          ((taskmanager_shutdown_flags) 0x1u)
#define taskmanager_SHUTDOWN_NO_PRE_QUIT        ((taskmanager_shutdown_flags) 0x2u)
#define taskmanager_SHUTDOWN_PORTABLE_POWER_DOWN ((taskmanager_shutdown_flags) 0x4u)
#define taskmanager_SHUTDOWN_SEND_MESSAGE       ((taskmanager_shutdown_flags) 0x8u)
#define taskmanager_SHUTDOWN_IGNORE_UP_CALLS    ((taskmanager_shutdown_flags) 0x10u)

/*************************
 * Function declarations *
 *************************/

#ifdef __cplusplus
   extern "C" {
#endif

/* ------------------------------------------------------------------------
 * Function:      taskmanager_task_name_from_handle()
 *
 * Description:   Finds the name of a task
 *
 * Input:         task - value of R0 on entry
 *
 * Output:        name - value of R0 on exit (X version only)
 *
 * Returns:       R0 (non-X version only)
 *
 * Other notes:   Calls SWI 0x42680.
 */

extern os_error *xtaskmanager_task_name_from_handle (wimp_t task,
      char **name);
__swi (0x42680) char *taskmanager_task_name_from_handle (wimp_t task);

/* ------------------------------------------------------------------------
 * Function:      taskmanager_enumerate_tasks()
 *
 * Description:   Enumerates all the currently active tasks
 *
 * Input:         context - value of R0 on entry
 *                task - value of R1 on entry
 *                size - value of R2 on entry
 *
 * Output:        context_out - value of R0 on exit (X version only)
 *                end - value of R1 on exit
 *
 * Returns:       R0 (non-X version only)
 *
 * Other notes:   Calls SWI 0x42681.
 */

extern os_error *xtaskmanager_enumerate_tasks (int context,
      taskmanager_task *task,
      int size,
      int *context_out,
      char **end);
extern int taskmanager_enumerate_tasks (int context,
      taskmanager_task *task,
      int size,
      char **end);

/* ------------------------------------------------------------------------
 * Function:      taskmanager_shutdown()
 *
 * Description:   Initiates a desktop shutdown
 *
 * Input:         flags - value of R0 on entry
 *
 * Other notes:   Calls SWI 0x42682.
 */

extern os_error *xtaskmanager_shutdown (taskmanager_shutdown_flags flags);
__swi (0x42682) void taskmanager_shutdown (taskmanager_shutdown_flags flags);

/* ------------------------------------------------------------------------
 * Function:      taskmanager_start_task()
 *
 * Description:   Starts a new WIMP task - RISC O S 4+
 *
 * Input:         path_name - value of R0 on entry
 *
 * Other notes:   Calls SWI 0x42683.
 */

extern os_error *xtaskmanager_start_task (char const *path_name);
__swi (0x42683) void taskmanager_start_task (char const *path_name);

#ifdef __cplusplus
   }
#endif

#if defined NAMESPACE_OSLIB
  } 
#endif

#endif
