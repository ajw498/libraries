#ifndef adfs_H
#define adfs_H

/* C header file for ADFS
 * written by DefMod (Dec 12 2000) on Tue Dec 12 18:10:31 2000
 * Jonathan Coxhead, jonathan@doves.demon.co.uk, 21 Aug 1995
 */

/*OSLib---efficient, type-safe, transparent, extensible,
   register-safe A P I coverage of RISC O S*/
/*Copyright � 1994 Jonathan Coxhead*/

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

#ifndef filecore_H
#include "oslib/filecore.h"
#endif

#if defined NAMESPACE_OSLIB
  namespace OSLib {
#endif

/**********************************
 * SWI names and SWI reason codes *
 **********************************/
#undef  ADFS_DiscOp
#define ADFS_DiscOp                             0x40240
#undef  XADFS_DiscOp
#define XADFS_DiscOp                            0x60240
#undef  ADFSDiscOp_Verify
#define ADFSDiscOp_Verify                       0x0
#undef  ADFSDiscOp_ReadSectors
#define ADFSDiscOp_ReadSectors                  0x1
#undef  ADFSDiscOp_WriteSectors
#define ADFSDiscOp_WriteSectors                 0x2
#undef  ADFSDiscOp_ReadTrack
#define ADFSDiscOp_ReadTrack                    0x3
#undef  ADFSDiscOp_ReadId
#define ADFSDiscOp_ReadId                       0x3
#undef  ADFSDiscOp_WriteTrack
#define ADFSDiscOp_WriteTrack                   0x4
#undef  ADFSDiscOp_FormatTrack
#define ADFSDiscOp_FormatTrack                  0x4
#undef  ADFSDiscOp_Seek
#define ADFSDiscOp_Seek                         0x5
#undef  ADFSDiscOp_Restore
#define ADFSDiscOp_Restore                      0x6
#undef  ADFSDiscOp_StepIn
#define ADFSDiscOp_StepIn                       0x7
#undef  ADFSDiscOp_StepOut
#define ADFSDiscOp_StepOut                      0x8
#undef  ADFSDiscOp_ReadSectorsViaCache
#define ADFSDiscOp_ReadSectorsViaCache          0x9
#undef  ADFSDiscOp_Specify
#define ADFSDiscOp_Specify                      0xF
#undef  ADFS_HDC
#define ADFS_HDC                                0x40241
#undef  XADFS_HDC
#define XADFS_HDC                               0x60241
#undef  ADFS_Drives
#define ADFS_Drives                             0x40242
#undef  XADFS_Drives
#define XADFS_Drives                            0x60242
#undef  ADFS_FreeSpace
#define ADFS_FreeSpace                          0x40243
#undef  XADFS_FreeSpace
#define XADFS_FreeSpace                         0x60243
#undef  ADFS_Retries
#define ADFS_Retries                            0x40244
#undef  XADFS_Retries
#define XADFS_Retries                           0x60244
#undef  ADFS_DescribeDisc
#define ADFS_DescribeDisc                       0x40245
#undef  XADFS_DescribeDisc
#define XADFS_DescribeDisc                      0x60245
#undef  ADFS_VetFormat
#define ADFS_VetFormat                          0x40246
#undef  XADFS_VetFormat
#define XADFS_VetFormat                         0x60246
#undef  ADFS_FlpProcessDCB
#define ADFS_FlpProcessDCB                      0x40247
#undef  XADFS_FlpProcessDCB
#define XADFS_FlpProcessDCB                     0x60247
#undef  ADFS_ControllerType
#define ADFS_ControllerType                     0x40248
#undef  XADFS_ControllerType
#define XADFS_ControllerType                    0x60248
#undef  ADFS_PowerControl
#define ADFS_PowerControl                       0x40249
#undef  XADFS_PowerControl
#define XADFS_PowerControl                      0x60249
#undef  ADFSPowerControl_ReadSpin
#define ADFSPowerControl_ReadSpin               0x0
#undef  ADFSPowerControl_SetAutospindown
#define ADFSPowerControl_SetAutospindown        0x1
#undef  ADFSPowerControl_SetSpin
#define ADFSPowerControl_SetSpin                0x2
#undef  ADFS_SetIDEController
#define ADFS_SetIDEController                   0x4024A
#undef  XADFS_SetIDEController
#define XADFS_SetIDEController                  0x6024A
#undef  ADFS_IDEUserOp
#define ADFS_IDEUserOp                          0x4024B
#undef  XADFS_IDEUserOp
#define XADFS_IDEUserOp                         0x6024B
#undef  ADFS_MiscOp
#define ADFS_MiscOp                             0x4024C
#undef  XADFS_MiscOp
#define XADFS_MiscOp                            0x6024C
#undef  ADFSMiscOp_Mount
#define ADFSMiscOp_Mount                        0x0
#undef  ADFSMiscOp_PollChanged
#define ADFSMiscOp_PollChanged                  0x1
#undef  ADFSMiscOp_LockDrive
#define ADFSMiscOp_LockDrive                    0x2
#undef  ADFSMiscOp_UnlockDrive
#define ADFSMiscOp_UnlockDrive                  0x3
#undef  ADFSMiscOp_PollPeriod
#define ADFSMiscOp_PollPeriod                   0x4
#undef  ADFSMiscOp_EjectDisc
#define ADFSMiscOp_EjectDisc                    0x5
#undef  ADFSMiscOp_ReadInfo
#define ADFSMiscOp_ReadInfo                     0x6
#undef  ADFS_SectorDiscOp
#define ADFS_SectorDiscOp                       0x4024D
#undef  XADFS_SectorDiscOp
#define XADFS_SectorDiscOp                      0x6024D
#undef  ADFSSectorDiscOp_Verify
#define ADFSSectorDiscOp_Verify                 0x0
#undef  ADFSSectorDiscOp_ReadSectors
#define ADFSSectorDiscOp_ReadSectors            0x1
#undef  ADFSSectorDiscOp_WriteSectors
#define ADFSSectorDiscOp_WriteSectors           0x2
#undef  ADFSSectorDiscOp_ReadTrack
#define ADFSSectorDiscOp_ReadTrack              0x3
#undef  ADFSSectorDiscOp_ReadId
#define ADFSSectorDiscOp_ReadId                 0x3
#undef  ADFSSectorDiscOp_WriteTrack
#define ADFSSectorDiscOp_WriteTrack             0x4
#undef  ADFSSectorDiscOp_FormatTrack
#define ADFSSectorDiscOp_FormatTrack            0x4
#undef  ADFSSectorDiscOp_Seek
#define ADFSSectorDiscOp_Seek                   0x5
#undef  ADFSSectorDiscOp_Restore
#define ADFSSectorDiscOp_Restore                0x6
#undef  ADFSSectorDiscOp_StepIn
#define ADFSSectorDiscOp_StepIn                 0x7
#undef  ADFSSectorDiscOp_StepOut
#define ADFSSectorDiscOp_StepOut                0x8
#undef  ADFSSectorDiscOp_ReadSectorsViaCache
#define ADFSSectorDiscOp_ReadSectorsViaCache    0x9
#undef  ADFSSectorDiscOp_Specify
#define ADFSSectorDiscOp_Specify                0xF
#undef  ADFS_ECCSAndRetries
#define ADFS_ECCSAndRetries                     0x40250
#undef  XADFS_ECCSAndRetries
#define XADFS_ECCSAndRetries                    0x60250
#undef  ADFS_LockIDE
#define ADFS_LockIDE                            0x40251
#undef  XADFS_LockIDE
#define XADFS_LockIDE                           0x60251
#undef  ADFS_FreeSpace64
#define ADFS_FreeSpace64                        0x40252
#undef  XADFS_FreeSpace64
#define XADFS_FreeSpace64                       0x60252
#undef  Service_IdentifyFormat
#define Service_IdentifyFormat                  0x6B
#undef  Service_DisplayFormatHelp
#define Service_DisplayFormatHelp               0x6C

/********************
 * Type definitions *
 ********************/
typedef int adfs_controller;

/************************
 * Constant definitions *
 ************************/
#define error_ADFS_DRIVER_IN_USE                0x108A0u
#define adfs_CONTROLLER_DISC_NOT_PRESENT        ((adfs_controller) 0x0u)
#define adfs_CONTROLLER1772                     ((adfs_controller) 0x1u)
#define adfs_CONTROLLER71X                      ((adfs_controller) 0x2u)
#define adfs_CONTROLLER_ST506                   ((adfs_controller) 0x3u)
#define adfs_CONTROLLER_IDE                     ((adfs_controller) 0x4u)

/*************************
 * Function declarations *
 *************************/

#ifdef __cplusplus
   extern "C" {
#endif

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_verify()
 *
 * Description:   Verifies a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                size - value of R4 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                unverified - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x0.
 */

extern os_error *xadfsdiscop_verify (bits flags,
      filecore_disc_address disc_addr,
      int size,
      filecore_disc_address *next_disc_addr,
      int *unverified);
extern int adfsdiscop_verify (bits flags,
      filecore_disc_address disc_addr,
      int size,
      filecore_disc_address *next_disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_read_sectors()
 *
 * Description:   Reads sectors from a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *                size - value of R4 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                next_data - value of R3 on exit
 *                unread - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x1.
 */

extern os_error *xadfsdiscop_read_sectors (bits flags,
      filecore_disc_address disc_addr,
      byte *data,
      int size,
      filecore_disc_address *next_disc_addr,
      byte **next_data,
      int *unread);
extern int adfsdiscop_read_sectors (bits flags,
      filecore_disc_address disc_addr,
      byte *data,
      int size,
      filecore_disc_address *next_disc_addr,
      byte **next_data);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_write_sectors()
 *
 * Description:   Writes sectors to a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *                size - value of R4 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                next_data - value of R3 on exit
 *                unwritten - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x2.
 */

extern os_error *xadfsdiscop_write_sectors (bits flags,
      filecore_disc_address disc_addr,
      byte const *data,
      int size,
      filecore_disc_address *next_disc_addr,
      byte **next_data,
      int *unwritten);
extern int adfsdiscop_write_sectors (bits flags,
      filecore_disc_address disc_addr,
      byte const *data,
      int size,
      filecore_disc_address *next_disc_addr,
      byte **next_data);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_read_track()
 *
 * Description:   Reads a track from a floppy disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x3.
 */

extern os_error *xadfsdiscop_read_track (bits flags,
      filecore_disc_address disc_addr,
      byte *data);
extern void adfsdiscop_read_track (bits flags,
      filecore_disc_address disc_addr,
      byte *data);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_read_id()
 *
 * Description:   Reads a hard disc ID
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x3.
 */

extern os_error *xadfsdiscop_read_id (bits flags,
      filecore_disc_address disc_addr,
      byte *data);
extern void adfsdiscop_read_id (bits flags,
      filecore_disc_address disc_addr,
      byte *data);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_write_track()
 *
 * Description:   Writes a track to a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x4.
 */

extern os_error *xadfsdiscop_write_track (bits flags,
      filecore_disc_address disc_addr,
      byte const *data);
extern void adfsdiscop_write_track (bits flags,
      filecore_disc_address disc_addr,
      byte const *data);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_format_track()
 *
 * Description:   Formats a track of a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                format - value of R4 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x4, R3 = 0x0.
 */

extern os_error *xadfsdiscop_format_track (bits flags,
      filecore_disc_address disc_addr,
      filecore_track_format const *format);
extern void adfsdiscop_format_track (bits flags,
      filecore_disc_address disc_addr,
      filecore_track_format const *format);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_seek()
 *
 * Description:   Seeks to a disc location
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x5.
 */

extern os_error *xadfsdiscop_seek (bits flags,
      filecore_disc_address disc_addr);
extern void adfsdiscop_seek (bits flags,
      filecore_disc_address disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_restore()
 *
 * Description:   Does a restore operation for a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x6.
 */

extern os_error *xadfsdiscop_restore (bits flags,
      filecore_disc_address disc_addr);
extern void adfsdiscop_restore (bits flags,
      filecore_disc_address disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_step_in()
 *
 * Description:   Steps a floppy disc in one track
 *
 * Input:         flags - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x7.
 */

extern os_error *xadfsdiscop_step_in (bits flags);
extern void adfsdiscop_step_in (bits flags);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_step_out()
 *
 * Description:   Steps a floppy disc out one track
 *
 * Input:         flags - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x8.
 */

extern os_error *xadfsdiscop_step_out (bits flags);
extern void adfsdiscop_step_out (bits flags);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_read_sectors_via_cache()
 *
 * Description:   Reads sectors of a disc using the RMA cache
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *                size - value of R4 on entry
 *                cache_handle - value of R6 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                next_data - value of R3 on exit
 *                unread - value of R4 on exit (X version only)
 *                cache_handle_out - value of R6 on exit
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0x9.
 */

extern os_error *xadfsdiscop_read_sectors_via_cache (bits flags,
      filecore_disc_address disc_addr,
      byte *data,
      int size,
      int cache_handle,
      filecore_disc_address *next_disc_addr,
      byte **next_data,
      int *unread,
      int *cache_handle_out);
extern int adfsdiscop_read_sectors_via_cache (bits flags,
      filecore_disc_address disc_addr,
      byte *data,
      int size,
      int cache_handle,
      filecore_disc_address *next_disc_addr,
      byte **next_data,
      int *cache_handle_out);

/* ------------------------------------------------------------------------
 * Function:      adfsdiscop_specify()
 *
 * Description:   Does a specify operation on a hard disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x40240 with R1 |= 0xF.
 */

extern os_error *xadfsdiscop_specify (bits flags,
      filecore_disc_address disc_addr);
extern void adfsdiscop_specify (bits flags,
      filecore_disc_address disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfs_hdc()
 *
 * Description:   Sets the address of an alternative ST506 hard disc
 *                controller
 *
 * Input:         controller - value of R2 on entry
 *                poll_location - value of R3 on entry
 *                poll_bits - value of R4 on entry
 *                enable_location - value of R5 on entry
 *                enable_bits - value of R6 on entry
 *
 * Other notes:   Calls SWI 0x40241.
 */

extern os_error *xadfs_hdc (byte *controller,
      int *poll_location,
      bits poll_bits,
      byte *enable_location,
      bits enable_bits);
extern void adfs_hdc (byte *controller,
      int *poll_location,
      bits poll_bits,
      byte *enable_location,
      bits enable_bits);

/* ------------------------------------------------------------------------
 * Function:      adfs_drives()
 *
 * Description:   Returns information on ADFS' drives
 *
 * Output:        default_drive - value of R0 on exit
 *                floppy_count - value of R1 on exit
 *                hard_disc_count - value of R2 on exit
 *
 * Other notes:   Calls SWI 0x40242.
 */

extern os_error *xadfs_drives (int *default_drive,
      int *floppy_count,
      int *hard_disc_count);
extern void adfs_drives (int *default_drive,
      int *floppy_count,
      int *hard_disc_count);

/* ------------------------------------------------------------------------
 * Function:      adfs_free_space()
 *
 * Description:   Returns information on a disc's free space
 *
 * Input:         disc_name - value of R0 on entry
 *
 * Output:        free - value of R0 on exit (X version only)
 *                max - value of R1 on exit
 *
 * Returns:       R0 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40243.
 */

extern os_error *xadfs_free_space (char const *disc_name,
      int *free,
      int *max);
extern int adfs_free_space (char const *disc_name,
      int *max);

/* ------------------------------------------------------------------------
 * Function:      adfs_retries()
 *
 * Description:   Sets the number of retries used for various operations
 *
 * Input:         mask - value of R0 on entry
 *                value - value of R1 on entry
 *
 * Output:        old_value - value of R2 on exit (X version only)
 *                new_value - value of R3 on exit
 *
 * Returns:       R2 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40244.
 */

extern os_error *xadfs_retries (bits mask,
      bits value,
      bits *old_value,
      bits *new_value);
extern bits adfs_retries (bits mask,
      bits value,
      bits *new_value);

/* ------------------------------------------------------------------------
 * Function:      adfs_describe_disc()
 *
 * Description:   Returns a disc record describing a disc's shape and
 *                format
 *
 * Input:         disc_name - value of R0 on entry
 *                disc - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x40245.
 */

extern os_error *xadfs_describe_disc (char const *disc_name,
      filecore_disc *disc);
__swi (0x40245) void adfs_describe_disc (char const *disc_name,
      filecore_disc *disc);

/* ------------------------------------------------------------------------
 * Function:      adfs_vet_format()
 *
 * Description:   Vets a format for achievability with the available
 *                hardware
 *
 * Input:         format - value of R0 on entry
 *                drive_no - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x40246.
 */

extern os_error *xadfs_vet_format (filecore_format *format,
      int drive_no);
__swi (0x40246) void adfs_vet_format (filecore_format *format,
      int drive_no);

/* ------------------------------------------------------------------------
 * Function:      adfs_controller_type()
 *
 * Description:   Returns the controller type of a driver
 *
 * Input:         drive_no - value of R0 on entry
 *
 * Output:        controller - value of R0 on exit (X version only)
 *
 * Returns:       R0 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40248.
 */

extern os_error *xadfs_controller_type (int drive_no,
      adfs_controller *controller);
__swi (0x40248) adfs_controller adfs_controller_type (int drive_no);

/* ------------------------------------------------------------------------
 * Function:      adfspowercontrol_read_spin()
 *
 * Description:   Reads the spin status of a drive
 *
 * Input:         drive_no - value of R1 on entry
 *
 * Output:        spinning - value of R2 on exit (X version only)
 *
 * Returns:       R2 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40249 with R0 = 0x0.
 */

extern os_error *xadfspowercontrol_read_spin (int drive_no,
      osbool *spinning);
extern osbool adfspowercontrol_read_spin (int drive_no);

/* ------------------------------------------------------------------------
 * Function:      adfspowercontrol_set_autospindown()
 *
 * Description:   Sets the autospindown characteristic of a drive
 *
 * Input:         drive_no - value of R1 on entry
 *                spindown_time - value of R2 on entry
 *
 * Output:        old_spindown_time - value of R3 on exit (X version only)
 *
 * Returns:       R3 (non-X version only)
 *
 * Other notes:   Calls SWI 0x40249 with R0 = 0x1.
 */

extern os_error *xadfspowercontrol_set_autospindown (int drive_no,
      int spindown_time,
      int *old_spindown_time);
extern int adfspowercontrol_set_autospindown (int drive_no,
      int spindown_time);

/* ------------------------------------------------------------------------
 * Function:      adfspowercontrol_set_spin()
 *
 * Description:   Controls drive spin directly without affecting
 *                autospindown
 *
 * Input:         drive_no - value of R1 on entry
 *                spinning - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x40249 with R0 = 0x2.
 */

extern os_error *xadfspowercontrol_set_spin (int drive_no,
      osbool spinning);
extern void adfspowercontrol_set_spin (int drive_no,
      osbool spinning);

/* ------------------------------------------------------------------------
 * Function:      adfs_set_ide_controller()
 *
 * Description:   Gives the IDE driver the details of an alternative
 *                controller
 *
 * Input:         controller - value of R2 on entry
 *                status_location - value of R3 on entry
 *                status_bits - value of R4 on entry
 *                irq_location - value of R5 on entry
 *                irq_bits - value of R6 on entry
 *                read_code - value of R7 on entry
 *                write_code - value of R8 on entry
 *
 * Other notes:   Calls SWI 0x4024A.
 */

extern os_error *xadfs_set_ide_controller (byte *controller,
      int *status_location,
      bits status_bits,
      int *irq_location,
      bits irq_bits,
      void const *read_code,
      void const *write_code);
extern void adfs_set_ide_controller (byte *controller,
      int *status_location,
      bits status_bits,
      int *irq_location,
      bits irq_bits,
      void const *read_code,
      void const *write_code);

/* ------------------------------------------------------------------------
 * Function:      adfs_ide_user_op()
 *
 * Description:   Direct user interface for low-level IDE commands
 *
 * Input:         op - value of R0 on entry
 *                commands - value of R2 on entry
 *                buffer - value of R3 on entry
 *                size - value of R4 on entry
 *                timeout - value of R5 on entry
 *
 * Output:        status - value of R0 on exit
 *                untransferred - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x4024B.
 */

extern os_error *xadfs_ide_user_op (bits op,
      byte const *commands,
      byte *buffer,
      int size,
      int timeout,
      int *status,
      int *untransferred);
extern int adfs_ide_user_op (bits op,
      byte const *commands,
      byte *buffer,
      int size,
      int timeout,
      int *status);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_mount()
 *
 * Description:   Mounts a disc, reading in the data asked for
 *
 * Input:         drive_no - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                buffer - value of R3 on entry
 *                size - value of R4 on entry
 *                disc - value of R5 on entry
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x0.
 */

extern os_error *xadfsmiscop_mount (int drive_no,
      filecore_disc_address disc_addr,
      byte *buffer,
      int size,
      filecore_disc *disc);
extern void adfsmiscop_mount (int drive_no,
      filecore_disc_address disc_addr,
      byte *buffer,
      int size,
      filecore_disc *disc);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_poll_changed()
 *
 * Description:   Polls the sequence number for a drive
 *
 * Input:         drive_no - value of R1 on entry
 *                sequence_no - value of R2 on entry
 *
 * Output:        sequence_no_out - value of R2 on exit
 *                result - value of R3 on exit
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x1.
 */

extern os_error *xadfsmiscop_poll_changed (int drive_no,
      int sequence_no,
      int *sequence_no_out,
      bits *result);
extern void adfsmiscop_poll_changed (int drive_no,
      int sequence_no,
      int *sequence_no_out,
      bits *result);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_lock_drive()
 *
 * Description:   Locks a disc in a floppy drive
 *
 * Input:         drive_no - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x2.
 */

extern os_error *xadfsmiscop_lock_drive (int drive_no);
extern void adfsmiscop_lock_drive (int drive_no);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_unlock_drive()
 *
 * Description:   Unlocks a disc in a floppy drive
 *
 * Input:         drive_no - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x3.
 */

extern os_error *xadfsmiscop_unlock_drive (int drive_no);
extern void adfsmiscop_unlock_drive (int drive_no);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_poll_period()
 *
 * Description:   Informs FileCore of the minimum period between polling
 *                for disc insertion
 *
 * Input:         disc_name - value of R1 on entry
 *
 * Output:        poll_period - value of R5 on exit
 *                media_type - value of R6 on exit
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x4.
 */

extern os_error *xadfsmiscop_poll_period (char const *disc_name,
      int *poll_period,
      char **media_type);
extern void adfsmiscop_poll_period (char const *disc_name,
      int *poll_period,
      char **media_type);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_eject_disc()
 *
 * Description:   Power-ejects the disc in the specified drive
 *
 * Input:         drive_no - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x5.
 */

extern os_error *xadfsmiscop_eject_disc (int drive_no);
extern void adfsmiscop_eject_disc (int drive_no);

/* ------------------------------------------------------------------------
 * Function:      adfsmiscop_read_info()
 *
 * Description:   Reads information on ADFS
 *
 * Output:        info - value of R0 on exit
 *
 * Other notes:   Calls SWI 0x4024C with R0 = 0x6.
 */

extern os_error *xadfsmiscop_read_info (filecore_info **info);
extern void adfsmiscop_read_info (filecore_info **info);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_verify()
 *
 * Description:   Verifies a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                size - value of R4 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                unverified - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x0.
 */

extern os_error *xadfssectordiscop_verify (bits flags,
      filecore_sector_disc_address disc_addr,
      int size,
      filecore_sector_disc_address *next_disc_addr,
      int *unverified);
extern int adfssectordiscop_verify (bits flags,
      filecore_sector_disc_address disc_addr,
      int size,
      filecore_sector_disc_address *next_disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_read_sectors()
 *
 * Description:   Reads sectors from a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *                size - value of R4 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                next_data - value of R3 on exit
 *                unread - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x1.
 */

extern os_error *xadfssectordiscop_read_sectors (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data,
      int size,
      filecore_sector_disc_address *next_disc_addr,
      byte **next_data,
      int *unread);
extern int adfssectordiscop_read_sectors (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data,
      int size,
      filecore_sector_disc_address *next_disc_addr,
      byte **next_data);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_write_sectors()
 *
 * Description:   Writes sectors to a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *                size - value of R4 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                next_data - value of R3 on exit
 *                unwritten - value of R4 on exit (X version only)
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x2.
 */

extern os_error *xadfssectordiscop_write_sectors (bits flags,
      filecore_sector_disc_address disc_addr,
      byte const *data,
      int size,
      filecore_sector_disc_address *next_disc_addr,
      byte **next_data,
      int *unwritten);
extern int adfssectordiscop_write_sectors (bits flags,
      filecore_sector_disc_address disc_addr,
      byte const *data,
      int size,
      filecore_sector_disc_address *next_disc_addr,
      byte **next_data);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_read_track()
 *
 * Description:   Reads a track from a floppy disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x3.
 */

extern os_error *xadfssectordiscop_read_track (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data);
extern void adfssectordiscop_read_track (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_read_id()
 *
 * Description:   Reads a hard disc ID
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x3.
 */

extern os_error *xadfssectordiscop_read_id (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data);
extern void adfssectordiscop_read_id (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_write_track()
 *
 * Description:   Writes a track to a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x4.
 */

extern os_error *xadfssectordiscop_write_track (bits flags,
      filecore_sector_disc_address disc_addr,
      byte const *data);
extern void adfssectordiscop_write_track (bits flags,
      filecore_sector_disc_address disc_addr,
      byte const *data);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_format_track()
 *
 * Description:   Formats a track of a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                format - value of R4 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x4, R3 = 0x0.
 */

extern os_error *xadfssectordiscop_format_track (bits flags,
      filecore_sector_disc_address disc_addr,
      filecore_track_format const *format);
extern void adfssectordiscop_format_track (bits flags,
      filecore_sector_disc_address disc_addr,
      filecore_track_format const *format);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_seek()
 *
 * Description:   Seeks to a disc location
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x5.
 */

extern os_error *xadfssectordiscop_seek (bits flags,
      filecore_sector_disc_address disc_addr);
extern void adfssectordiscop_seek (bits flags,
      filecore_sector_disc_address disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_restore()
 *
 * Description:   Does a restore operation for a disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x6.
 */

extern os_error *xadfssectordiscop_restore (bits flags,
      filecore_sector_disc_address disc_addr);
extern void adfssectordiscop_restore (bits flags,
      filecore_sector_disc_address disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_step_in()
 *
 * Description:   Steps a floppy disc in one track
 *
 * Input:         flags - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x7.
 */

extern os_error *xadfssectordiscop_step_in (bits flags);
extern void adfssectordiscop_step_in (bits flags);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_step_out()
 *
 * Description:   Steps a floppy disc out one track
 *
 * Input:         flags - value of R1 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x8.
 */

extern os_error *xadfssectordiscop_step_out (bits flags);
extern void adfssectordiscop_step_out (bits flags);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_read_sectors_via_cache()
 *
 * Description:   Reads sectors of a disc using the RMA cache
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *                data - value of R3 on entry
 *                size - value of R4 on entry
 *                cache_handle - value of R6 on entry
 *
 * Output:        next_disc_addr - value of R2 on exit
 *                next_data - value of R3 on exit
 *                unread - value of R4 on exit (X version only)
 *                cache_handle_out - value of R6 on exit
 *
 * Returns:       R4 (non-X version only)
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0x9.
 */

extern os_error *xadfssectordiscop_read_sectors_via_cache (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data,
      int size,
      int cache_handle,
      filecore_sector_disc_address *next_disc_addr,
      byte **next_data,
      int *unread,
      int *cache_handle_out);
extern int adfssectordiscop_read_sectors_via_cache (bits flags,
      filecore_sector_disc_address disc_addr,
      byte *data,
      int size,
      int cache_handle,
      filecore_sector_disc_address *next_disc_addr,
      byte **next_data,
      int *cache_handle_out);

/* ------------------------------------------------------------------------
 * Function:      adfssectordiscop_specify()
 *
 * Description:   Does a specify operation on a hard disc
 *
 * Input:         flags - value of R1 on entry
 *                disc_addr - value of R2 on entry
 *
 * Other notes:   Calls SWI 0x4024D with R1 |= 0xF.
 */

extern os_error *xadfssectordiscop_specify (bits flags,
      filecore_sector_disc_address disc_addr);
extern void adfssectordiscop_specify (bits flags,
      filecore_sector_disc_address disc_addr);

/* ------------------------------------------------------------------------
 * Function:      adfs_lock_ide()
 *
 * Description:   Locks/unlocks IDE bus - RISC O S 3.5+
 *
 * Input:         lock - value of R0 on entry
 *
 * Other notes:   Calls SWI 0x40251.
 */

extern os_error *xadfs_lock_ide (osbool lock);
__swi (0x40251) void adfs_lock_ide (osbool lock);

/* ------------------------------------------------------------------------
 * Function:      adfs_free_space64()
 *
 * Description:   Returns 64-bit information on a disc's free space - needs
 *                FileCore 2.94+ or RISC O S 3.6+
 *
 * Input:         disc_name - value of R0 on entry
 *
 * Output:        free_lo - value of R0 on exit
 *                free_hi - value of R1 on exit
 *                max - value of R2 on exit
 *
 * Other notes:   Calls SWI 0x40252.
 */

extern os_error *xadfs_free_space64 (char const *disc_name,
      bits *free_lo,
      int *free_hi,
      int *max);
extern void adfs_free_space64 (char const *disc_name,
      bits *free_lo,
      int *free_hi,
      int *max);

/* ------------------------------------------------------------------------
 * Function:      service_identify_format()
 *
 * Description:   Identify disc format name
 *
 * Input:         format - value of R0 on entry
 *
 * Output:        command - value of R0 on exit
 *                unclaimed - value of R1 on exit (X version only)
 *                disc_format_swi - value of R2 on exit
 *                disc_format_handle - value of R3 on exit
 *                layout_structure_swi - value of R4 on exit
 *                layout_structure_handle - value of R5 on exit
 *
 * Returns:       R1 (non-X version only)
 *
 * Other notes:   Calls SWI 0x30 with R1 = 0x6B.
 */

extern os_error *xservice_identify_format (char const *format,
      char **command,
      osbool *unclaimed,
      int *disc_format_swi,
      int *disc_format_handle,
      int *layout_structure_swi,
      int *layout_structure_handle);
extern osbool service_identify_format (char const *format,
      char **command,
      int *disc_format_swi,
      int *disc_format_handle,
      int *layout_structure_swi,
      int *layout_structure_handle);

/* ------------------------------------------------------------------------
 * Function:      service_display_format_help()
 *
 * Description:   Display list of available formats
 *
 * Output:        error - value of R0 on exit
 *                unclaimed - value of R1 on exit (X version only)
 *
 * Returns:       R1 (non-X version only)
 *
 * Other notes:   Calls SWI 0x30 with R0 = 0x0, R1 = 0x6C.
 */

extern os_error *xservice_display_format_help (os_error **error,
      osbool *unclaimed);
extern osbool service_display_format_help (os_error **error);

#ifdef __cplusplus
   }
#endif

#if defined NAMESPACE_OSLIB
  } 
#endif

#endif
