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

#include "apr.h"
#include "apr_atomic.h"
#include "apr_thread_mutex.h"

#if APR_HAS_THREADS

#if defined(APR_ATOMIC_NEED_DEFAULT) || defined(APR_ATOMIC_NEED_CAS_DEFAULT)

#define NUM_ATOMIC_HASH 7
/* shift by 2 to get rid of alignment issues */
#define ATOMIC_HASH(x) (unsigned int)(((unsigned long)(x)>>2)%(unsigned int)NUM_ATOMIC_HASH)
static apr_thread_mutex_t **hash_mutex;

apr_status_t apr_atomic_init(apr_pool_t *p)
{
    int i;
    apr_status_t rv;
    hash_mutex = apr_palloc(p, sizeof(apr_thread_mutex_t*) * NUM_ATOMIC_HASH);

    for (i = 0; i < NUM_ATOMIC_HASH; i++) {
        rv = apr_thread_mutex_create(&(hash_mutex[i]),
                                     APR_THREAD_MUTEX_DEFAULT, p);
        if (rv != APR_SUCCESS) {
           return rv;
        }
    }
    return APR_SUCCESS;
}
#endif /* APR_ATOMIC_NEED_DEFAULT || APR_ATOMIC_NEED_CAS_DEFAULT */

#if defined(APR_ATOMIC_NEED_DEFAULT) 
void apr_atomic_add(volatile apr_atomic_t *mem, apr_uint32_t val) 
{
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t prev;
       
    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *mem;
        *mem += val;
        apr_thread_mutex_unlock(lock);
    }
}

void apr_atomic_set(volatile apr_atomic_t *mem, apr_uint32_t val) 
{
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t prev;

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *mem;
        *mem = val;
        apr_thread_mutex_unlock(lock);
    }
}

void apr_atomic_inc(volatile apr_uint32_t *mem) 
{
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t prev;

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *mem;
        (*mem)++;
        apr_thread_mutex_unlock(lock);
    }
}

int apr_atomic_dec(volatile apr_atomic_t *mem) 
{
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t new;

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        (*mem)--;
        new = *mem;
        apr_thread_mutex_unlock(lock);
        return new; 
    }
    return *mem; 
}

#endif /* APR_ATOMIC_NEED_DEFAULT */
#if defined(APR_ATOMIC_NEED_CAS_DEFAULT)

apr_uint32_t apr_atomic_cas(volatile apr_uint32_t *mem, long with, long cmp)
{
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    long prev;

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *(long*)mem;
        if ( prev == cmp) {
            *(long*)mem = with;
        }
        apr_thread_mutex_unlock(lock);
        return prev;
    }
    return *(long*)mem;
}
#endif /* APR_ATOMIC_NEED_CAS_DEFAULT */

#else /* !APR_HAS_THREADS */

#if !defined(apr_atomic_init)
apr_status_t apr_atomic_init(apr_pool_t *p)
{
    return APR_SUCCESS;
}
#endif /* !defined(apr_atomic_init) */

#endif /* APR_HAS_THREADS */
