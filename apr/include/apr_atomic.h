/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2000-2003 The Apache Software Foundation.  All rights
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
 *
 * Portions of this software are based upon public domain software
 * originally written at the National Center for Supercomputing Applications,
 * University of Illinois, Urbana-Champaign.
 */

#ifndef APR_ATOMIC_H
#define APR_ATOMIC_H

/**
 * @file apr_atomic.h
 * @brief APR Atomic Operations
 */

#include "apr.h"
#include "apr_pools.h"

/* Platform includes for atomics */
#if defined(NETWARE) || defined(__MVS__) /* OS/390 */
#include <stdlib.h>
#elif defined(__FreeBSD__)
#include <machine/atomic.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup apr_atomic Atomic Operations
 * @ingroup APR 
 * @{
 */

/* easiest way to get these documented for the moment */
#if defined(DOXYGEN)
/**
 * structure for holding a atomic value.
 * this number >only< has a 24 bit size on some platforms
 */
typedef apr_atomic_t;

/**
 * this function is required on some platforms to initialize the
 * atomic operation's internal structures
 * @param p pool
 * @return APR_SUCCESS on successful completion
 */
apr_status_t apr_atomic_init(apr_pool_t *p);
/**
 * read the value stored in a atomic variable
 * @param mem the pointer
 * @warning on certain platforms this number is not stored
 * directly in the pointer. in others it is 
 * @deprecated
 */
apr_uint32_t apr_atomic_read(volatile apr_atomic_t *mem);
/**
 * set the value for atomic.
 * @param mem the pointer
 * @param val the value
 * @deprecated
 */
void apr_atomic_set(volatile apr_atomic_t *mem, apr_uint32_t val);
/**
 * Add 'val' to the atomic variable
 * @param mem pointer to the atomic value
 * @param val the addition
 * @deprecated
 */
void apr_atomic_add(volatile apr_atomic_t *mem, apr_uint32_t val);

/**
 * increment the atomic variable by 1
 * @param mem pointer to the atomic value
 * @deprecated
 */
void apr_atomic_inc(volatile apr_atomic_t *mem);

/**
 * decrement the atomic variable by 1
 * @param mem pointer to the atomic value
 * @return zero if the value is zero, otherwise non-zero
 * @deprecated
 */
int apr_atomic_dec(volatile apr_atomic_t *mem);

/**
 * compare the atomic's value with cmp.
 * If they are the same swap the value with 'with'
 * @param mem pointer to the atomic value
 * @param with what to swap it with
 * @param cmp the value to compare it to
 * @return the old value of the atomic
 * @warning do not mix apr_atomic's with the CAS function.
 * @deprecated
 * on some platforms they may be implemented by different mechanisms
 */
apr_uint32_t apr_atomic_cas(volatile apr_uint32_t *mem, long with, long cmp);


/*
 * Atomic operations on 32-bit values
 * Note: Each of these functions internally implements a memory barrier
 * on platforms that require it
 */

/**
 * atomically read an apr_uint32_t from memory
 * @param mem the pointer
 */
apr_uint32_t apr_atomic_read32(volatile apr_uint32_t *mem);

/**
 * atomically set an apr_uint32_t in memory
 * @param mem pointer to the object
 */
void apr_atomic_set32(volatile apr_uint32_t *mem, apr_uint32_t val);

/**
 * atomically add 'val' to an apr_uint32_t
 * @param mem pointer to the object
 * @param val amount to add
 */
void apr_atomic_add32(volatile apr_uint32_t *mem, apr_uint32_t val);

/**
 * atomically subtract 'val' from an apr_uint32_t
 * @param mem pointer to the object
 * @param val amount to subtract
 */
void apr_atomic_sub32(volatile apr_uint32_t *mem, apr_uint32_t val);

/**
 * atomically increment an apr_uint32_t by 1
 * @param mem pointer to the object
 */
void apr_atomic_inc32(volatile apr_uint32_t *mem);

/**
 * atomically decrement an apr_uint32_t by 1
 * @param mem pointer to the atomic value
 * @return zero if the value becomes zero on decrement, otherwise non-zero
 */
int apr_atomic_dec32(volatile apr_uint32_t *mem);

/**
 * compare an apr_uint32_t's value with 'cmp'.
 * If they are the same swap the value with 'with'
 * @param mem pointer to the value
 * @param with what to swap it with
 * @param cmp the value to compare it to
 * @return the old value of *mem
 */
apr_uint32_t apr_atomic_cas32(volatile apr_uint32_t *mem, apr_uint32_t with,
                              apr_uint32_t cmp);

/**
 * exchange an apr_uint32_t's value with 'val'.
 * @param mem pointer to the value
 * @param val what to swap it with
 * @return the old value of *mem
 */
apr_uint32_t apr_atomic_xchg32(volatile apr_uint32_t *mem, apr_uint32_t val);

/**
 * compare the pointer's value with cmp.
 * If they are the same swap the value with 'with'
 * @param mem pointer to the pointer
 * @param with what to swap it with
 * @param cmp the value to compare it to
 * @return the old value of the pointer
 */
void *apr_atomic_casptr(volatile void **mem, void *with, const void *cmp);
#else /* !DOXYGEN */

/* The following definitions provide optimized, OS-specific
 * implementations of the APR atomic functions on various
 * platforms.  Any atomic operation that isn't redefined as
 * a macro here will be declared as a function later, and
 * apr_atomic.c will provide a mutex-based default implementation.
 */

#if defined(WIN32)

#define apr_atomic_t LONG

#define apr_atomic_init(pool)        APR_SUCCESS
#define apr_atomic_add(mem, val)     InterlockedExchangeAdd(mem,val)
#define apr_atomic_inc(mem)          InterlockedIncrement(mem)
#define apr_atomic_dec(mem)          InterlockedDecrement(mem)
#define apr_atomic_set(mem, val)     InterlockedExchange(mem, val)
#define apr_atomic_read(mem)         (*mem)
#define apr_atomic_cas(mem,with,cmp) InterlockedCompareExchange(mem,with,cmp)
#define apr_atomic_casptr(mem,with,cmp) InterlockedCompareExchangePointer(mem,with,cmp)

/* 
 * Remapping function pointer type to accept apr_uint32_t's type-safely
 * as the arguments for as our apr_atomic_foo32 Functions
 */
typedef WINBASEAPI apr_uint32_t (WINAPI apr_atomic_win32_ptr_fn)
                                           (apr_uint32_t volatile *);
typedef WINBASEAPI apr_uint32_t (WINAPI apr_atomic_win32_ptr_val_fn)
                                           (apr_uint32_t volatile *, 
                                            apr_uint32_t);
typedef WINBASEAPI apr_uint32_t (WINAPI apr_atomic_win32_ptr_val_val_fn)
                                           (apr_uint32_t volatile *, 
                                            apr_uint32_t, apr_uint32_t);

#define apr_atomic_add32(mem, val)      \
    ((apr_atomic_win32_ptr_val_fn)InterlockedExchangeAdd)(mem,val)
#define apr_atomic_sub32(mem, val)      \
    ((apr_atomic_win32_ptr_val_fn)InterlockedExchangeSub)(mem,val)
#define apr_atomic_inc32(mem)           \
    ((apr_atomic_win32_ptr_fn)InterlockedIncrement)(mem)
#define apr_atomic_dec32(mem)           \
    ((apr_atomic_win32_ptr_fn)InterlockedDecrement)(mem)
#define apr_atomic_set32(mem, val)      \
    ((apr_atomic_win32_ptr_val_fn)InterlockedExchange)(mem,val)
#define apr_atomic_read32(mem)          (*mem)
#define apr_atomic_cas32(mem,with,cmp)  \
    ((apr_atomic_win32_ptr_val_val_fn)InterlockedCompareExchange)(mem,val)
#define apr_atomic_xchg32(mem,val)      \
    ((apr_atomic_win32_ptr_val_fn)InterlockedExchange)(mem,val)

#elif defined(NETWARE)

#define apr_atomic_init(pool)           APR_SUCCESS
#define apr_atomic_add32(mem, val)      atomic_add((unsigned long *)(mem),(unsigned long)(val))
#define apr_atomic_sub32(mem, val)      atomic_sub((unsigned long *)(mem),(unsigned long)(val))
#define apr_atomic_inc32(mem)           atomic_inc((unsigned long *)(mem))
#define apr_atomic_set32(mem, val)      (*mem = val)
#define apr_atomic_read32(mem)          (*mem)
#define apr_atomic_cas32(mem,with,cmp)  atomic_cmpxchg((unsigned long *)(mem),(unsigned long)(cmp),(unsigned long)(with))
#define apr_atomic_xchg32(mem, val)     atomic_xchg((unsigned long *)(mem),(unsigned long)val)
    
int apr_atomic_dec32(apr_uint32_t *mem);
void *apr_atomic_casptr(void **mem, void *with, const void *cmp);

#define APR_OVERRIDE_ATOMIC_READ32  1
#define APR_OVERRIDE_ATOMIC_SET32   1
#define APR_OVERRIDE_ATOMIC_ADD32   1
#define APR_OVERRIDE_ATOMIC_SUB32   1
#define APR_OVERRIDE_ATOMIC_INC32   1
#define APR_OVERRIDE_ATOMIC_DEC32   1
#define APR_OVERRIDE_ATOMIC_CAS32   1
#define APR_OVERRIDE_ATOMIC_XCHG32  1

#define APR_OVERRIDE_ATOMIC_CASPTR 1

inline int apr_atomic_dec32(apr_uint32_t *mem) 
{
    atomic_dec((unsigned long *)mem);
    return *mem; 
}

inline void *apr_atomic_casptr(void **mem, void *with, const void *cmp)
{
    return (void*)atomic_cmpxchg((unsigned long *)mem,(unsigned long)cmp,(unsigned long)with);
}

#define apr_atomic_read(mem)            apr_atomic_read32(mem)
#define apr_atomic_set(mem, val)        apr_atomic_set32(mem, val)
#define apr_atomic_add(mem, val)        apr_atomic_add32(mem,val)
#define apr_atomic_inc(mem)             apr_atomic_inc32(mem)
#define apr_atomic_dec(mem)             apr_atomic_dec32(mem)
#define apr_atomic_cas(mem,with,cmp)    apr_atomic_cas32(mem,with,cmp)

#define APR_OVERRIDE_ATOMIC_READ    1
#define APR_OVERRIDE_ATOMIC_SET     1
#define APR_OVERRIDE_ATOMIC_ADD     1
#define APR_OVERRIDE_ATOMIC_INC     1
#define APR_OVERRIDE_ATOMIC_DEC     1
#define APR_OVERRIDE_ATOMIC_CAS     1

#elif defined(__FreeBSD__)

#define apr_atomic_t apr_uint32_t
#define apr_atomic_add(mem, val)     atomic_add_int(mem,val)
#define apr_atomic_dec(mem)          atomic_subtract_int(mem,1)
#define apr_atomic_inc(mem)          atomic_add_int(mem,1)
#define apr_atomic_set(mem, val)     atomic_set_int(mem, val)
#define apr_atomic_read(mem)         (*mem)

#define apr_atomic_add32(mem, val)        apr_atomic_add(mem, val)
#define apr_atomic_dec32(mem)             apr_atomic_dec(mem)
#define apr_atomic_inc32(mem)             apr_atomic_inc(mem)
#define apr_atomic_set32(mem)             apr_atomic_set(mem)
#define apr_atomic_read32(mem)            apr_atomic_read(mem)

#elif (defined(__linux__) || defined(__EMX__)) && defined(__i386__) && !APR_FORCE_ATOMIC_GENERIC

#define apr_atomic_t apr_uint32_t
#define apr_atomic_cas(mem,with,cmp) \
({ apr_atomic_t prev; \
    asm volatile ("lock; cmpxchgl %1, %2"              \
         : "=a" (prev)               \
         : "r" (with), "m" (*(mem)), "0"(cmp) \
         : "memory"); \
    prev;})

#define apr_atomic_add(mem, val)                                \
 asm volatile ("lock; addl %1, %0"                              \
    :                                                           \
    : "m" (*(mem)), "r" (val)                                   \
    : "memory")

#define apr_atomic_sub(mem, val)                                \
 asm volatile ("lock; subl %1, %0"                              \
    :                                                           \
    : "m" (*(mem)), "r" (val)                                   \
    : "memory")

#define apr_atomic_dec(mem)                                     \
({ int prev;                                                    \
   asm volatile ("mov $0, %%eax;\n\t"                           \
                 "lock; decl %1;\n\t"                           \
                 "setnz %%al;\n\t"                              \
                 "mov %%eax, %0"                                \
                 : "=r" (prev)                                  \
                 : "m" (*(mem))                                 \
                 : "memory", "%eax");                           \
   prev;})

#define apr_atomic_inc(mem)                                     \
 asm volatile ("lock; incl %0"                                  \
    :                                                           \
    : "m" (*(mem))                                              \
    : "memory")

#define apr_atomic_set(mem, val)     (*(mem) = val)
#define apr_atomic_read(mem)        (*(mem))

#define apr_atomic_cas32(mem, with, cmp)  apr_atomic_cas(mem, with, cmp)
#define apr_atomic_add32(mem, val)        apr_atomic_add(mem, val)
#define apr_atomic_sub32(mem, val)        apr_atomic_sub(mem, val)
#define apr_atomic_dec32(mem)             apr_atomic_dec(mem)
#define apr_atomic_inc32(mem)             apr_atomic_inc(mem)
#define apr_atomic_set32(mem, val)        apr_atomic_set(mem, val)
#define apr_atomic_read32(mem)            apr_atomic_read(mem)

#define apr_atomic_xchg32(mem,val) \
({ apr_uint32_t prev = val; \
    asm volatile ("lock; xchgl %0, %1"              \
         : "=r" (prev)               \
         : "m" (*(mem)), "0"(prev) \
         : "memory"); \
    prev;})

/*#define apr_atomic_init(pool)        APR_SUCCESS*/

#elif defined(__MVS__) /* OS/390 */

#define apr_atomic_t cs_t

apr_int32_t apr_atomic_add(volatile apr_atomic_t *mem, apr_int32_t val);
apr_uint32_t apr_atomic_cas(volatile apr_atomic_t *mem, apr_uint32_t swap, 
                            apr_uint32_t cmp);
#define APR_OVERRIDE_ATOMIC_ADD 1
#define APR_OVERRIDE_ATOMIC_CAS 1

#define apr_atomic_inc(mem)          apr_atomic_add(mem, 1)
#define apr_atomic_dec(mem)          apr_atomic_add(mem, -1)
/*#define apr_atomic_init(pool)        APR_SUCCESS*/

/* warning: the following two operations, _read and _set, are atomic
 * if the memory variables are aligned (the usual case).  
 * 
 * If you try really hard and manage to mis-align them, they are not 
 * guaranteed to be atomic on S/390.  But then your program will blow up 
 * with SIGBUS on a sparc, or with a S0C6 abend if you use the mis-aligned 
 * variables with other apr_atomic_* operations on OS/390.
 */

#define apr_atomic_read(p)           (*p)
#define apr_atomic_set(mem, val)     (*mem = val)

#endif /* end big if-elseif switch for platform-specifics */


/* Default implementation of the atomic API
 * The definitions above may override some or all of the
 * atomic functions with optimized, platform-specific versions.
 * Any operation that hasn't been overridden as a macro above
 * is declared as a function here, unless APR_OVERRIDE_ATOMIC_[OPERATION]
 * is defined.  (The purpose of the APR_OVERRIDE_ATOMIC_* is
 * to allow a platform to declare an apr_atomic_*() function
 * with a different signature than the default.)
 */

#if !defined(apr_atomic_t)
#define apr_atomic_t apr_uint32_t
#endif

#if !defined(apr_atomic_init) && !defined(APR_OVERRIDE_ATOMIC_INIT)
apr_status_t apr_atomic_init(apr_pool_t *p);
#endif

#if !defined(apr_atomic_read) && !defined(APR_OVERRIDE_ATOMIC_READ)
#define apr_atomic_read(p)  *p
#endif

#if !defined(apr_atomic_set) && !defined(APR_OVERRIDE_ATOMIC_SET)
void apr_atomic_set(volatile apr_atomic_t *mem, apr_uint32_t val);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_add) && !defined(APR_OVERRIDE_ATOMIC_ADD)
void apr_atomic_add(volatile apr_atomic_t *mem, apr_uint32_t val);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_inc) && !defined(APR_OVERRIDE_ATOMIC_INC)
void apr_atomic_inc(volatile apr_atomic_t *mem);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_dec) && !defined(APR_OVERRIDE_ATOMIC_DEC)
int apr_atomic_dec(volatile apr_atomic_t *mem);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_cas) && !defined(APR_OVERRIDE_ATOMIC_CAS)
apr_uint32_t apr_atomic_cas(volatile apr_uint32_t *mem,long with,long cmp);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_read32) && !defined(APR_OVERRIDE_ATOMIC_READ32)
#define apr_atomic_read32(p)  *p
#endif

#if !defined(apr_atomic_set32) && !defined(APR_OVERRIDE_ATOMIC_SET32)
void apr_atomic_set32(volatile apr_uint32_t *mem, apr_uint32_t val);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_add32) && !defined(APR_OVERRIDE_ATOMIC_ADD32)
void apr_atomic_add32(volatile apr_uint32_t *mem, apr_uint32_t val);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_sub32) && !defined(APR_OVERRIDE_ATOMIC_SUB32)
void apr_atomic_sub32(volatile apr_uint32_t *mem, apr_uint32_t val);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_inc32) && !defined(APR_OVERRIDE_ATOMIC_INC32)
void apr_atomic_inc32(volatile apr_uint32_t *mem);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_dec32) && !defined(APR_OVERRIDE_ATOMIC_DEC32)
int apr_atomic_dec32(volatile apr_uint32_t *mem);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_cas32) && !defined(APR_OVERRIDE_ATOMIC_CAS32)
apr_uint32_t apr_atomic_cas32(volatile apr_uint32_t *mem, apr_uint32_t with,
			      apr_uint32_t cmp);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_xchg32) && !defined(APR_OVERRIDE_ATOMIC_XCHG32)
apr_uint32_t apr_atomic_xchg32(volatile apr_uint32_t *mem, apr_uint32_t val);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif

#if !defined(apr_atomic_casptr) && !defined(APR_OVERRIDE_ATOMIC_CASPTR)
#if APR_SIZEOF_VOIDP == 4
#define apr_atomic_casptr(mem, with, cmp) (void *)apr_atomic_cas((apr_uint32_t *)(mem), (long)(with), (long)cmp)
#else
void *apr_atomic_casptr(volatile void **mem, void *with, const void *cmp);
#define APR_ATOMIC_NEED_DEFAULT_INIT 1
#endif
#endif

#ifndef APR_ATOMIC_NEED_DEFAULT_INIT
#define APR_ATOMIC_NEED_DEFAULT_INIT 0
#endif

/* If we're using the default versions of any of the atomic functions,
 * we'll need the atomic init to set up mutexes.  If a platform-specific
 * override above has replaced the atomic_init with a macro, it's an error.
 */
#if APR_ATOMIC_NEED_DEFAULT_INIT
#if defined(apr_atomic_init) || defined(APR_OVERRIDE_ATOMIC_INIT)
#error Platform has redefined apr_atomic_init, but other default atomics require a default apr_atomic_init
#endif
#endif /* APR_ATOMIC_NEED_DEFAULT_INIT */

#endif /* !DOXYGEN */

/** @} */

#ifdef __cplusplus
}
#endif

#endif	/* !APR_ATOMIC_H */
