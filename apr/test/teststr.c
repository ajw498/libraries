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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "apr_general.h"
#include "apr_strings.h"

static void test_strtok(apr_pool_t *p)
{
    struct {
        char *input;
        char *sep;
    }
    tc[] = {
        {
            "",
            "Z"
        },
        {
            "      asdf jkl; 77889909            \r\n\1\2\3Z",
            " \r\n\3\2\1"
        },
        {
            NULL,  /* but who cares if apr_strtok() segfaults? */
            " \t"
        },
#if 0     /* don't do this... you deserve to segfault */
        {
            "a b c              ",
            NULL
        },
#endif
        {
            "   a       b        c   ",
            ""
        },
        {
            "a              b c         ",
            " "
        }
    };
    int curtc;

    for (curtc = 0; curtc < sizeof tc / sizeof tc[0]; curtc++) {
        char *retval1, *retval2;
        char *str1, *str2;
        char *state;

        str1 = apr_pstrdup(p, tc[curtc].input);
        str2 = apr_pstrdup(p, tc[curtc].input);

        do {
            retval1 = apr_strtok(str1, tc[curtc].sep, &state);
            retval2 = strtok(str2, tc[curtc].sep);

            if (!retval1)
                assert(!retval2);
            else {
                assert(retval2);
                assert(!strcmp(retval1, retval2));
            }

            str1 = str2 = NULL; /* make sure we pass NULL on subsequent calls */
        } while (retval1);
    }
}

int main(int argc, const char * const argv[])
{
    apr_pool_t *p;

    apr_initialize();
    atexit(apr_terminate);
    apr_pool_create(&p, NULL);

    test_strtok(p);

    return 0;
}
