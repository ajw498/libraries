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

/*
 * apr_ldap.h is generated from apr_ldap.h.in by configure -- do not edit apr_ldap.h
 */
/**
 * @file apr_ldap.h
 * @brief  APR-UTIL LDAP 
 */
#ifndef APU_LDAP_H
#define APU_LDAP_H

/**
 * @defgroup APR_Util_LDAP LDAP
 * @ingroup APR_Util
 * @{
 */


/*
 * This switches LDAP support on or off.
 */

/* this will be defined if LDAP support was compiled into apr-util */
#undef	APU_HAS_LDAP

/* this whole thing disappears if LDAP is not enabled */
#ifdef APU_HAS_LDAP

/* LDAP secure capabilities */
#undef	APU_HAS_LDAP_NETSCAPE_SSL
#undef	APU_HAS_LDAP_STARTTLS

/* LDAP header files */





/*
 * LDAP Compatibility
 */

#if LDAP_VERSION_MAX <= 2
int ldap_search_ext_s(LDAP *ldap, char *base, int scope, char *filter,
		      char **attrs, int attrsonly, void *servertrls, void *clientctrls,
		      void *timeout, int sizelimit, LDAPMessage **res);
void ldap_memfree(void *p);

/* The const_cast is used to get around the fact that some of the LDAPv2 prototypes
 * have non-const parameters, while the same ones in LDAPv3 are const. If compiling
 * with LDAPv2, the const_cast casts away the constness, but won't under LDAPv3
 */
#define const_cast(x) ((char *)(x))
#else
#define const_cast(x) (x)
#endif /* LDAP_VERSION_MAX */

/* Define some errors that are mysteriously gone from OpenLDAP 2.x */
#ifndef LDAP_URL_ERR_NOTLDAP
#define LDAP_URL_ERR_NOTLDAP LDAP_URL_ERR_BADSCHEME
#endif

#ifndef LDAP_URL_ERR_NODN
#define LDAP_URL_ERR_NODN LDAP_URL_ERR_BADURL
#endif

/** @} */
#endif /* APU_HAS_LDAP */
#endif /* APU_LDAP_H */
