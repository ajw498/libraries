# Copyright (C) 1998-2002 Joe Orton <joe@manyfish.co.uk>    -*- autoconf -*-
#
# This file is free software; you may copy and/or distribute it with
# or without modifications, as long as this notice is preserved.
# This software is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.

# The above license applies to THIS FILE ONLY, the neon library code
# itself may be copied and distributed under the terms of the GNU
# LGPL, see COPYING.LIB for more details

# This file is part of the neon HTTP/WebDAV client library.
# See http://www.webdav.org/neon/ for the latest version. 
# Please send any feedback to <neon@webdav.org>

# Check for XML parser.
# Supports:
#  *  libxml 1.x (requires version 1.8.3 or later)
#  *  libxml 2.x
#  *  jclark expat in -lexpat (custom build)
#  *  new expat in -lexpat
#  *  expat in -lxmlparse and -lxmltok (as packaged by Debian/Red Hat)
#  *  Bundled expat if a directory name argument is passed
#     -> expat dir must contain minimal expat sources, i.e.
#        xmltok, xmlparse sub-directories.  See sitecopy/cadaver for
#	 examples of how to do this.
#
# Usage: 
#  NEON_XML_PARSER()
# or
#  NEON_XML_PARSER(expat-dir)
#
# FIXME: needs to take second arg for VPATH builds

AC_DEFUN([NEON_XML_EXTERNAL_EXPAT], [
ne_found_hdr=no
case $neon_expat_dir in
*/libexpat.la)
	neon_using_libtool_expat=yes
	neon_expat_dir=`echo $neon_expat_dir | sed 's:/libexpat.la$::'`
esac
if test -r "$neon_expat_dir/xmlparse.h"; then
        ne_found_hdr=yes
	AC_DEFINE(HAVE_XMLPARSE_H, 1, [Define if you have xmlparse.h])
fi
if test -r "$neon_expat_dir/expat.h"; then
       ne_found_hdr=yes
       AC_DEFINE(HAVE_EXPAT_H, 1, [Define if you have expat.h])
fi
if test "$ne_found_hdr" = "yes"; then
	AC_DEFINE(HAVE_EXPAT, 1, [Define if you have expat])
	CFLAGS="$CFLAGS -I$neon_expat_dir"
	dnl add the library (if it isn't a libtool library)
	if test -z "$neon_using_libtool_expat"; then
		NEON_LIBS="$NEON_LIBS -L$neon_expat_dir -lexpat"
	fi
	neon_xml_parser_message="expat in $neon_expat_dir"
	neon_found_parser="yes"
fi
])

AC_DEFUN([NEON_XML_SYSTEM_EXPAT], [
ne_found_hdr=no
AC_CHECK_HEADERS(expat.h xmlparse.h xmltok/xmlparse.h, ne_found_hdr=yes)
if test "$ne_found_hdr" = "yes"; then
ne_found_lib=no
AC_CHECK_LIB(expat, XML_Parse, ne_found_lib="-lexpat",
AC_CHECK_LIB(xmlparse, XML_Parse, ne_found_lib="-lxmltok -lxmlparse",,-lxmltok))
if test "$ne_found_lib" != "no"; then
	AC_DEFINE(HAVE_EXPAT, 1, [Define if you have expat])
	NEON_LIBS="$NEON_LIBS $ne_found_lib"
	neon_xml_parser_message="expat in $ne_found_lib"
	neon_found_parser="expat"
fi
fi
])

dnl Check for libxml's parser.h
AC_DEFUN([NEON_FIND_PARSER_H], [
AC_CHECK_HEADERS(parser.h,,[
 AC_CHECK_HEADERS(libxml/parser.h,,[
  AC_MSG_ERROR([could not find parser.h, libxml installation problem?])])])
])

AC_DEFUN([NEON_XML_LIBXML2], [
# Check for libxml2
AC_CHECK_PROG(XML2_CONFIG, xml2-config, xml2-config)
if test "$XML2_CONFIG" != ""; then
	neon_found_parser="libxml2"
	neon_xml_parser_message="libxml `$XML2_CONFIG --version`"
	AC_DEFINE(HAVE_LIBXML, 1, [Define if you have libxml])
	# xml2-config in some versions erroneously includes -I/include
	# in the --cflags output.
	CPPFLAGS="$CPPFLAGS `$XML2_CONFIG --cflags | sed 's| -I/include||g'`"
	NEON_LIBS="$NEON_LIBS `$XML2_CONFIG --libs | sed 's|-L/usr/lib ||g'`"
	AC_CHECK_HEADERS(xmlversion.h libxml/xmlversion.h)
	NEON_FIND_PARSER_H
fi
])

AC_DEFUN([NEON_XML_LIBXML1], [
# Have we got libxml 1.8.3 or later?
AC_CHECK_PROG(XML_CONFIG, xml-config, xml-config)
if test "$XML_CONFIG" != ""; then
	# Check for recent library
	oLIBS="$LIBS"
	NEWLIBS="`$XML_CONFIG --libs`"
	LIBS="$LIBS $NEWLIBS"
	AC_CHECK_LIB(xml, xmlCreatePushParserCtxt, [
		neon_found_parser="libxml" 
		CPPFLAGS="$CPPFLAGS `$XML_CONFIG --cflags`"
		NEON_FIND_PARSER_H
		neon_xml_parser_message="libxml `$XML_CONFIG --version`"
		AC_DEFINE(HAVE_LIBXML, 1, [Define if you have libxml])
		NEON_LIBS="$NEON_LIBS $NEWLIBS"
	], [AC_WARN([cannot use old libxml (1.8.3 or newer required)])])
	LIBS="$oLIBS"
fi
])

AC_DEFUN([NEON_XML_PARSER], [

if test "$NEON_NEED_XML_PARSER" = "yes"; then

neon_xml_choice="none"
neon_found_parser="none"

AC_ARG_WITH([libxml1],
AC_HELP_STRING([--with-libxml1], [force use of libxml 1.x]),
[if test "$withval" = "yes"; then
   neon_xml_choice=libxml1
fi])

AC_ARG_WITH([libxml2],
AC_HELP_STRING([--with-libxml2], [force use of libxml 2.x]),
[if test "$withval" = "yes"; then
   neon_xml_choice=libxml2
fi])

AC_ARG_WITH([expat], 
AC_HELP_STRING([--with-expat], [force use of expat]), [
case $withval in
yes) neon_xml_choice=findexpat ;;
no) : ;;
*) neon_xml_choice=thisexpat
   neon_expat_dir=$withval ;;
esac
])

ifelse($#, 1, [
AC_ARG_WITH([included-expat],
AC_HELP_STRING([--with-included-expat], [use bundled expat sources]),
[if test "$withval" = "yes"; then
   neon_xml_choice=skip
fi])
])

echo Choice of XML parser is $neon_xml_choice >&5

case $neon_xml_choice in
skip) : ;;
none)
	# Try them all.
	NEON_XML_LIBXML2
	if test "$neon_found_parser" = "none"; then
		NEON_XML_LIBXML1
		if test "$neon_found_parser" = "none"; then
			NEON_XML_SYSTEM_EXPAT
		fi
	fi
	;;
thisexpat) NEON_XML_EXTERNAL_EXPAT ;;
findexpat) NEON_XML_SYSTEM_EXPAT ;;
libxml1) NEON_XML_LIBXML1 ;;
libxml2) NEON_XML_LIBXML2 ;;
esac

if test "$neon_found_parser" = "none"; then
	ifelse($#, 1, [

	AC_REQUIRE([AC_C_BIGENDIAN])
	# Define XML_BYTE_ORDER for expat sources.
	if test $ac_cv_c_bigendian = "yes"; then
		ne_border=21
	else
		ne_border=12
	fi

	# mini-expat doesn't pick up config.h
	CPPFLAGS="$CPPFLAGS -DXML_BYTE_ORDER=$ne_border"

	# Use the bundled expat sources
	AC_LIBOBJ($1/xmltok/xmltok)
	AC_LIBOBJ($1/xmltok/xmlrole)
	AC_LIBOBJ($1/xmlparse/xmlparse)
	AC_LIBOBJ($1/xmlparse/hashtable)
	CFLAGS="$CFLAGS -DXML_DTD -I$1/xmlparse -I$1/xmltok"
	AC_DEFINE(HAVE_EXPAT, 1, [Define if you have expat])
	AC_DEFINE(HAVE_XMLPARSE_H, 1, [Define if you have xmlparse.h])
	neon_xml_parser_message="supplied expat in $1"
    ], [
	AC_MSG_ERROR([no XML parser was found: expat or libxml>=1.8.3 required])
    ])
fi

AC_MSG_NOTICE([XML parser found: $neon_xml_parser_message])

fi

])
