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

#include "test_apr.h"
#include "apr.h"
#include "apr_portable.h"


static void ssize_t_fmt(CuTest *tc)
{
    char buf[100];
    apr_ssize_t var = 0;

    sprintf(buf, "%" APR_SSIZE_T_FMT, var);
    CuAssertStrEquals(tc, buf, "0");
}

static void size_t_fmt(CuTest *tc)
{
    char buf[100];
    apr_size_t var = 0;

    sprintf(buf, "%" APR_SIZE_T_FMT, var);
    CuAssertStrEquals(tc, buf, "0");
}

static void off_t_fmt(CuTest *tc)
{
    char buf[100];
    apr_off_t var = 0;

    sprintf(buf, "%" APR_OFF_T_FMT, var);
    CuAssertStrEquals(tc, buf, "0");
}

static void pid_t_fmt(CuTest *tc)
{
    char buf[100];
    pid_t var = 0;

    sprintf(buf, "%" APR_PID_T_FMT, var);
    CuAssertStrEquals(tc, buf, "0");
}

static void int64_t_fmt(CuTest *tc)
{
    char buf[100];
    apr_int64_t var = 0;

    sprintf(buf, "%" APR_INT64_T_FMT, var);
    CuAssertStrEquals(tc, buf, "0");
}

CuSuite *testfmt(void)
{
    CuSuite *suite = CuSuiteNew("Test Formats");

    SUITE_ADD_TEST(suite, ssize_t_fmt);
    SUITE_ADD_TEST(suite, size_t_fmt);
    SUITE_ADD_TEST(suite, off_t_fmt);
    SUITE_ADD_TEST(suite, pid_t_fmt);
    SUITE_ADD_TEST(suite, int64_t_fmt);

    return suite;
}

#ifdef SINGLE_PROG
CuSuite *getsuite(void)
{
    return testfmt();
}
#endif

