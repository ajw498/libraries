/* 
   String handling tests
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
#ifdef HAVE_ERRNO_H
#include <errno.h> /* for the ENOENT definitions in str_errors */
#endif

#include "ne_string.h"

#include "tests.h"

#undef ONCMP
#define ONCMP(a,b) ONV(strcmp(a, b), \
		       ("result was [%s] not [%s]", a, b))

static int simple(void) {
    ne_buffer *s = ne_buffer_create();
    ON(s == NULL);
    ne_buffer_zappend(s, "abcde");
    ONCMP(s->data, "abcde");
    ON(ne_buffer_size(s) != 5);
    ne_buffer_destroy(s);
    return OK;
}

static int buf_concat(void)
{
    ne_buffer *s = ne_buffer_create();
    ON(s == NULL);
    ne_buffer_concat(s, "a", "b", "c", "d", "e", "f", "g", NULL);
    ONCMP(s->data, "abcdefg");
    ON(ne_buffer_size(s) != 7);
    ne_buffer_destroy(s);
    return OK;
}

static int buf_concat2(void)
{
#define RES "alphabetagammadeltaepsilonetatheta"
    ne_buffer *s = ne_buffer_create();
    ON(s == NULL);
    ne_buffer_concat(s, "alpha", "beta", "gamma", "delta", "epsilon", 
		     "eta", "theta", NULL);
    ONCMP(s->data, RES);
    ON(ne_buffer_size(s) != strlen(RES));
    ne_buffer_destroy(s);
    return OK;
}

static int buf_concat3(void)
{
    ne_buffer *s = ne_buffer_create();
    ON(s == NULL);
    ne_buffer_zappend(s, "foobar");
    ne_buffer_concat(s, "norman", NULL);
    ONCMP(s->data, "foobarnorman");
    ON(ne_buffer_size(s) != 12);
    ne_buffer_destroy(s);
    return OK;
}

static int append(void) {
    ne_buffer *s = ne_buffer_create();
    ON(s == NULL);
    ne_buffer_append(s, "a", 1);
    ne_buffer_append(s, "b", 1);
    ne_buffer_append(s, "c", 1);
    ONCMP(s->data, "abc");
    ON(ne_buffer_size(s) != 3);
    ne_buffer_destroy(s);
    return OK;
}    

static int grow(void)
{
    ne_buffer *s = ne_buffer_ncreate(2);
    ON(s == NULL);
    ne_buffer_append(s, "a", 1);
    ne_buffer_grow(s, 4);
    ONCMP(s->data, "a");
    ne_buffer_destroy(s);
    return OK;
}

static int alter(void) {
    ne_buffer *s = ne_buffer_create();
    char *d;
    ON(s == NULL);
    ne_buffer_zappend(s, "abcdefg");
    d = s->data;
    ON(d == NULL);
    d[2] = '\0';
    ne_buffer_altered(s);
    ONCMP(s->data, "ab");
    ON(ne_buffer_size(s) != 2);
    ne_buffer_zappend(s, "hijkl");
    ONCMP(s->data, "abhijkl");
    return OK;
}

/* Macros for testing ne_token. */

#define TEST(res) do { \
  char *tok = ne_token(&pnt, ','); \
  ONN(res ": return", tok == NULL); \
  ONN(res ": compare", strcmp(tok, (res))); \
  ONN(res ": modify", pnt == NULL); \
} while (0)

#define LASTTEST(res) do { \
  char *tok = ne_token(&pnt, ','); \
  ONN(res ": last return", tok == NULL); \
  ONN(res ": last compare", strcmp(tok, (res))); \
  ONN(res ": last modify", pnt != NULL); \
} while (0)

#define QTEST(res) do { \
  char *tok = ne_qtoken(&pnt, ',', QUOTES); \
  ONN(res ": return", tok == NULL); \
  ONN(res ": compare", strcmp(tok, (res))); \
  ONN(res ": modify", pnt == NULL); \
} while (0)

#define QLASTTEST(res) do { \
  char *tok = ne_qtoken(&pnt, ',', QUOTES); \
  ONN(res ": last return", tok == NULL); \
  ONN(res ": last compare", strcmp(tok, (res))); \
  ONN(res ": last modify", pnt != NULL); \
} while (0)

static int token1(void)
{
    char *str = ne_strdup("a,b,c,d"), *pnt = str;

    TEST("a"); TEST("b"); TEST("c"); LASTTEST("d");
    
    free(str);
    return OK;
}

static int token2(void)
{
    char *str = ne_strdup("norman,fishing, elsewhere"), *pnt = str;
    
    TEST("norman"); TEST("fishing"); LASTTEST(" elsewhere");

    free(str);
    return OK;
}

static int nulls(void)
{
    char *str = ne_strdup("alpha,,gamma"), *pnt = str;

    TEST("alpha"); TEST(""); LASTTEST("gamma");
    free(str);
    
    pnt = str = ne_strdup(",,,wooo");
    TEST(""); TEST(""); TEST(""); LASTTEST("wooo");
    free(str);

    pnt = str = ne_strdup("wooo,,,");
    TEST("wooo"); TEST(""); TEST(""); LASTTEST("");
    free(str);    

    return OK;
}

static int empty(void)
{
    char *str = ne_strdup(""), *pnt = str;

    LASTTEST("");
    free(str);

    return OK;
}

#undef QUOTES
#define QUOTES "'"

static int quoted(void)
{
    char *str = 
	ne_strdup("alpha,'beta, a fish called HELLO!?',sandwiches");
    char *pnt = str;
    
    QTEST("alpha");
    QTEST("'beta, a fish called HELLO!?'");
    QLASTTEST("sandwiches");
    
    free(str);
    return OK;
}

static int badquotes(void)
{
    char *str = ne_strdup("alpha,'blah"), *pnt = str;
    
    QTEST("alpha");
    ON(ne_qtoken(&pnt, ',', QUOTES) != NULL);
    
    free(str);
    return OK;
}

/* for testing ne_shave. */
#undef TEST
#define TEST(str, ws, res) do { \
  char *s = ne_strdup((str)); \
  char *r = ne_shave(s, (ws)); \
  ONN("[" str "]", strcmp(r, (res))); \
  free(s); \
} while (0)

static int shave(void)
{
    TEST(" b ", " ", "b");
    TEST("b", " ", "b");
    TEST("   b    ", " ", "b");
    TEST("--bbb-----", "-", "bbb");
    TEST("hello, world    ", " ", "hello, world");
    TEST("<<><<<><<this is foo<<><<<<><<", "<>", "this is foo");
    TEST("09809812342347I once saw an helicopter0012312312398", "0123456789",
	 "I once saw an helicopter");
    return OK;
}

/* Regression test for ne_shave call which should produce an empty
 * string. */
static int shave_regress(void)
{
    TEST("\"\"", "\"", "");
    return OK;
}

/* Test the ne_token/ne_shave combination. */

#undef TEST
#undef LASTTEST

#define TEST(res) do { \
  char *tok = ne_token(&pnt, ','); \
  ONN(res ": return", tok == NULL); \
  tok = ne_shave(tok, " "); \
  ONN(res ": shave", tok == NULL); \
  ONN(res ": compare", strcmp(tok, (res))); \
  ONN(res ": modify", pnt == NULL); \
} while (0)


#define LASTTEST(res) do { \
  char *tok = ne_token(&pnt, ','); \
  ONN(res ": last return", tok == NULL); \
  tok = ne_shave(tok, " "); \
  ONN(res ": last shave", tok == NULL); \
  ONN(res ": last compare", strcmp(tok, (res))); \
  ONN(res ": last modify", pnt != NULL); \
} while (0)

/* traditional use of ne_token/ne_shave. */
static int combo(void)
{
    char *str = ne_strdup("  fred , mary, jim , alice, david"), *pnt = str;
    
    TEST("fred"); TEST("mary"); TEST("jim"); TEST("alice");
    LASTTEST("david");
    
    free(str);
    return 0;
}

static int concat(void)
{
#define CAT(res, args) do { char *str = ne_concat args; \
ONCMP(str, res); \
free(str); } while (0)
    CAT("alphabeta", ("alpha", "beta", NULL));
    CAT("alpha", ("alpha", "", "", NULL));
    CAT("", ("", NULL));
    CAT("", ("", "", "", NULL));
    CAT("alpha", ("", "a", "lph", "", "a", NULL));
    return OK;    
}

static int str_errors(void)
{
    char expect[200], actual[200];
    
    strncpy(expect, strerror(ENOENT), sizeof(expect));
    ONN("ne_strerror did not return passed-in buffer",
	ne_strerror(ENOENT, actual, sizeof(actual)) != actual);
    
    ONV(strcmp(expect, actual), 
	("error from ENOENT was `%s' not `%s'", actual, expect));

    /* Test truncated error string is still NUL-terminated. */
    ne_strerror(ENOENT, actual, 6);
    ONN("truncated string had wrong length", strlen(actual) != 5);

    return OK;
}

static int strnzcpy(void)
{
    char buf[5];

    ne_strnzcpy(buf, "abcdefghi", sizeof buf);
    ONV(strcmp(buf, "abcd"), ("result was `%s' not `abcd'", buf));
    
    ne_strnzcpy(buf, "ab", sizeof buf);
    ONV(strcmp(buf, "ab"), ("result was `%s' not `ab'", buf));    

    return OK;    
}

ne_test tests[] = {
    T(simple),
    T(buf_concat),
    T(buf_concat2),
    T(buf_concat3),
    T(append),
    T(grow),
    T(alter),
    T(token1),
    T(token2),
    T(nulls),
    T(empty),
    T(quoted),
    T(badquotes),
    T(shave),
    T(shave_regress),
    T(combo),
    T(concat),
    T(str_errors),
    T(strnzcpy),
    T(NULL)
};

