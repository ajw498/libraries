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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apr_file_io.h"
#include "apr_file_info.h"
#include "apr_errno.h"
#include "apr_general.h"
#include "apr_pools.h"
#include "apr_lib.h"

apr_pool_t *context;

static void closeapr(void)
{
    apr_pool_destroy(context);
    apr_terminate();
}

static void root_result(const char *path)
{
    apr_status_t status;
    char errmsg[256];
    const char *root = NULL;

    status = apr_filepath_root(&root, &path, APR_FILEPATH_NATIVE, context);
    apr_strerror(status, errmsg, sizeof(errmsg));
    if (root)
        fprintf(stderr, "\tRoot \"%s\" Path \"%s\" (%s)\n", 
                root, path, errmsg);
    else
        fprintf(stderr, "\tPath \"%s\" Error (%s)\n", 
                path, errmsg);
}

static void mergeresult(char *rootpath, char *addpath, apr_int32_t mergetype, char *tdesc)
{
    char errmsg[256];
    char *dstpath = NULL;
    apr_status_t status = apr_filepath_merge(&dstpath, 
                                strcmp(rootpath, "NULL") ? rootpath : NULL,
                                strcmp(addpath, "NULL") ? addpath : NULL,
                                mergetype, context);
    apr_strerror(status, errmsg, sizeof(errmsg));
    if (dstpath) {
        fprintf(stderr, "%s result for %s\n\tResult Path \"%s\"\n", errmsg, tdesc, dstpath);
    }
    else {
        fprintf(stderr, "%s result for %s\n", errmsg, tdesc);
    }
}

#define merge_result(r, a, t) mergeresult(r, a, t, #t)

int main(void)
{
    char rootpath[256];
    char addpath[256];
    char *eos;

    if (apr_initialize() != APR_SUCCESS) {
        fprintf(stderr, "Couldn't initialize.");
        exit(-1);
    }
    atexit(closeapr);
    if (apr_pool_create(&context, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Couldn't allocate context.");
        exit(-1);
    }

    fprintf(stdout, "Testing file truepath.\n");

    while (1) {
        fprintf(stdout, "\nEnter a root path$ ");
        if (!fgets(rootpath, 256, stdin))
            exit(0);
        for (eos = strchr(rootpath, '\0'); --eos >= rootpath; )
            if (apr_isspace(*eos))
                *eos = '\0';
        fprintf(stdout, "Enter an add path$ ");
        if (!fgets(addpath, 256, stdin))
            exit(0);
        for (eos = strchr(addpath, '\0'); --eos >= addpath; )
            if (apr_isspace(*eos))
                *eos = '\0';
        merge_result(rootpath, addpath, 0);
        merge_result(rootpath, addpath, APR_FILEPATH_NOTABOVEROOT);
        merge_result(rootpath, addpath, APR_FILEPATH_SECUREROOT);
        merge_result(rootpath, addpath, APR_FILEPATH_NOTABSOLUTE);
        merge_result(rootpath, addpath, APR_FILEPATH_NOTRELATIVE);
        root_result(rootpath);
        root_result(addpath);
    }
    return (0);
}
