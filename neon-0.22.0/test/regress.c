/* 
   Some miscellenaneous regression tests
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

#include <sys/types.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "ne_request.h"
#include "ne_props.h"

#include "tests.h"
#include "child.h"
#include "utils.h"

#ifndef NEON_NODAV
/* This caused a segfault in 0.15.3 and earlier. */
static int serve_dodgy_xml(ne_socket *sock, void *ud)
{
    char buffer[BUFSIZ];

    CALL(discard_request(sock));
    
    ne_sock_read(sock, buffer, clength);

    SEND_STRING(sock,
		"HTTP/1.0 207 OK\r\n"
		"Server: foo\r\n"
		"Connection: close\r\n"
		"\r\n"
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		"<multistatus xmlns=\"DAV:\">"
		"<response><propstat><prop><href>"
		"</href></prop></propstat></response>"
		"</multistatus>");

    return 0;
}

static void dummy_results(void *ud, const char *href,
			  const ne_prop_result_set *rset)
{

}

static int propfind_segv(void)
{
    ne_session *sess;

    CALL(make_session(&sess, serve_dodgy_xml, NULL));
    
    ne_simple_propfind(sess, "/", 0, NULL, dummy_results, NULL);
    ne_session_destroy(sess);
    await_server();

    return OK;
}

/* TODO: regression test needed for ne_lock_discover getting this
 * response body. Segfaults pre-0.18. */

/* 
<?xml version="1.0" encoding="utf-8"?>
<D:multistatus xmlns:D="DAV:">
<D:response>
<D:href>/dav/ltmain.txt</D:href>
<D:propstat>
<D:prop>
<D:lockdiscovery/>
</D:prop>
<D:status>HTTP/1.1 200 OK</D:status>
</D:propstat>
</D:response>
</D:multistatus>

*/

#else
static int propfind_segv(void)
{
    t_context("built without WebDAV support");
    return SKIP;
}
#endif   

ne_test tests[] = {
    T(propfind_segv),
    T(NULL)
};
