/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2000-2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Apache" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/* This header file is where you should put ANY platform specific information.
 * This should be the only header file that programs need to include that 
 * actually has platform dependant code which refers to the .
 */
#ifndef APR_PORTABLE_H
#define APR_PORTABLE_H
/**
 * @file apr_portable.h
 * @brief APR Portability Routines
 */
/**
 * @defgroup APR_portability Portability Routines
 * @ingroup APR
 * @{
 */

#include "apr.h"
#include "apr_pools.h"
#include "apr_thread_proc.h"
#include "apr_file_io.h"
#include "apr_network_io.h"
#include "apr_errno.h"
#include "apr_global_mutex.h"
#include "apr_proc_mutex.h"
#include "apr_time.h"
#include "apr_dso.h"
#include "apr_shm.h"

#if APR_HAVE_DIRENT_H
#include <dirent.h>
#endif
#if APR_HAVE_FCNTL_H
#include <fcntl.h>
#endif
#if APR_HAVE_PTHREAD_H
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef WIN32
/* The primitives for Windows types */
typedef HANDLE                apr_os_file_t;
typedef HANDLE                apr_os_dir_t;
typedef SOCKET                apr_os_sock_t;
typedef HANDLE                apr_os_proc_mutex_t;
typedef HANDLE                apr_os_thread_t;
typedef HANDLE                apr_os_proc_t;
typedef DWORD                 apr_os_threadkey_t; 
typedef FILETIME              apr_os_imp_time_t;
typedef SYSTEMTIME            apr_os_exp_time_t;
typedef HANDLE                apr_os_dso_handle_t;
typedef HANDLE                apr_os_shm_t;

#elif defined(OS2)
typedef HFILE                 apr_os_file_t;
typedef HDIR                  apr_os_dir_t;
typedef int                   apr_os_sock_t;
typedef HMTX                  apr_os_proc_mutex_t;
typedef TID                   apr_os_thread_t;
typedef PID                   apr_os_proc_t;
typedef PULONG                apr_os_threadkey_t; 
typedef struct timeval        apr_os_imp_time_t;
typedef struct tm             apr_os_exp_time_t;
typedef HMODULE               apr_os_dso_handle_t;
typedef void*                 apr_os_shm_t;

#elif defined(__BEOS__)
#include <kernel/OS.h>
#include <kernel/image.h>

struct apr_os_proc_mutex_t {
	sem_id sem;
	int32  ben;
};

typedef int                   apr_os_file_t;
typedef DIR                   apr_os_dir_t;
typedef int                   apr_os_sock_t;
typedef struct apr_os_proc_mutex_t  apr_os_proc_mutex_t;
typedef thread_id             apr_os_thread_t;
typedef thread_id             apr_os_proc_t;
typedef int                   apr_os_threadkey_t;
typedef struct timeval        apr_os_imp_time_t;
typedef struct tm             apr_os_exp_time_t;
typedef image_id              apr_os_dso_handle_t;
typedef void*                 apr_os_shm_t;

#elif defined(NETWARE)
typedef int                   apr_os_file_t;
typedef DIR                   apr_os_dir_t;
typedef int                   apr_os_sock_t;
typedef NXMutex_t             apr_os_proc_mutex_t;
typedef NXThreadId_t          apr_os_thread_t;
typedef long                  apr_os_proc_t;
typedef NXKey_t               apr_os_threadkey_t; 
typedef struct timeval        apr_os_imp_time_t;
typedef struct tm             apr_os_exp_time_t;
typedef void *                apr_os_dso_handle_t;
typedef void*                 apr_os_shm_t;

#else
/* Any other OS should go above this one.  This is the lowest common
 * denominator typedefs for  all UNIX-like systems.  :)
 */

struct apr_os_proc_mutex_t {
#if APR_HAS_SYSVSEM_SERIALIZE || APR_HAS_FCNTL_SERIALIZE || APR_HAS_FLOCK_SERIALIZE
    int crossproc;
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
    pthread_mutex_t *pthread_interproc;
#endif
#if APR_HAS_THREADS
    /* If no threads, no need for thread locks */
#if APR_USE_PTHREAD_SERIALIZE
    pthread_mutex_t *intraproc;
#endif
#endif
};

typedef int                   apr_os_file_t;
typedef DIR                   apr_os_dir_t;
typedef int                   apr_os_sock_t;
typedef struct apr_os_proc_mutex_t  apr_os_proc_mutex_t;
#if APR_HAS_THREADS && APR_HAVE_PTHREAD_H 
typedef pthread_t             apr_os_thread_t;
typedef pthread_key_t         apr_os_threadkey_t;
#endif
typedef pid_t                 apr_os_proc_t;
typedef struct timeval        apr_os_imp_time_t;
typedef struct tm             apr_os_exp_time_t;
/* dso types... */
#if defined(HPUX) || defined(HPUX10) || defined(HPUX11)
#include <dl.h>
typedef shl_t                 apr_os_dso_handle_t;
#elif defined(DARWIN)
#include <mach-o/dyld.h>
typedef NSModule              apr_os_dso_handle_t;
#else
typedef void *                apr_os_dso_handle_t;
#endif
typedef void*                 apr_os_shm_t;

#endif

/**
 * @typedef apr_os_sock_t
 * @brief alias for local OS socket
 */
/**
 * everything APR needs to know about an active socket to construct
 * an APR socket from it; currently, this is platform-independent
 */
struct apr_os_sock_info_t {
    apr_os_sock_t *os_sock; /**< always required */
    struct sockaddr *local; /**< NULL if not yet bound */
    struct sockaddr *remote; /**< NULL if not connected */
    int family;             /**< always required (APR_INET, APR_INET6, etc. */
    int type;               /**< always required (SOCK_STREAM, SOCK_DGRAM, etc. */
};

typedef struct apr_os_sock_info_t apr_os_sock_info_t;

#if APR_PROC_MUTEX_IS_GLOBAL
#define apr_os_global_mutex_t apr_os_proc_mutex_t
#define apr_os_global_mutex_get apr_os_proc_mutex_get
#else
    struct apr_os_global_mutex_t {
        apr_pool_t *pool;
        apr_proc_mutex_t *proc_mutex;
#if APR_HAS_THREADS
        apr_thread_mutex_t *thread_mutex;
#endif /* APR_HAS_THREADS */
    };
    typedef struct apr_os_global_mutex_t apr_os_global_mutex_t;

APR_DECLARE(apr_status_t) apr_os_global_mutex_get(apr_os_global_mutex_t *ospmutex, 
                                                apr_global_mutex_t *pmutex);
#endif


/**
 * convert the file from apr type to os specific type.
 * @param thefile The os specific file we are converting to
 * @param file The apr file to convert.
 * @remark On Unix, it is only possible to get a file descriptor from 
 *         an apr file type.
 */
APR_DECLARE(apr_status_t) apr_os_file_get(apr_os_file_t *thefile,
                                          apr_file_t *file);

/**
 * convert the dir from apr type to os specific type.
 * @param thedir The os specific dir we are converting to
 * @param dir The apr dir to convert.
 */   
APR_DECLARE(apr_status_t) apr_os_dir_get(apr_os_dir_t **thedir, 
                                         apr_dir_t *dir);

/**
 * Convert the socket from an apr type to an OS specific socket
 * @param thesock The socket to convert.
 * @param sock The os specifc equivelant of the apr socket..
 */
APR_DECLARE(apr_status_t) apr_os_sock_get(apr_os_sock_t *thesock,
                                          apr_socket_t *sock);

/**
 * Convert the proc mutex from os specific type to apr type
 * @param ospmutex The os specific proc mutex we are converting to.
 * @param pmutex The apr proc mutex to convert.
 */
APR_DECLARE(apr_status_t) apr_os_proc_mutex_get(apr_os_proc_mutex_t *ospmutex, 
                                                apr_proc_mutex_t *pmutex);

/**
 * Get the exploded time in the platforms native format.
 * @param ostime the native time format
 * @param aprtime the time to convert
 */
APR_DECLARE(apr_status_t) apr_os_exp_time_get(apr_os_exp_time_t **ostime,
                                 apr_time_exp_t *aprtime);

/**
 * Get the imploded time in the platforms native format.
 * @param ostime the native time format
 * @param aprtimethe time to convert
 */
APR_DECLARE(apr_status_t) apr_os_imp_time_get(apr_os_imp_time_t **ostime, 
                                              apr_time_t *aprtime);

/**
 * convert the shm from apr type to os specific type.
 * @param osshm The os specific shm representation
 * @param shm The apr shm to convert.
 */   
APR_DECLARE(apr_status_t) apr_os_shm_get(apr_os_shm_t *osshm,
                                         apr_shm_t *shm);

#if APR_HAS_THREADS || defined(DOXYGEN)
/** 
 * @defgroup APR_PORT_Thread Thread portability Routines
 * @{ 
 */
/**
 * convert the thread to os specific type from apr type.
 * @param thethd The apr thread to convert
 * @param thd The os specific thread we are converting to
 */
APR_DECLARE(apr_status_t) apr_os_thread_get(apr_os_thread_t **thethd, 
                                            apr_thread_t *thd);

/**
 * convert the thread private memory key to os specific type from an apr type.
 * @param thekey The apr handle we are converting from.
 * @param key The os specific handle we are converting to.
 */
APR_DECLARE(apr_status_t) apr_os_threadkey_get(apr_os_threadkey_t *thekey,
                                               apr_threadkey_t *key);

/**
 * convert the thread from os specific type to apr type.
 * @param thd The apr thread we are converting to.
 * @param thethd The os specific thread to convert
 * @param cont The pool to use if it is needed.
 */
APR_DECLARE(apr_status_t) apr_os_thread_put(apr_thread_t **thd,
                                            apr_os_thread_t *thethd,
                                            apr_pool_t *cont);

/**
 * convert the thread private memory key from os specific type to apr type.
 * @param key The apr handle we are converting to.
 * @param thekey The os specific handle to convert
 * @param cont The pool to use if it is needed.
 */
APR_DECLARE(apr_status_t) apr_os_threadkey_put(apr_threadkey_t **key,
                                               apr_os_threadkey_t *thekey,
                                               apr_pool_t *cont);
/**
 * Get the thread ID
 */
APR_DECLARE(apr_os_thread_t) apr_os_thread_current(void);

/**
 * Compare two thread id's
 * @param tid1 1st Thread ID to compare
 * @param tid2 2nd Thread ID to compare
 */ 
APR_DECLARE(int) apr_os_thread_equal(apr_os_thread_t tid1, 
                                     apr_os_thread_t tid2);

/** @} */
#endif /* APR_HAS_THREADS */

/**
 * convert the file from os specific type to apr type.
 * @param file The apr file we are converting to.
 * @param thefile The os specific file to convert
 * @param flags The flags that were used to open this file.
 * @param cont The pool to use if it is needed.
 * @remark On Unix, it is only possible to put a file descriptor into
 *         an apr file type.
 */
APR_DECLARE(apr_status_t) apr_os_file_put(apr_file_t **file,
                                          apr_os_file_t *thefile,
                                          apr_int32_t flags, apr_pool_t *cont); 

/**
 * convert the dir from os specific type to apr type.
 * @param dir The apr dir we are converting to.
 * @param thedir The os specific dir to convert
 * @param cont The pool to use when creating to apr directory.
 */
APR_DECLARE(apr_status_t) apr_os_dir_put(apr_dir_t **dir,
                                         apr_os_dir_t *thedir,
                                         apr_pool_t *cont); 

/**
 * Convert a socket from the os specific type to the apr type
 * @param sock The pool to use.
 * @param thesock The socket to convert to.
 * @param cont The socket we are converting to an apr type.
 */
APR_DECLARE(apr_status_t) apr_os_sock_put(apr_socket_t **sock, 
                                          apr_os_sock_t *thesock, 
                                          apr_pool_t *cont);

/**
 * Create a socket from an existing descriptor and local and remote
 * socket addresses.
 * @param apr_sock The new socket that has been set up
 * @param os_sock_info The os representation of the socket handle and
 *        other characteristics of the socket
 * @param cont The pool to use
 * @remark If you only know the descriptor/handle or if it isn't really
 *         a true socket, use apr_os_sock_put() instead.
 */
APR_DECLARE(apr_status_t) apr_os_sock_make(apr_socket_t **apr_sock,
                                           apr_os_sock_info_t *os_sock_info,
                                           apr_pool_t *cont);

/**
 * Convert the proc mutex from os specific type to apr type
 * @param pmutex The apr proc mutex we are converting to.
 * @param ospmutex The os specific proc mutex to convert.
 * @param cont The pool to use if it is needed.
 */
APR_DECLARE(apr_status_t) apr_os_proc_mutex_put(apr_proc_mutex_t **pmutex,
                                                apr_os_proc_mutex_t *ospmutex,
                                                apr_pool_t *cont); 

/**
 * Put the imploded time in the APR format.
 * @param aprtime the APR time format
 * @param ostime the time to convert
 * @param cont the pool to use if necessary
 */
APR_DECLARE(apr_status_t) apr_os_imp_time_put(apr_time_t *aprtime,
                                              apr_os_imp_time_t **ostime,
                                              apr_pool_t *cont); 

/**
 * Put the exploded time in the APR format.
 * @param aprtime the APR time format
 * @param ostime the time to convert
 * @param cont the pool to use if necessary
 */
APR_DECLARE(apr_status_t) apr_os_exp_time_put(apr_time_exp_t *aprtime,
                                              apr_os_exp_time_t **ostime,
                                              apr_pool_t *cont); 

/**
 * convert the shared memory from os specific type to apr type.
 * @param shm The apr shm representation of osshm
 * @param osshm The os specific shm identity
 * @param cont The pool to use if it is needed.
 * @remark On fork()ed architectures, this is typically nothing more than
 * the memory block mapped.  On non-fork architectures, this is typically
 * some internal handle to pass the mapping from process to process.
 */
APR_DECLARE(apr_status_t) apr_os_shm_put(apr_shm_t **shm,
                                         apr_os_shm_t *osshm,
                                         apr_pool_t *cont); 


#if APR_HAS_DSO || defined(DOXYGEN)
/** 
 * @defgroup apr_port_DSO DSO (Dynamic Loading) Portabiliity Routines
 * @{
 */
/**
 * convert the dso handle from os specific to apr
 * @param dso The apr handle we are converting to
 * @param thedso the os specific handle to convert
 * @param pool the pool to use if it is needed
 */
APR_DECLARE(apr_status_t) apr_os_dso_handle_put(apr_dso_handle_t **dso,
                                                apr_os_dso_handle_t thedso,
                                                apr_pool_t *pool);

/**
 * convert the apr dso handle into an os specific one
 * @param aprdso The apr dso handle to convert
 * @param dso The os specific dso to return
 */
APR_DECLARE(apr_status_t) apr_os_dso_handle_get(apr_os_dso_handle_t *dso,
                                                apr_dso_handle_t *aprdso);

#if APR_HAS_OS_UUID
/**
 * Private: apr-util's apr_uuid module when supported by the platform
 */
APR_DECLARE(apr_status_t) apr_os_uuid_get(unsigned char *uuid_data);
#endif

/** @} */
#endif /* APR_HAS_DSO */


#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* ! APR_PORTABLE_H */