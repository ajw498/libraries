/* 
   utils tests
   Copyright (C) 2001-2002, Joe Orton <joe@manyfish.co.uk>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <errno.h> /* for the EFOO definitions in str_errors */

#include "ne_utils.h"
#include "ne_md5.h"
#include "ne_alloc.h"
#include "ne_dates.h"
#include "ne_string.h"

#include "tests.h"

static const struct {
    const char *status;
    int major, minor, code;
    const char *rp;
} accept_sl[] = {
    /* These are really valid. */
    { "HTTP/1.1 200 OK", 1, 1, 200, "OK" },
    { "HTTP/1.1000 200 OK", 1, 1000, 200, "OK" },
    { "HTTP/1000.1000 200 OK", 1000, 1000, 200, "OK" },
    { "HTTP/00001.1 200 OK", 1, 1, 200, "OK" },
    { "HTTP/1.00001 200 OK", 1, 1, 200, "OK" },
    { "HTTP/99.99 999 99999", 99, 99, 999, "99999" },
    { "HTTP/1.1 100 ", 1, 1, 100, "" },

    /* these aren't really valid but we should be able to parse them. */
    { "HTTP/1.1 100", 1, 1, 100, "" },
    { "HTTP/1.1   200   OK", 1, 1, 200, "OK" },
    { "   HTTP/1.1 200 OK", 1, 1, 200, "OK" },
    { "Norman is a dog HTTP/1.1 200 OK", 1, 1, 200, "OK" },
    { NULL }
};

static const char *bad_sl[] = {
    "",
    "HTTP/1.1 1000 OK",
    "HTTP/1.1 1000",
    "HTTP/-1.1 100 OK",
    "HTTP/1.1 -100 OK",
    "HTTP/ 200 OK",
    "HTTP/",
    NULL
};  

static int status_lines(void)
{
    ne_status s;
    int n;

    for (n = 0; accept_sl[n].status != NULL; n++) {
	ONV(ne_parse_statusline(accept_sl[n].status, &s),
	    ("valid #%d: parse", n));
	ONV(accept_sl[n].major != s.major_version, ("valid #%d: major", n));
	ONV(accept_sl[n].minor != s.minor_version, ("valid #%d: minor", n));
	ONV(accept_sl[n].code != s.code, ("valid #%d: code", n));
	ONV(strcmp(accept_sl[n].rp, s.reason_phrase), 
	    ("valid #%d: reason phrase", n));
    }
    
    for (n = 0; bad_sl[n] != NULL; n++) {
	ONV(ne_parse_statusline(bad_sl[n], &s) == 0, 
	    ("invalid #%d", n));
    }

    return OK;
}

static int md5(void)
{
    unsigned char buf[17] = {0}, buf2[17] = {0};
    char ascii[33] = {0};

    ne_md5_to_ascii(ne_md5_buffer("", 0, buf), ascii);
    ONN("MD5(null)", strcmp(ascii, "d41d8cd98f00b204e9800998ecf8427e"));
    
    ne_md5_to_ascii(ne_md5_buffer("foobar", 7, buf), ascii);
    ONN("MD5(foobar)", strcmp(ascii, "b4258860eea29e875e2ee4019763b2bb"));

    ne_ascii_to_md5(ascii, buf2);

    ON(memcmp(buf, buf2, 16));
    
    return OK;
}

static int md5_alignment(void)
{
    char *bb = ne_malloc(66);
    struct ne_md5_ctx ctx;

    /* regression test for a bug in md5.c in <0.15.0 on SPARC, where
     * the process_bytes function would SIGBUS if the buffer argument
     * isn't 32-bit aligned. Won't trigger on x86 though. */
    ne_md5_init_ctx(&ctx);
    ne_md5_process_bytes(bb + 1, 65, &ctx);
    free(bb);

    return OK;
}

static int base64(void)
{
#define B64B(x, l, y) \
do { char *_b = ne_base64(x, l); \
ONV(strcmp(_b, y), ("B64(\"%s\") gave \"%s\" not \"%s\"", x, _b, y)); \
free(_b); } while (0)
#define B64(x, y) B64B(x, strlen(x), y)

    /* invent these with 
     *  $ printf "string" | uuencode -m blah
     */
    B64("a", "YQ==");
    B64("bb", "YmI=");
    B64("ccc", "Y2Nj");
    B64("Hello, world", "SGVsbG8sIHdvcmxk");
    B64("Aladdin:open sesame", "QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    B64("I once saw a dog called norman.\n", 
	"SSBvbmNlIHNhdyBhIGRvZyBjYWxsZWQgbm9ybWFuLgo=");
    B64("The quick brown fox jumped over the lazy dog", 
	"VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgbGF6eSBkb2c=");

    /* binary data..
     *   $ printf "string" | wc -c # get the length
     *   $ printf "string" | uuencode -m blah # get the base64
     */
    B64B("\0\0\0\0\0\n", 6, "AAAAAAAK");
    B64B("I once wished \0 upon a \0 fish.", 30, 
	 "SSBvbmNlIHdpc2hlZCAAIHVwb24gYSAAIGZpc2gu");

#undef B64
#undef B64B
    return OK;
}

static const struct {
    const char *str;
    time_t time;
    enum { d_rfc1123, d_iso8601, d_rfc1036 } type;
} good_dates[] = {
    { "Fri, 08 Jun 2001 22:59:46 GMT", 992041186, d_rfc1123 },
    { "Friday, 08-Jun-01 22:59:46 GMT", 992041186, d_rfc1036 },
    /* some different types of ISO8601 dates. */
    { "2001-06-08T22:59:46Z", 992041186, d_iso8601 },
    { "2001-06-08T22:59:46.9Z", 992041186, d_iso8601 },
    { "2001-06-08T26:00:46+03:01", 992041186, d_iso8601 },
    { "2001-06-08T20:58:46-02:01", 992041186, d_iso8601 },
    { NULL }
};

static int parse_dates(void)
{
    int n;

    for (n = 0; good_dates[n].str != NULL; n++) {
	time_t res;
	const char *str = good_dates[n].str;

	switch (good_dates[n].type) {
	case d_rfc1036: res = ne_rfc1036_parse(str); break;
	case d_iso8601: res = ne_iso8601_parse(str); break;
	case d_rfc1123: res = ne_rfc1123_parse(str); break;
	default: res = -1; break;
	}
	
	ONV(res == -1, ("date %d parse", n));
	
#define FT "%" NE_FMT_TIME_T
	ONV(res != good_dates[n].time, (
	    "date %d incorrect (" FT " not " FT ")", n,
	    res, good_dates[n].time));
    }

    return OK;
}

static int versioning(void)
{
#define GOOD(n,m,msg) ONV(ne_version_match(n,m), \
("match of " msg " failed (%d.%d)", n, m))
#define BAD(n,m,msg) ONV(ne_version_match(n,m) == 0, \
("match of " msg " succeeded (%d.%d)", n, m))
    GOOD(NEON_VERSION_MAJOR, NEON_VERSION_MINOR, "current version");
    BAD(NEON_VERSION_MAJOR, NEON_VERSION_MINOR + 1, "later minor");
    BAD(NEON_VERSION_MAJOR + 1, 0, "later major");
#if NEON_VERSION_MINOR > 0
    GOOD(NEON_VERSION_MAJOR, NEON_VERSION_MINOR - 1, "earlier minor");
#endif
#if NEON_VERSION_MAJOR > 0
    BAD(NEON_VERSION_MAJOR - 1, 0, "earlier major");
#endif
#undef GOOD
#undef BAD
    return OK;
}

static int str_errors(void)
{
    char expect[200], actual[200];
    
    strncpy(expect, strerror(ENOENT), sizeof(expect));
    ne_strerror(ENOENT, actual, sizeof(actual));
    
    ONV(strcmp(expect, actual), 
	("error from ENOENT was `%s' not `%s'", actual, expect));

    return OK;
}

ne_test tests[] = {
    T(status_lines),
    T(md5),
    T(md5_alignment),
    T(base64),
    T(parse_dates),
    T(versioning),
    T(str_errors),
    T(NULL)
};
