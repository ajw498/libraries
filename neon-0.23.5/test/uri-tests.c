/* 
   URI tests
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

#include "ne_uri.h"

#include "tests.h"

static int simple(void)
{
    ne_uri p = {0};
    ON(ne_uri_parse("http://www.webdav.org/foo", &p));
    ON(strcmp(p.host, "www.webdav.org"));
    ON(strcmp(p.path, "/foo"));
    ON(strcmp(p.scheme, "http"));
    ON(p.port);
    ON(p.authinfo != NULL);
    ne_uri_free(&p);
    return 0;
}

static int simple_ssl(void)
{
    ne_uri p = {0};
    ON(ne_uri_parse("https://webdav.org/", &p));
    ON(strcmp(p.scheme, "https"));
    ON(p.port);
    ne_uri_free(&p);
    return OK;
}

static int no_path(void)
{
    ne_uri p = {0};
    ON(ne_uri_parse("https://webdav.org", &p));
    ON(strcmp(p.path, "/"));
    ne_uri_free(&p);
    return OK;
}

static int authinfo(void)
{
    ne_uri p = {0};
    ON(ne_uri_parse("ftp://jim:bob@jim.com", &p));
    ON(strcmp(p.host, "jim.com"));
    ON(strcmp(p.authinfo, "jim:bob"));
    ne_uri_free(&p);
    return OK;
}

#define STR "/a¹²³¼½/"
static int escapes(void)
{
    char *un, *esc;
    esc = ne_path_escape(STR);
    ON(esc == NULL);
    un = ne_path_unescape(esc);
    ON(un == NULL);
    ON(strcmp(un, STR));
    free(un);
    free(esc);
    return OK;
}    

static int parents(void)
{
    static const struct {
	const char *path, *parent;
    } ps[] = {
	{ "/a/b/c", "/a/b/" },
	{ "/a/b/c/", "/a/b/" },
	{ "/alpha/beta", "/alpha/" },
	{ "/foo", "/" },
	{ "norman", NULL },
	{ "/", NULL },
	{ "", NULL },
	{ NULL, NULL }
    };
    int n;
    
    for (n = 0; ps[n].path != NULL; n++) {
	char *p = ne_path_parent(ps[n].path);
	if (ps[n].parent == NULL) {
	    ONV(p != NULL, ("parent of `%s' was `%s' not NULL", 
			    ps[n].path, p));
	} else {
	    ONV(p == NULL, ("parent of `%s' was NULL", ps[n].path));
	    ONV(strcmp(p, ps[n].parent),
		("parent of `%s' was `%s' not `%s'",
		 ps[n].path, p, ps[n].parent));
	    free(p);
	}
    }

    return OK;
}

static int compares(void)
{
    ON(ne_path_compare("/a", "/a/") != 0);
    ON(ne_path_compare("/a/", "/a") != 0);
    ON(ne_path_compare("/ab", "/a/") == 0);
    ON(ne_path_compare("/a/", "/ab") == 0);
    ON(ne_path_compare("/a/", "/a/") != 0);
    ON(ne_path_compare("/a/b/c/d", "/a/b/c/") == 0);
    return OK;
}

/* Checks that a URI comparison of 'u1' and 'u2', which have differing
 * 'field', doesn't compare to equal; and that they are ordered
 * correctly. */
static int cmp_differ(const char *field,
		      const ne_uri *u1, const ne_uri *u2)
{
    ONV(ne_uri_cmp(u1, u2) == 0,
	("URIs with different %s were equal", field));

    ONV(ne_uri_cmp(u2, u1) == 0,
	("URIs with different %s were equal (reversed)", field));

    /* relies on strcmp return value being of equal magnitude when
     * arguments are reversed; not sure if this is portable
     * assumption. */
    ONV(ne_uri_cmp(u1, u2) + ne_uri_cmp(u2, u1) != 0,
	("relative ordering of URIs with different %s incorrect", field));

    return OK;
}

static int cmp(void)
{
    ne_uri alpha, beta;
    
    alpha.path = "/alpha";
    alpha.scheme = "http";
    alpha.host = "example.com";
    alpha.port = 80;

    beta = alpha; /* structure copy. */

    ONN("equal URIs not equal", ne_uri_cmp(&alpha, &beta) != 0);

    beta.path = "/beta";
    CALL(cmp_differ("path", &alpha, &beta));

    beta = alpha; beta.scheme = "https";
    CALL(cmp_differ("scheme", &alpha, &beta));
    
    beta = alpha; beta.port = 433;
    CALL(cmp_differ("port", &alpha, &beta));

    beta = alpha; beta.host = "fish.com";
    CALL(cmp_differ("host", &alpha, &beta));

    beta = alpha; beta.host = "EXAMPLE.CoM";
    ONN("hostname comparison not case-insensitive",
	ne_uri_cmp(&alpha, &beta) != 0);
    
    beta = alpha; beta.scheme = "HtTp";
    ONN("scheme comparison not case-insensitive",
	ne_uri_cmp(&alpha, &beta) != 0);
    
    beta = alpha; beta.path = ""; alpha.path = "/";
    ONN("empty abspath doesn't match '/'",
	ne_uri_cmp(&alpha, &beta) != 0);
    ONN("'/' doesn't match empty abspath",
	ne_uri_cmp(&beta, &alpha) != 0);

    return OK;
}

static int children(void)
{
    ON(ne_path_childof("/a", "/a/b") == 0);
    ON(ne_path_childof("/a/", "/a/b") == 0);
    ON(ne_path_childof("/aa/b/c", "/a/b/c/d/e") != 0);
    ON(ne_path_childof("////", "/a") != 0);
    return OK;
}

static int slash(void)
{
    ON(ne_path_has_trailing_slash("/a/") == 0);
    ON(ne_path_has_trailing_slash("/a") != 0);
    {
	/* check the uri == "" case. */
	char *foo = "/";
	ON(ne_path_has_trailing_slash(&foo[1]));
    }
    return OK;
}

static int just_hostname(void)
{
    ne_uri p = {0};
    ON(ne_uri_parse("host.name.com", &p));
    ON(strcmp(p.host, "host.name.com"));
    ne_uri_free(&p);
    return 0;
}

static int just_path(void)
{
    ne_uri p = {0};
    ON(ne_uri_parse("/argh", &p));
    ON(strcmp(p.path, "/argh"));
    ne_uri_free(&p);
    return 0;
}

static int default_port(void)
{
    ONN("default http: port incorrect", ne_uri_defaultport("http") != 80);
    ONN("default https: port incorrect", ne_uri_defaultport("https") != 443);
    return OK;
}

static int parse(void)
{
    static const struct test_uri {
	const char *uri, *scheme, *host;
	unsigned int port;
	const char *path;
    } uritests[] = {
	{ "http://webdav.org/norman", "http", "webdav.org", 0, "/norman" },
	{ "http://webdav.org:/norman", "http", "webdav.org", 0, "/norman" },
	{ "https://webdav.org/foo", "https", "webdav.org", 0, "/foo" },
	{ "http://webdav.org:8080/bar", "http", "webdav.org", 8080, "/bar" },
	{ "http://a/b", "http", "a", 0, "/b" },
	{ "http://webdav.org/bar:fish", "http", "webdav.org", 0, "/bar:fish" },
	{ "http://webdav.org", "http", "webdav.org", 0, "/" },
	/* relativeURIs accepted for dubious legacy reasons. */
	{ "a/b", NULL, "a", 0, "/b" },
	{ "a:8080/b", NULL, "a", 8080, "/b" },
	{ "/fish", NULL, NULL, 0, "/fish" },
	{ "webdav.org:8080", NULL, "webdav.org", 8080, "/" },
	/* IPv6 hex strings allowed even if IPv6 not supported. */
	{ "http://[::1]/foo", "http", "[::1]", 0, "/foo" },
	{ "http://[a:a:a:a::0]/foo", "http", "[a:a:a:a::0]", 0, "/foo" },
	{ "http://[::1]:8080/bar", "http", "[::1]", 8080, "/bar" },
	{ "http://fish/[foo]/bar", "http", "fish", 0, "/[foo]/bar" },
	/* and some dubious ones: */
	{ "[::1]/foo", NULL, "[::1]", 0, "/foo" },
	{ "[::1]:8000/foo", NULL, "[::1]", 8000, "/foo" },
	{ NULL }
    };
    int n;

    for (n = 0; uritests[n].uri != NULL; n++) {
	ne_uri res;
	const struct test_uri *exp = &uritests[n];
	ONV(ne_uri_parse(exp->uri, &res) != 0,
	    ("%s: parse failed", exp->uri));
	ONV(res.port != exp->port,
	    ("%s: parsed port was %d not %d", exp->uri, res.port, exp->port));
	ONCMP(exp->scheme, res.scheme, exp->uri, "scheme");
	ONCMP(exp->host, res.host, exp->uri, "host");
	ONV(strcmp(res.path, exp->path),
	    ("%s: parsed path was %s not %s", exp->uri, res.path, exp->path));
	ne_uri_free(&res);
    }

    return OK;
}

static int failparse(void)
{
    static const char *uris[] = {
	"",
	"http://[::1/",
	NULL
    };
    int n;
    
    for (n = 0; uris[n] != NULL; n++) {
	ne_uri p;
	ONV(ne_uri_parse(uris[n], &p) == 0,
	    ("`%s' did not fail to parse", uris[n]));
	ne_uri_free(&p);
    }

    return 0;
}

static int unparse(void)
{
    const char *uris[] = {
	"http://foo.com/bar",
	"https://bar.com/foo/wishbone",
	"http://www.random.com:8000/",
	"http://[::1]:8080/",
	"ftp://ftp.foo.bar/abc/def",
	NULL
    };
    int n;

    for (n = 0; uris[n] != NULL; n++) {
	ne_uri parsed;
	char *unp;

	ONV(ne_uri_parse(uris[n], &parsed),
	    ("failed to parse %s", uris[n]));
	
	unp = ne_uri_unparse(&parsed);

	ONV(strcmp(unp, uris[n]),
	    ("unparse got %s from %s", unp, uris[n]));
	
	free(unp);
    }

    return OK;    
}

ne_test tests[] = {
    T(simple),
    T(simple_ssl),
    T(authinfo),
    T(no_path),
    T(escapes),
    T(parents),
    T(compares),
    T(cmp),
    T(children),
    T(slash),
    T(just_hostname),
    T(just_path),
    T(default_port),
    T(parse),
    T(failparse),
    T(unparse),
    T(NULL)
};
