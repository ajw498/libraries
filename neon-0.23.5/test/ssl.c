/* 
   neon test suite
   Copyright (C) 2002, Joe Orton <joe@manyfish.co.uk>

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

#include <sys/stat.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include "ne_request.h"
#include "ne_socket.h"

#include "tests.h"
#include "child.h"
#include "utils.h"

#ifndef NEON_SSL
/* this file shouldn't be built if SSL is not enabled. */
#error SSL not supported
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#define ERROR_SSL_STRING (ERR_reason_error_string(ERR_get_error()))

#define SERVER_CERT "server.cert"
#define CA_CERT "ca/cert.pem"

static SSL_CTX *server_ctx = NULL;

static char *srcdir = ".";

static int s_strwrite(SSL *s, const char *buf)
{
    size_t len = strlen(buf);
    
    ONV(SSL_write(s, buf, len) != (int)len,
	("SSL_write failed: %s", ERROR_SSL_STRING));

    return OK;
}

/* Do an SSL response over socket given context; returning ssl session
 * structure in *sess if sess is non-NULL. */
static int do_ssl_response(ne_socket *sock, SSL_CTX *ctx, SSL_SESSION **sess,
			   const char *resp, int unclean)
{
    int fd = ne_sock_fd(sock), ret;
    /* we don't want OpenSSL to close this socket for us. */
    BIO *bio = BIO_new_socket(fd, BIO_NOCLOSE);
    char buf[BUFSIZ];
    SSL *ssl = SSL_new(ctx);

    ONN("SSL_new failed", ssl == NULL);

    SSL_set_bio(ssl, bio, bio);

    ONV(SSL_accept(ssl) != 1,
	("SSL_accept failed: %s", ERROR_SSL_STRING));

    ret = SSL_read(ssl, buf, BUFSIZ);
    if (ret == 0)
	return 0; /* connection closed by parent; give up. */
    ONV(ret < 0, ("SSL_read failed (%d): %s", ret, ERROR_SSL_STRING));

    CALL(s_strwrite(ssl, resp));

    /* copy out the session if requested. */
    if (sess) {
	*sess = SSL_get1_session(ssl);
    }	
    
    if (!unclean) {
	/* Erk, shutdown is messy! See Eric Rescorla's article:
	 * http://www.linuxjournal.com/article.php?sid=4822 ; we'll just
	 * hide our heads in the sand here. */
	SSL_shutdown(ssl);
	SSL_free(ssl);
    }

    return 0;
}

#define DEF_RESP "HTTP/1.0 200 OK\r\nContent-Length: 0\r\n\r\n"

/* Standard server callback to send an HTTP response; SSL negotiated
 * using certificate passed as userdata. */
static int serve_ssl(ne_socket *sock, void *ud)
{
    const char *cert = ud;

    NE_DEBUG(NE_DBG_HTTP, "using server cert %s\n", cert);

    ONN("failed to load certificate",
	!SSL_CTX_use_certificate_file(server_ctx, cert, SSL_FILETYPE_PEM));

    CALL(do_ssl_response(sock, server_ctx, NULL, DEF_RESP, 0));

    return OK;
}

static int serve_response_unclean(ne_socket *sock, void *ud)
{
    const char *resp = ud;

    ONN("failed to load certificate",
	!SSL_CTX_use_certificate_file(server_ctx, 
				      SERVER_CERT, SSL_FILETYPE_PEM));

    CALL(do_ssl_response(sock, server_ctx, NULL, resp, 1));

    return OK;
}    

/* Server function which requires use of a client cert. */
static int serve_ccert(ne_socket *sock, void *ud)
{
    const char *cert = ud;

    NE_DEBUG(NE_DBG_HTTP, "using server cert %s\n", cert);

    ONN("failed to load certificate",
	!SSL_CTX_use_certificate_file(server_ctx, cert, SSL_FILETYPE_PEM));
    
    /* require a client cert. */
    SSL_CTX_set_verify(server_ctx, SSL_VERIFY_PEER | 
		       SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);

    /* load the CA used to verify the client cert. */
    ONN("failed to load CA cert",
	SSL_CTX_load_verify_locations(server_ctx, CA_CERT, NULL) != 1);

    /* send CA cert to the client */
    SSL_CTX_set_client_CA_list(server_ctx, 
			       SSL_load_client_CA_file(CA_CERT));

    CALL(do_ssl_response(sock, server_ctx, NULL, DEF_RESP, 0));

    return OK;
}

static int fail_serve(ne_socket *sock, void *ud)
{
    serve_ssl(sock, ud);
    return OK;
}

#define DEFSESS  (ne_session_create("https", "localhost", 7777))

/* Run a request in a new session; returns ne*/
static int any_ssl_request(ne_session *sess, server_fn fn,
			   char *server_cert, char *ca_cert,
			   ne_ssl_verify_fn verify_fn, void *verify_ud)
{
    int ret;
    
    if (ca_cert)
	ONV(ne_ssl_load_ca(sess, ca_cert),
	    ("failed to load CA cert `%s'", ca_cert));

    CALL(spawn_server(7777, fn, server_cert));

    if (verify_fn)
	ne_ssl_set_verify(sess, verify_fn, verify_ud);

    ret = any_request(sess, "/foo");
    CALL(await_server());
    
    ONREQ(ret);

    return OK;
}

static int init(void)
{
    char *server_key;
 
    /* take srcdir as argv[1]. */
    if (test_argc > 1) {
	srcdir = test_argv[1];
	server_key = ne_concat(srcdir, "/server.key", NULL);
    } else {
	server_key = "server.key";
    }
    
    if (ne_sock_init()) {
	t_context("could not initialize socket/SSL library.");
	return FAILHARD;
    }

    server_ctx = SSL_CTX_new(SSLv23_server_method());
    if (server_ctx == NULL) {
	t_context("could not create SSL_CTX: %s", ERROR_SSL_STRING);
	return FAILHARD;
    } else if (!SSL_CTX_use_PrivateKey_file(server_ctx, server_key, 
					    SSL_FILETYPE_PEM)) {
	t_context("failed to load private key: %s", ERROR_SSL_STRING);
	return FAILHARD;
    }
    return OK;
}

/* just check the result codes of loading CA certs. */
static int load_ca(void)
{
    /* create a dummy session. */
    ne_session *sess = ne_session_create("https", "localhost", 7777);
    
    ONN("invalid CA cert file loaded successfully",
	ne_ssl_load_ca(sess, "Makefile") == 0);

    ONN("valid CA cert file didn't load",
	ne_ssl_load_ca(sess, CA_CERT) != 0);

    if (ne_ssl_load_default_ca(sess)) {
	t_warning("failed to load default CA certs from SSL library");
    }
    
    ne_session_destroy(sess);

    return OK;
}

static int load_pem_ccert(void)
{
    ne_session *sess = DEFSESS;

    ONV(ne_ssl_load_pem(sess, "client.cert", "client.key"),
	("client cert load failed: %s", ne_get_error(sess)));

    ne_session_destroy(sess);
    return OK;
}

static int keypw_prompt(void *userdata, char *buf, size_t len)
{
    const char *pw = userdata;
    strcpy(buf, pw);
    return 0;
}

static int load_pkcs12_ccert(void)
{
    ne_session *sess = DEFSESS;

    ne_ssl_keypw_prompt(sess, keypw_prompt, "foobar");

    ONV(ne_ssl_load_pkcs12(sess, "client.p12"),
	("client cert load failed: %s", ne_get_error(sess)));

    ne_session_destroy(sess);
    return OK;
}

static int fail_load_ccerts(void)
{
    ne_session *sess = DEFSESS;

    ONN("loaded Makefile as PKCS12 certificate",
	ne_ssl_load_pkcs12(sess, "Makefile") == 0);
    
    ONN("loaded Makefile as PEM certificate",
	ne_ssl_load_pem(sess, "Makefile", NULL) == 0);

    ne_session_destroy(sess);
    return OK;
}

/* Test that 'cert', which is signed by CA_CERT, is accepted
 * unconditionaly. */
static int accept_signed_cert(char *cert)
{
    ne_session *sess = DEFSESS;
    /* no verify callback needed. */
    CALL(any_ssl_request(sess, serve_ssl, cert, CA_CERT, NULL, NULL));
    ne_session_destroy(sess);
    return OK;
}

static int simple(void)
{
    return accept_signed_cert(SERVER_CERT);
}

/* Serves using HTTP/1.0 get-till-EOF semantics. */
static int serve_eof(ne_socket *sock, void *ud)
{
    const char *cert = ud;

    NE_DEBUG(NE_DBG_HTTP, "using server cert %s\n", cert);

    ONN("failed to load certificate",
	!SSL_CTX_use_certificate_file(server_ctx, cert, SSL_FILETYPE_PEM));

    CALL(do_ssl_response(sock, server_ctx, NULL,
			 "HTTP/1.0 200 OK\r\n"
			 "Connection: close\r\n"
			 "\r\n"
			 "This is a response body, like it or not.",
			 0));

    return OK;
}

/* Test read-til-EOF behaviour with SSL. */
static int simple_eof(void)
{
    ne_session *sess = DEFSESS;

    CALL(any_ssl_request(sess, serve_eof, SERVER_CERT, CA_CERT, NULL, NULL));
    ne_session_destroy(sess);
    return OK;
}

static int empty_truncated_eof(void)
{
    ne_session *sess = DEFSESS;
    
    CALL(any_ssl_request(sess, serve_response_unclean,
			 "HTTP/1.0 200 OK\r\n" "\r\n",
			 CA_CERT, NULL, NULL));

    ne_session_destroy(sess);
    return OK;
}

static int fail_truncated_eof(void)
{
    ne_session *sess = DEFSESS;
    int ret;
    
    ONN("failed to load CA cert", ne_ssl_load_ca(sess, CA_CERT));
    CALL(spawn_server(7777, serve_response_unclean,
		      "HTTP/1.0 200 OK\r\n" "\r\n"
		      "This is some content\n"
		      "Followed by a truncation attack!\n"));
    
    ret = any_request(sess, "/foo");
    CALL(await_server());
    
    ONV(ret != NE_ERROR,
	("request failed with %d not error: `%s'", ret, ne_get_error(sess)));
    ne_session_destroy(sess);
    return OK;
}
    

static int wildcard_match(void)
{
    ne_session *sess;
    struct stat stbuf;
    
    t_context("wildcard.cert not found:\n"
	      "This test requires a Linux-like hostname command, see makekeys.sh");
    PRECOND(stat("wildcard.cert", &stbuf) == 0);

    PRECOND(lookup_hostname() == OK);

    sess = ne_session_create("https", local_hostname, 7777);

    CALL(any_ssl_request(sess, serve_ssl, 
			 "wildcard.cert", CA_CERT, NULL, NULL));
    ne_session_destroy(sess);
    
    return OK;
}

/* Check that hostname comparisons are not cases-sensitive. */
static int caseless_match(void)
{
    return accept_signed_cert("caseless.cert");
}

/* Test that the subjectAltName extension has precedence over the
 * commonName attribute */
static int subject_altname(void)
{
    return accept_signed_cert("altname.cert");
}

/* tests for multiple altNames. */
static int two_subject_altname(void)
{
    return accept_signed_cert("altname2.cert");
}

static int two_subject_altname2(void)
{
    return accept_signed_cert("altname3.cert");
}

/* Test that a subject altname with *only* an eMail entry is
 * ignored, and the commonName is used instead. */
static int notdns_altname(void)
{
    return accept_signed_cert("altname4.cert");
}

/* test that the *most specific* commonName attribute is used. */
static int multi_commonName(void)
{
    return accept_signed_cert("twocn.cert");
}

/* regression test for neon <= 0.23.4 where if commonName was the first
 * RDN in the subject DN, it was ignored. */
static int commonName_first(void)
{
    return accept_signed_cert("cnfirst.cert");
}

/* Verify callback which checks that the certificate has the predetermined
 * values (as per makekeys.sh). */
static int check_DNs(void *userdata, int fs, const ne_ssl_certificate *cert)
{
    int *ret = userdata;
    
    if (!cert->issuer || !cert->subject) {
	*ret = -1;
	t_context("subject or issuer passed as NULL");
    } else {
	ne_ssl_dname e_subject = {
	    "GB", "Cambridgeshire", "Cambridge", "Neon Hackers Ltd",
	    "Neon QA Dept", "localhost"
	}, e_issuer = {
	    "US", "California", "Oakland", "Neosign", "Random Dept",
	    "nowhere.example.com"
	};

	*ret = 1;

#define FON(field) do { \
if (cert->subject->field == NULL) { \
    t_context("subject " #field " was NULL"); \
    *ret = -1; \
} else if (strcmp(cert->subject->field, e_subject.field)) { \
  t_context("subject " #field " expected %s got %s", e_subject.field, cert->subject->field); \
  *ret = -1; } } while (0)

	FON(country); FON(state); FON(locality); FON(organization);
	FON(organizationalUnit); FON(commonName);
	
#undef FON
#define FON(field) do { \
if (cert->issuer->field == NULL) { \
    t_context("issuer " #field " was NULL"); \
    *ret = -1; \
} else if (strcmp(cert->issuer->field, e_issuer.field)) { \
  t_context("issuer " #field " expected %s got %s", e_issuer.field, cert->issuer->field); \
  *ret = -1; } } while (0)


	FON(country); FON(state); FON(locality); FON(organization);
	FON(organizationalUnit); FON(commonName);

#undef FON

    }	
    return 0;
}

/* Check that certificate attributes are passed correctly. */
static int parse_cert(void)
{
    ne_session *sess = DEFSESS;
    int ret = 0;

    /* don't give a CA cert; should force the verify callback to be
     * used. */
    CALL(any_ssl_request(sess, serve_ssl, SERVER_CERT, NULL, 
			 check_DNs, &ret));
    ne_session_destroy(sess);

    ONN("cert verification never called", ret == 0);

    if (ret == -1)
	return FAIL;

    return OK;
}

static int count_vfy(void *userdata, int fs, const ne_ssl_certificate *c)
{
    int *count = userdata;
    (*count)++;
    return 0;
}

static int no_verify(void)
{
    ne_session *sess = DEFSESS;
    int count = 0;

    CALL(any_ssl_request(sess, serve_ssl, SERVER_CERT, CA_CERT, count_vfy,
			 &count));

    ONN("verify callback called unnecessarily", count != 0);

    ne_session_destroy(sess);

    return OK;
}

static int cache_verify(void)
{
    ne_session *sess = DEFSESS;
    int ret, count = 0;
    
    /* force verify cert. */
    ret = any_ssl_request(sess, serve_ssl, SERVER_CERT, NULL, count_vfy,
			  &count);

    CALL(spawn_server(7777, serve_ssl, SERVER_CERT));
    ret = any_request(sess, "/foo2");
    CALL(await_server());

    ONV(count != 1,
	("verify callback result not cached: called %d times", count));

    ne_session_destroy(sess);

    return OK;
}

/* Copy failures into *userdata, and fail verification. */
static int get_failures(void *userdata, int fs, const ne_ssl_certificate *c)
{
    int *out = userdata;
    *out = fs;
    return -1;
}

/* Helper function: run a request using the given self-signed server
 * certificate, and expect the request to fail with the given
 * verification failure flags. */
static int fail_ssl_request(char *cert, char *cacert, 
			    const char *msg, int failures)
{
    ne_session *sess = DEFSESS;
    int gotf = 0, ret;

    ret = any_ssl_request(sess, fail_serve, cert, cacert,
			  get_failures, &gotf);

    ONV(gotf == 0,
	("no error in verification callback; request failed: %s",
	 ne_get_error(sess)));

    ONV(gotf & ~NE_SSL_FAILMASK,
	("verification flags %x outside mask %x", gotf, NE_SSL_FAILMASK));

    /* check the failure flags were as expected. */
    ONV(failures != gotf,
	("verification flags were %d not %d", gotf, failures));

    /* and check that the request was failed too. */
    ONN(msg, ret == NE_OK);

    ne_session_destroy(sess);

    return OK;
}

/* Note that the certs used for fail_* are all self-signed, so the
 * cert is passed as CA cert and server cert to fail_ssl_request. */

/* Check that a certificate with the incorrect commonName attribute is
 * flagged as such. */
static int fail_wrongCN(void)
{
    return fail_ssl_request("wrongcn.pem", "wrongcn.pem",
			    "certificate with incorrect CN was accepted",
			    NE_SSL_CNMISMATCH);
}

/* Check that an expired certificate is flagged as such. */
static int fail_expired(void)
{
    char *c = ne_concat(srcdir, "/expired.pem", NULL);
    return fail_ssl_request(c, c, "expired certificate was accepted",
			    NE_SSL_EXPIRED);
}

static int fail_notvalid(void)
{
    char *c = ne_concat(srcdir, "/notvalid.pem", NULL);
    return fail_ssl_request(c, c, "not yet valid certificate was accepted",
			    NE_SSL_NOTYETVALID);
    
}

/* Check that a server cert with a random issuer and self-signed cert
 * fail with UNKNOWNCA. */
static int fail_untrusted_ca(void)
{
    return fail_ssl_request("server.cert", NULL, "untrusted CA.",
			    NE_SSL_UNKNOWNCA);
}

static int fail_self_signed(void)
{
    return fail_ssl_request("ssigned.pem", NULL, "self-signed cert", 
			    NE_SSL_UNKNOWNCA);
}

struct scache_args {
    SSL_CTX *ctx;
    char *cert;
    int count;
    SSL_SESSION *sess;
};

/* FIXME: factor out shared code with serve_ssl */
static int serve_scache(ne_socket *sock, void *ud)
{
    struct scache_args *args = ud;
    SSL_SESSION *sess;
    
    if (args->count == 0) {
	/* enable OpenSSL's internal session cache, enabling the
	 * negotiation to re-use a session if both sides support it. */
	SSL_CTX_set_session_cache_mode(args->ctx, SSL_SESS_CACHE_SERVER);
	
	ONN("failed to load certificate",
	    !SSL_CTX_use_certificate_file(args->ctx, 
					  args->cert, SSL_FILETYPE_PEM));
    }

    args->count++;

    CALL(do_ssl_response(sock, args->ctx, &sess, DEF_RESP, 0));

    /* dump session to child.log for debugging. */
    SSL_SESSION_print_fp(ne_debug_stream, sess);

    if (args->count == 1) {
	/* save the session. */
	args->sess = sess;
    } else {
	/* could just to do this with SSL_CTX_sess_hits really,
	 * but this is a more thorough test. */
	ONN("cached SSL session not used",
	    SSL_SESSION_cmp(args->sess, sess));
	SSL_SESSION_free(args->sess);
	SSL_SESSION_free(sess);
    }

    return 0;
}

/* Test that the SSL session is cached across connections. */
static int session_cache(void)
{
    struct scache_args args;
    ne_session *sess = ne_session_create("https", "localhost", 7777);
    
    args.ctx = server_ctx;
    args.count = 0;
    args.cert = SERVER_CERT;

    ne_ssl_load_ca(sess, CA_CERT);

    /* have spawned server listen for several connections. */
    CALL(spawn_server_repeat(7777, serve_scache, &args, 4));

    ONREQ(any_request(sess, "/req1"));
    ONREQ(any_request(sess, "/req2"));
    ne_session_destroy(sess);
    /* server should still be waiting for connections: if not,
     * something went wrong. */
    ONN("error from child", dead_server());
    /* now get rid of it. */
    reap_server();

    return OK;
}

static int client_cert_pem(void)
{
    ne_session *sess = DEFSESS;
    
    ONV(ne_ssl_load_pem(sess, "client.cert", "client.key"),
	("failed to load client cert: %s", ne_get_error(sess)));

    CALL(any_ssl_request(sess, serve_ccert, SERVER_CERT, CA_CERT,
			 NULL, NULL));    
    ne_session_destroy(sess);    

    return OK;
}

static void ccert_provider(void *userdata, ne_session *sess,
			  const ne_ssl_dname *dn)
{
    ne_ssl_load_pem(sess, "client.cert", "client.key");
}

static int client_cert_provided(void)
{
    ne_session *sess = DEFSESS;
    ne_ssl_provide_ccert(sess, ccert_provider, NULL);
    CALL(any_ssl_request(sess, serve_ccert, SERVER_CERT, CA_CERT, NULL, NULL));
    ne_session_destroy(sess);
    return OK;
}

static int client_cert_pkcs12(void)
{
    ne_session *sess = DEFSESS;

    ne_ssl_keypw_prompt(sess, keypw_prompt, "foobar");
    
    ONV(ne_ssl_load_pkcs12(sess, "client.p12"),
	("failed to load client cert: %s", ne_get_error(sess)));

    CALL(any_ssl_request(sess, serve_ccert, SERVER_CERT, CA_CERT,
			 NULL, NULL));

    ne_session_destroy(sess);    
    return OK;
}

static int serve_tunnel(ne_socket *sock, void *ud)
{
    CALL(discard_request(sock));
    
    SEND_STRING(sock, "HTTP/1.1 200 OK\r\nServer: Fish\r\n\r\n");
    
    return serve_ssl(sock, ud);
}

/* neon versions <= 0.21.2 segfault here because ne_sock_close would
 * be called twice on the socket after the server cert verification
 * fails. */
static int fail_tunnel(void)
{
    ne_session *sess = ne_session_create("https", "example.com", 443);
    ne_session_proxy(sess, "localhost", 7777);

    ONN("server cert verification didn't fail",
	any_ssl_request(sess, serve_tunnel, SERVER_CERT, CA_CERT,
			NULL, NULL) != NE_ERROR);
    
    ne_session_destroy(sess);
    return OK;
}

static int proxy_tunnel(void)
{
    ne_session *sess = ne_session_create("https", "localhost", 443);
    ne_session_proxy(sess, "localhost", 7777);
    
    /* CA cert is trusted, so no verify callback should be needed. */
    CALL(any_ssl_request(sess, serve_tunnel, SERVER_CERT, CA_CERT,
			 NULL, NULL));

    ne_session_destroy(sess);
    return OK;
}

/* TODO: code paths still to test in cert verification:
 * - server cert changes between connections: Mozilla gives
 * a "bad MAC decode" error for this; can do better?
 * - server presents no certificate (using ADH ciphers)... can
 * only really happen if they mess with the SSL_CTX and enable
 * ADH cipher manually; but good to check the failure case is 
 * safe.
 * From the SSL book:
 * - an early FIN should be returned as a possible truncation attack,
 * NOT just an NE_SOCK_CLOSED.
 * - unexpected close_notify is an error but not an attack.
 * - never attempt session resumption after any aborted connection.
 */

ne_test tests[] = {
    T(init),

    T(load_ca),

    T(load_pem_ccert),
    T(load_pkcs12_ccert),
    T(fail_load_ccerts),

    T(simple),
    T(simple_eof),
    T(empty_truncated_eof),
    T(fail_truncated_eof),

    T(client_cert_pem),
    T(client_cert_pkcs12),
    T(client_cert_provided),

    T(parse_cert),
    T(no_verify),
    T(cache_verify),
    T(wildcard_match),
    T(caseless_match),

    T(subject_altname),
    T(two_subject_altname),
    T(two_subject_altname2),
    T(notdns_altname),

    T(multi_commonName),
    T(commonName_first),

    T(fail_wrongCN),
    T(fail_expired),
    T(fail_notvalid),
    T(fail_untrusted_ca),
    T(fail_self_signed),

    T(session_cache),
	
    T(fail_tunnel),
    T(proxy_tunnel),

    T(NULL) 
};
