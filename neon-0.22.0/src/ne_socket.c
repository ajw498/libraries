/* 
   socket handling routines
   Copyright (C) 1998-2002, Joe Orton <joe@manyfish.co.uk>, 
   Copyright (C) 1999-2000 Tommi Komulainen <Tommi.Komulainen@iki.fi>

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

/*
  portions were originally under GPL in Mutt, http://www.mutt.org/
  Relicensed under LGPL for neon, http://www.webdav.org/neon/
*/

#include "config.h"

#include <sys/types.h>
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_NETINET_IN_H
/* some platforms need this to prevent warnings when including
 * arpa/inet.h, e.g. NetBSD, (and AIX?) */
#include <netinet/in.h>
#endif

#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#include <sys/stat.h>

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

#include <errno.h>
#include <fcntl.h>
#ifdef NEON_SSL
#include <limits.h> /* for INT_MAX */
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif 
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SOCKS_H
#include <socks.h>
#endif

#include "ne_i18n.h"
#include "ne_utils.h"
#include "ne_string.h"
#include "ne_socket.h"
#include "ne_alloc.h"

#if defined(__BEOS__) && !defined(BONE_VERSION)
/* pre-BONE */
#define NEON_WRITE(a,b,c) send(a,b,c,0)
#define NEON_READ(a,b,c) recv(a,b,c,0)
#define NEON_CLOSE(s) closesocket(s)
#elif defined(WIN32)
#define NEON_WRITE(a,b,c) send(a,b,c,0)
#define NEON_READ(a,b,c) recv(a,b,c,0)
#define NEON_CLOSE(s) closesocket(s)
#else /* really Unix! */
#define NEON_WRITE(a,b,c) write(a,b,c)
#define NEON_READ(a,b,c) read(a,b,c)
#define NEON_CLOSE(s) close(s)
#endif

#if !defined(ECONNRESET) && defined(WIN32)
#define ECONNRESET WSAECONNRESET
#endif

#ifdef NEON_SSL
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h> /* for PKCS12_PBE_add */
#endif

/* Socket read timeout */
#define SOCKET_READ_TIMEOUT 120

/* Critical I/O functions on a socket: useful abstraction for easily
 * handling SSL I/O alongside raw socket I/O. */
struct iofns {
    /* Read up to 'len' bytes into 'buf' from socket.  Return <0 on
     * error or EOF, or >0; number of bytes read. */
    ssize_t (*read)(ne_socket *s, char *buf, size_t len);
    /* Write exactly 'len' bytes from 'buf' to socket.  Return zero on
     * success, <0 on error. */
    ssize_t (*write)(ne_socket *s, const char *buf, size_t len);
    /* Wait up to 'n' seconds for socket to become readable.  Returns
     * 0 when readable, otherwise NE_SOCK_TIMEOUT or NE_SOCK_ERROR. */
    int (*readable)(ne_socket *s, int n);
};

struct ne_socket_s {
    int fd;
    char error[200];
    ne_progress progress_cb;
    void *progress_ud;
    int rdtimeout; /* read timeout. */
    const struct iofns *ops;
#ifdef NEON_SSL
    SSL *ssl;
    SSL_CTX *ssl_ctx;
#endif
    /* The read buffer: ->buffer stores byte which have been read; as
     * these are consumed and passed back to the caller, bufpos
     * advances through ->buffer.  ->bufavail gives the number of
     * bytes which remain to be consumed in ->buffer (from ->bufpos),
     * and is hence always <= RDBUFSIZ. */
#define RDBUFSIZ 4096
    char buffer[RDBUFSIZ];
    char *bufpos;
    size_t bufavail;
};

/* set_error: set socket error string to 'str'. */
#define set_error(s, str) strncpy((s)->error, (str), sizeof (s)->error)

/* set_strerror: set socket error to system error string for 'e' */
#define set_strerror(s, e) ne_strerror((e), (s)->error, sizeof (s)->error)

void ne_register_progress(ne_socket *sock, ne_progress cb, void *userdata)
{
    sock->progress_cb = cb;
    sock->progress_ud = userdata;
}

int ne_sock_init(void)
{
#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
#endif
    static int result = 0; 

    if (result > 0) 
	return 0;
    else if (result < 0)
	return -1;

#ifdef WIN32    
    wVersionRequested = MAKEWORD(2, 2);
    
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
	result = -1;
	return -1;
    }

#endif

#ifdef NEON_SOCKS
    SOCKSinit("neon");
#endif

#ifdef NEON_SSL
    SSL_load_error_strings();
    SSL_library_init();
    PKCS12_PBE_add();  /* ### not sure why this is needed. */

    NE_DEBUG(NE_DBG_SOCKET, "Initialized SSL.\n");
#endif

#if defined(HAVE_SIGNAL) && defined(HAVE_SIGPIPE)
    (void) signal(SIGPIPE, SIG_IGN);
#endif

    result = 1;
    return 0;
}

void ne_sock_exit(void)
{
#ifdef WIN32
    WSACleanup();
#endif	
}

int ne_sock_block(ne_socket *sock, int n)
{
    if (sock->bufavail)
	return 0;
    return sock->ops->readable(sock, n);
}

#define SOCK_ERR(x) do { ssize_t _sock_err = (x); \
if (_sock_err < 0) return _sock_err; } while(0)

ssize_t ne_sock_read(ne_socket *sock, char *buffer, size_t buflen)
{
    ssize_t bytes;

#if 0
    NE_DEBUG(NE_DBG_SOCKET, "buf: at %d, %d avail [%s]\n", 
	     sock->bufpos - sock->buffer, sock->bufavail, sock->bufpos);
#endif

    if (sock->bufavail > 0) {
	/* Deliver buffered data. */
	if (buflen > sock->bufavail)
	    buflen = sock->bufavail;
	memcpy(buffer, sock->bufpos, buflen);
	sock->bufpos += buflen;
	sock->bufavail -= buflen;
	return buflen;
    } else if (buflen >= sizeof sock->buffer) {
	/* No need for read buffer. */
	return sock->ops->read(sock, buffer, buflen);
    } else {
	/* Fill read buffer. */
	bytes = sock->ops->read(sock, sock->buffer, sizeof sock->buffer);
	if (bytes <= 0)
	    return bytes;

	if (buflen > (size_t)bytes)
	    buflen = bytes;
	memcpy(buffer, sock->buffer, buflen);
	sock->bufpos = sock->buffer + buflen;
	sock->bufavail = bytes - buflen;
	return buflen; 
    }
}

ssize_t ne_sock_peek(ne_socket *sock, char *buffer, size_t buflen)
{
    ssize_t bytes;
    
    if (sock->bufavail) {
	/* just return buffered data. */
	bytes = sock->bufavail;
    } else {
	/* fill the buffer. */
	bytes = sock->ops->read(sock, sock->buffer, sizeof sock->buffer);
	if (bytes <= 0)
	    return bytes;

	sock->bufpos = sock->buffer;
	sock->bufavail = bytes;
    }

    if (buflen > (size_t)bytes)
	buflen = bytes;

    memcpy(buffer, sock->bufpos, buflen);

    return buflen;
}

/* Await data on raw fd in socket. */
static int readable_raw(ne_socket *sock, int secs)
{
    int fdno = sock->fd, ret;
    fd_set rdfds;
    struct timeval timeout, *tvp = (secs >= 0 ? &timeout : NULL);

    /* Init the fd set */
    FD_ZERO(&rdfds);
    do {
	FD_SET(fdno, &rdfds);
	if (tvp) {
	    tvp->tv_sec = secs;
	    tvp->tv_usec = 0;
	}
	errno = 0;
	ret = select(fdno + 1, &rdfds, NULL, NULL, tvp);
    } while (ret < 0 && errno == EINTR);
    if (ret < 0) {
	set_strerror(sock, errno);
	return NE_SOCK_ERROR;
    }
    return (ret == 0) ? NE_SOCK_TIMEOUT : 0;
}

static ssize_t read_raw(ne_socket *sock, char *buffer, size_t len)
{
    ssize_t ret;
    
    ret = readable_raw(sock, sock->rdtimeout);
    if (ret) return ret;

    do {
	ret = NEON_READ(sock->fd, buffer, len);
    } while (ret == -1 && errno == EINTR);

    if (ret == 0) {
	set_error(sock, _("Connection closed"));
	ret = NE_SOCK_CLOSED;
    } else if (ret < 0) {
	int errnum = errno;
	ret = (errnum == ECONNRESET) ? NE_SOCK_RESET : NE_SOCK_ERROR;
	set_strerror(sock, errnum);
    }

    return ret;
}

#define MAP_ERR(e) ((e) == EPIPE ? NE_SOCK_CLOSED : \
((e) == ECONNRESET ? NE_SOCK_RESET : NE_SOCK_ERROR))

static ssize_t write_raw(ne_socket *sock, const char *data, size_t length) 
{
    ssize_t wrote;
    
    do {
	wrote = NEON_WRITE(sock->fd, data, length);
	data += wrote;
	length -= wrote;
    } while ((wrote > 0 || errno == EINTR) && length > 0);

    if (wrote < 0) {
	int errnum = errno;
	set_strerror(sock, errnum);
	return MAP_ERR(errnum);
    }

    return 0;
}

static const struct iofns iofns_raw = { read_raw, write_raw, readable_raw };

#ifdef NEON_SSL
/* OpenSSL I/O function implementations. */
static int readable_ossl(ne_socket *sock, int secs)
{
    /* If there is buffered SSL data, then don't block on the socket.
     * FIXME: make sure that SSL_read *really* won't block if
     * SSL_pending returns non-zero.  Possibly need to do
     * SSL_read(ssl, buf, SSL_pending(ssl)) */

    if (sock->ssl && SSL_pending(sock->ssl))
	return 0;

    return readable_raw(sock, secs);
}

/* SSL error handling, according to SSL_get_error(3). */
static int error_ossl(ne_socket *sock, int sret)
{
    int err = SSL_get_error(sock->ssl, sret), ret = NE_SOCK_ERROR;
    
    switch (err) {
    case SSL_ERROR_ZERO_RETURN:
	ret = NE_SOCK_CLOSED;
	set_error(sock, _("Connection closed"));
	break;
    case SSL_ERROR_SYSCALL:
	err = ERR_get_error();
	if (err == 0) {
	    if (sret == 0)
		/* TODO: connection was closed without getting a
		 * close_notify event; this is a possible truncation
		 * attack, though EKR thinks it can be ignored. */
		set_error(sock, _("Connection aborted"));
	    else {
		/* Other socket error. */
		err = errno;
		set_strerror(sock, err);
		ret = MAP_ERR(err);
	    }
	} else {
	    ne_snprintf(sock->error, sizeof sock->error, 
			_("SSL error: %s"), ERR_reason_error_string(err));
	}
	break;
    default:
	ne_snprintf(sock->error, sizeof sock->error, _("SSL error: %s"), 
		    ERR_reason_error_string(ERR_get_error()));
	break;
    }
    return ret;
}

/* Work around OpenSSL's use of 'int' rather than 'size_t', to prevent
 * accidentally passing a negative number, etc. */
#define CAST2INT(n) (((n) > INT_MAX) ? INT_MAX : (n))

static ssize_t read_ossl(ne_socket *sock, char *buffer, size_t len)
{
    int ret;

    ret = readable_ossl(sock, sock->rdtimeout);
    if (ret) return ret;
    
    ret = SSL_read(sock->ssl, buffer, CAST2INT(len));
    if (ret <= 0)
	ret = error_ossl(sock, ret);

    return ret;
}

static ssize_t write_ossl(ne_socket *sock, const char *data, size_t len)
{
    int ret, ilen = CAST2INT(len);
    ret = SSL_write(sock->ssl, data, ilen);
    /* ssl.h says SSL_MODE_ENABLE_PARTIAL_WRITE must be enabled to
     * have SSL_write return < length...  so, SSL_write should never
     * return < length. */
    if (ret != ilen)
	return error_ossl(sock, ret);
    return 0;
}

static const struct iofns iofns_ossl = {
    read_ossl,
    write_ossl,
    readable_ossl
};

#endif /* NEON_SSL */

int ne_sock_fullwrite(ne_socket *sock, const char *data, size_t len)
{
    return sock->ops->write(sock, data, len);
}

ssize_t ne_sock_readline(ne_socket *sock, char *buf, size_t buflen)
{
    char *lf;
    size_t len;
    
    if ((lf = memchr(sock->bufpos, '\n', sock->bufavail)) == NULL
	&& sock->bufavail < RDBUFSIZ) {
	/* The buffered data does not contain a complete line: move it
	 * to the beginning of the buffer. */
	if (sock->bufavail)
	    memmove(sock->buffer, sock->bufpos, sock->bufavail);
	sock->bufpos = sock->buffer;
	
	/* Loop filling the buffer whilst no newline is found in the data
	 * buffered so far, and there is still buffer space available */ 
	do {
	    /* Read more data onto end of buffer. */
	    ssize_t ret = sock->ops->read(sock, sock->buffer + sock->bufavail,
					  RDBUFSIZ - sock->bufavail);
	    if (ret < 0) return ret;
	    sock->bufavail += ret;
	} while ((lf = memchr(sock->buffer, '\n', sock->bufavail)) == NULL
		 && sock->bufavail < RDBUFSIZ);
    }

    if (lf)
	len = lf - sock->bufpos + 1;
    else
	len = buflen; /* fall into "line too long" error... */

    if ((len + 1) > buflen) {
	set_error(sock, _("Line too long"));
	return NE_SOCK_ERROR;
    }

    memcpy(buf, sock->bufpos, len);
    buf[len] = '\0';
    /* consume the line from buffer: */
    sock->bufavail -= len;
    sock->bufpos += len;
    return len;
}

ssize_t ne_sock_fullread(ne_socket *sock, char *buffer, size_t buflen) 
{
    ssize_t len;

    while (buflen > 0) {
	len = ne_sock_read(sock, buffer, buflen);
	if (len < 0) return len;
	buflen -= len;
	buffer += len;
    }

    return 0;
}

#ifndef INADDR_NONE
#define INADDR_NONE ((unsigned long) -1)
#endif

/* Do a name lookup on given hostname, writes the address into
 * given address buffer. Return -1 on failure.
 */
int ne_name_lookup(const char *hostname, struct in_addr *addr) 
{
    struct hostent *hp;
    unsigned long laddr;
    
    /* TODO?: a possible problem here, is that if we are passed an
     * invalid IP address e.g. "500.500.500.500", then this gets
     * passed to gethostbyname and returned as "Host not found".
     * Arguably wrong, but maybe difficult to detect correctly what is
     * an invalid IP address and what is a hostname... can hostnames
     * begin with a numeric character? */
    laddr = inet_addr(hostname);
    if (laddr == INADDR_NONE) {
	/* inet_addr failed. */
	hp = gethostbyname(hostname);
	if (hp == NULL) {
#if 0
	    /* Need to get this back somehow, but we don't have 
	     * an ne_socket * yet... */
	    switch(h_errno) {
	    case HOST_NOT_FOUND:
		sock->error = _("Host not found");
		break;
	    case TRY_AGAIN:
		sock->error = _("Host not found (try again later?)");
		break;
	    case NO_ADDRESS:
		sock->error = _("Host exists but has no address.");
		break;
	    case NO_RECOVERY:
	    default:
		sock->error = _("Non-recoverable error in resolver library.");
		break;
	    }
#endif
	    return NE_SOCK_ERROR;
	}
	memcpy(addr, hp->h_addr, hp->h_length);
    } else {
	addr->s_addr = laddr;
    }
    return 0;
}

static ne_socket *create_sock(int fd)
{
    ne_socket *sock = ne_calloc(sizeof *sock);
    sock->fd = fd;
    sock->rdtimeout = SOCKET_READ_TIMEOUT;
    sock->bufpos = sock->buffer;
    sock->ops = &iofns_raw;
    return sock;
}

/* Opens a socket to the given port at the given address.
 * Returns -1 on failure, or the socket on success. 
 * portnum must be in HOST byte order */
ne_socket *ne_sock_connect(const struct in_addr addr, 
			   unsigned int portnum)
{
    struct sockaddr_in sa;
    int fd;

    /* Create the socket */
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
	return NULL;
    /* Connect the ne_socket */
    sa.sin_family = AF_INET;
    sa.sin_port = htons(portnum); /* host -> net byte orders */
    sa.sin_addr = addr;
    if (connect(fd, (struct sockaddr *)&sa, sizeof sa) < 0) {
	(void) NEON_CLOSE(fd);
	return NULL;
    }
    /* Success - return the ne_socket */
    return create_sock(fd);
}

ne_socket *ne_sock_accept(int listener) 
{
    int fd = accept(listener, NULL, NULL);
    if (fd > 0)
	return create_sock(fd);
    return NULL;
}

int ne_sock_fd(const ne_socket *sock)
{
    return sock->fd;
}

void ne_sock_read_timeout(ne_socket *sock, int timeout)
{
    sock->rdtimeout = timeout;
}

#ifdef NEON_SSL
int ne_sock_use_ssl(ne_socket *sock)
{
    /* create a context. */
    sock->ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    return ne_sock_use_ssl_os(sock, sock->ssl_ctx, NULL, NULL, NULL);
}

void ne_sock_switch_ssl(ne_socket *sock, SSL *ssl)
{
    sock->ssl = ssl;
    sock->ops = &iofns_ossl;
}

#else
int ne_sock_use_ssl(ne_socket *sock) { return -1; }
#endif

#ifdef NEON_SSL
int ne_sock_use_ssl_os(ne_socket *sock, SSL_CTX *ctx, 
		       SSL_SESSION *sess, SSL **ssl,
		       void *appdata)
{
    int ret;

    sock->ssl = SSL_new(ctx);
    if (!sock->ssl) {
	set_error(sock, _("Could not create SSL structure"));
	return NE_SOCK_ERROR;
    }
    
    if (appdata) {
	SSL_set_app_data(sock->ssl, appdata);
    }

    sock->ops = &iofns_ossl;

    SSL_set_mode(sock->ssl, SSL_MODE_AUTO_RETRY);

    SSL_set_fd(sock->ssl, sock->fd);
    
    if (sess)
	SSL_set_session(sock->ssl, sess);

    ret = SSL_connect(sock->ssl);
    if (ret != 1) {
	error_ossl(sock, ret);
	SSL_free(sock->ssl);
	sock->ssl = NULL;
	return NE_SOCK_ERROR;
    }

    if (ssl)
	*ssl = sock->ssl;

    return 0;
}

#endif

const char *ne_sock_error(const ne_socket *sock)
{
    return sock->error;
}

/* Closes given ne_socket */
int ne_sock_close(ne_socket *sock)
{
    int ret;
#ifdef NEON_SSL
    if (sock->ssl) {
	SSL_shutdown(sock->ssl);
	SSL_free(sock->ssl);
	if (sock->ssl_ctx)
	    SSL_CTX_free(sock->ssl_ctx);
    }
#endif
    ret = NEON_CLOSE(sock->fd);
    free(sock);
    return ret;
}

/* Returns HOST byte order port of given name */
int ne_service_lookup(const char *name)
{
    struct servent *ent;
    ent = getservbyname(name, "tcp");
    if (ent)
	return ntohs(ent->s_port);
    return 0;
}
