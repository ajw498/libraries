/* 
   socket handling interface
   Copyright (C) 1999-2002, Joe Orton <joe@manyfish.co.uk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA

*/

#ifndef NE_SOCKET_H
#define NE_SOCKET_H

#ifdef WIN32
#include <winsock2.h>
#include <stddef.h>
#include <sys/types.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#ifdef NEON_SSL
#include <openssl/ssl.h>
#endif

#include "ne_defs.h"

BEGIN_NEON_DECLS

/* define ssize_t for Win32 */
#if defined(WIN32) && !defined(ssize_t)
#define ssize_t int
#endif

#define NE_SOCK_ERROR (-1)
/* Read/Write timed out */
#define NE_SOCK_TIMEOUT (-2)
/* Socket was closed */
#define NE_SOCK_CLOSED (-3)
/* Connection was reset (e.g. server crashed) */
#define NE_SOCK_RESET (-4)

typedef struct ne_socket_s ne_socket;

typedef void (*ne_block_reader) (
    void *userdata, const char *buf, size_t len);

typedef void (*ne_progress)(void *userdata, off_t progress, off_t total);

void ne_register_progress(ne_socket *sock, ne_progress cb, void *userdata);

/* While neon itself doesn't require per-process global
 * initialization, some platforms do, and so does the OpenSSL
 * library. */
int ne_sock_init(void);

/* Shutdown any underlying libraries. */
void ne_sock_exit(void);

/* ne_sock_read reads up to 'count' bytes into 'buffer'.
 * Returns:
 *   NE_SOCK_* on error,
 *   >0 length of data read into buffer.
 */
ssize_t ne_sock_read(ne_socket *sock, char *buffer, size_t count);

/* ne_sock_peek reads up to 'count' bytes into 'buffer', but the data
 * will still be returned on a subsequent call to ne_sock_read or 
 * ne_sock_peek.
 * Returns:
 *   NE_SOCK_* on error,
 *   >0 length of data read into buffer.
 */
ssize_t ne_sock_peek(ne_socket *sock, char *buffer, size_t count);

/* Block for up to 'n' seconds until data becomes available for reading
 * on the socket. Returns:
 *  NE_SOCK_* on error,
 *  NE_SOCK_TIMEOUT if no data arrives in 'n' seconds.
 *  0 if data arrived on the socket.
 */
int ne_sock_block(ne_socket *sock, int n);

/* Writes 'count' bytes of 'data' to the socket.
 * Returns 0 on success, NE_SOCK_* on error. */
int ne_sock_fullwrite(ne_socket *sock, const char *data, size_t count); 

/* Reads an LF-terminated line into 'buffer', and NUL-terminate it.
 * At most 'len' bytes are read (including the NUL terminator).
 * Returns:
 * NE_SOCK_* on error,
 * >0 number of bytes read (including NUL terminator)
 */
ssize_t ne_sock_readline(ne_socket *sock, char *buffer, size_t len);

/* Read exactly 'len' bytes into buffer; returns 0 on success, SOCK_*
 * on error. */
ssize_t ne_sock_fullread(ne_socket *sock, char *buffer, size_t len);

/* Create a socket connected to server at address 'host' on port
 * 'port'.  Returns NULL if a connection could not be established. */
ne_socket *ne_sock_connect(const struct in_addr host, unsigned int port);

/* Accept a connection on listening socket 'fd'. */
ne_socket *ne_sock_accept(int fd);

/* Returns the file descriptor used for socket 'sock'. */
int ne_sock_fd(const ne_socket *sock);

/* Close the socket, and destroy the socket object. Returns non-zero
 * on error. */
int ne_sock_close(ne_socket *sock);

/* Return current error string for socket. */
const char *ne_sock_error(const ne_socket *sock);

/* Set read timeout for socket. */
void ne_sock_read_timeout(ne_socket *sock, int timeout);

/* Do a name lookup on given hostname, writes the address into
 * given address buffer. Return -1 on failure. */
int ne_name_lookup(const char *hostname, struct in_addr *addr);

/* Returns the standard TCP port for the given service */
int ne_service_lookup(const char *name);

/* Enable SSL/TLS on the socket. Returns non-zero if the SSL
 * negotiation fails. */
int ne_sock_use_ssl(ne_socket *sock);

#ifdef NEON_SSL
/* FIXME: this is a terribly disgusting API. */

/* Enable SSL/TLS, using the given OpenSSL SSL context, and resuming
 * the given session if sess is non-NULL. Returns non-zero if the SSL
 * negotiation fails.  If out is non-NULL, *out is set to the SSL
 * connection structure from OpenSSL. */
int ne_sock_use_ssl_os(ne_socket *sock, SSL_CTX *ctx, 
		       SSL_SESSION *sess, SSL **out, void *appdata);

/* Enable SSL with an already-negotiated SSL socket. */
void ne_sock_switch_ssl(ne_socket *sock, SSL *ssl);

#endif

END_NEON_DECLS

#endif /* NE_SOCKET_H */
