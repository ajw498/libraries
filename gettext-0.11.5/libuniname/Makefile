# Makefile.in generated automatically by automake 1.5 from Makefile.am.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /home/riscos/cross/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/gettext
pkglibdir = $(libdir)/gettext
pkgincludedir = $(includedir)/gettext
top_builddir = ..

ACLOCAL = ${SHELL} /home/cross/libraries/gettext-0.11.5/missing --run aclocal
AUTOCONF = ${SHELL} /home/cross/libraries/gettext-0.11.5/missing --run autoconf
AUTOMAKE = ${SHELL} /home/cross/libraries/gettext-0.11.5/missing --run automake
AUTOHEADER = ${SHELL} /home/cross/libraries/gettext-0.11.5/missing --run autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = arm-riscos-aof
host_triplet = arm-riscos-aof
AMTAR = ${SHELL} /home/cross/libraries/gettext-0.11.5/missing --run tar
AS = as
AWK = mawk
BUILDJAVA = no
BUILDJAVAEXE = no
BUILD_INCLUDED_LIBINTL = yes
CATOBJEXT = .gmo
CC = gcc
CLASSPATH = 
CLASSPATH_SEPARATOR = :
CROSS_COMPILING = yes
CXX = c++
DATADIRNAME = share
DEPDIR = .deps
DLLTOOL = dlltool
DVIPS = /home/cross/libraries/gettext-0.11.5/missing dvips
ECHO = echo
EMACS = emacs
EXEEXT = 
GCC = yes
GCJ = none
GCJFLAGS = 
GENCAT = gencat
GLIBC21 = no
GMSGFMT = /usr/bin/msgfmt
HAVE_GCJ = 
HAVE_GCJ_C = 
HAVE_GCJ_IN_PATH = 
HAVE_GIJ = 
HAVE_GIJ_IN_PATH = 
HAVE_JAVA = 
HAVE_JAVAC = 
HAVE_JAVAC_IN_PATH = 
HAVE_JAVA_IN_PATH = 
HAVE_JIKES = 
HAVE_JIKES_IN_PATH = 
HAVE_JRE = 
HAVE_JRE_IN_PATH = 
HAVE_JVIEW = 
HAVE_JVIEW_IN_PATH = 
HAVE_LIB = @HAVE_LIB@
HAVE__BOOL = 0
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
INSTOBJEXT = .mo
INTLBISON = bison
INTLLIBS = ${top_builddir}/intl/libintl.la 
INTLOBJS = $(GETTOBJS)
INTL_LIBTOOL_SUFFIX_PREFIX = l
JAR = 
JAVA = 
JAVAC = 
LD = /home/riscos/cross-7.7.2002/bin/arm-riscos-aof/2_95_4/ld
LEX = flex
LEX_OUTPUT_ROOT = lex.yy
LIB = @LIB@
LIBEXPAT = /home/riscos/cross/local/lib/libexpat.a
LIBICONV = 
LIBINTL = ${top_builddir}/intl/libintl.la 
LIBOBJS =  vasprintf.o getline.o pfnmatch.o mkdtemp.o
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTALLOCA = 
LTLIB = @LTLIB@
LTLIBEXPAT = -L/home/riscos/cross/local/lib -lexpat
LTLIBICONV = 
LTLIBINTL = ${top_builddir}/intl/libintl.la 
LTLIBOBJS =  vasprintf.lo getline.lo pfnmatch.lo mkdtemp.lo
MKINSTALLDIRS = ./mkinstalldirs
OBJDUMP = objdump
OBJEXT = o
PACKAGE = gettext
PERL = /usr/bin/perl
POSUB = po
RANLIB = ranlib
STDBOOL_H = stdbool.h
STRIP = strip
TESTJAVA = no
TEXI2PDF = /home/cross/libraries/gettext-0.11.5/missing texi2pdf
USE_INCLUDED_LIBINTL = yes
USE_NLS = yes
VERSION = 0.11.5
YACC = bison -y
aclocaldir = ${datadir}/aclocal
am__include = include
am__quote = 
install_sh = /home/cross/libraries/gettext-0.11.5/install-sh
lispdir = ${datadir}/emacs/site-lisp
with_gnu_ld = no

AUTOMAKE_OPTIONS = 1.5 gnits no-dependencies

noinst_LIBRARIES = libuniname.a

libuniname_a_SOURCES = uniname.h uniname.c uninames.h

INCLUDES = -I.. -I../lib -I$(top_srcdir)/lib

TESTS = test-names.sh
TESTS_ENVIRONMENT = top_srcdir=$(top_srcdir) $(SHELL)

noinst_PROGRAMS = test-names
test_names_LDADD = libuniname.a ../lib/libgettextlib.la

EXTRA_DIST = $(TESTS) gen-uninames UnicodeDataNames.txt
subdir = libuniname
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
LIBRARIES = $(noinst_LIBRARIES)

libuniname_a_AR = $(AR) cru
libuniname_a_LIBADD =
am_libuniname_a_OBJECTS = uniname.$(OBJEXT)
libuniname_a_OBJECTS = $(am_libuniname_a_OBJECTS)
noinst_PROGRAMS = test-names$(EXEEXT)
PROGRAMS = $(noinst_PROGRAMS)

test_names_SOURCES = test-names.c
test_names_OBJECTS = test-names.$(OBJEXT)
test_names_DEPENDENCIES = libuniname.a ../lib/libgettextlib.la
test_names_LDFLAGS =

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)
CPPFLAGS = -I/home/riscos/cross/local/include
LDFLAGS = 
LIBS = 
depcomp =
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(DEFAULT_INCLUDES) \
	$(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
CFLAGS = -D_INTL_REDIRECT_MACROS
DIST_SOURCES = $(libuniname_a_SOURCES) test-names.c
DIST_COMMON = ChangeLog Makefile.am Makefile.in
SOURCES = $(libuniname_a_SOURCES) test-names.c

all: all-am

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnits  libuniname/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status

AR = ar

clean-noinstLIBRARIES:
	-test -z "$(noinst_LIBRARIES)" || rm -f $(noinst_LIBRARIES)
libuniname.a: $(libuniname_a_OBJECTS) $(libuniname_a_DEPENDENCIES) 
	-rm -f libuniname.a
	$(libuniname_a_AR) libuniname.a $(libuniname_a_OBJECTS) $(libuniname_a_LIBADD)
	$(RANLIB) libuniname.a

clean-noinstPROGRAMS:
	-test -z "$(noinst_PROGRAMS)" || rm -f $(noinst_PROGRAMS)
test-names$(EXEEXT): $(test_names_OBJECTS) $(test_names_DEPENDENCIES) 
	@rm -f test-names$(EXEEXT)
	$(LINK) $(test_names_LDFLAGS) $(test_names_OBJECTS) $(test_names_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

.c.o:
	$(COMPILE) -c `test -f $< || echo '$(srcdir)/'`$<

.c.obj:
	$(COMPILE) -c `cygpath -w $<`

.c.lo:
	$(LTCOMPILE) -c -o $@ `test -f $< || echo '$(srcdir)/'`$<
uninstall-info-am:

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || etags $(ETAGS_ARGS) $$tags  $$unique $(LISP)

GTAGS:
	here=`CDPATH=: && cd $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH

check-TESTS: $(TESTS)
	@failed=0; all=0; xfail=0; xpass=0; \
	srcdir=$(srcdir); export srcdir; \
	list='$(TESTS)'; \
	if test -n "$$list"; then \
	  for tst in $$list; do \
	    if test -f ./$$tst; then dir=./; \
	    elif test -f $$tst; then dir=; \
	    else dir="$(srcdir)/"; fi; \
	    if $(TESTS_ENVIRONMENT) $${dir}$$tst; then \
	      all=`expr $$all + 1`; \
	      case " $(XFAIL_TESTS) " in \
	      *" $$tst "*) \
	        xpass=`expr $$xpass + 1`; \
	        failed=`expr $$failed + 1`; \
	        echo "XPASS: $$tst"; \
	      ;; \
	      *) \
	        echo "PASS: $$tst"; \
	      ;; \
	      esac; \
	    elif test $$? -ne 77; then \
	      all=`expr $$all + 1`; \
	      case " $(XFAIL_TESTS) " in \
	      *" $$tst "*) \
	        xfail=`expr $$xfail + 1`; \
	        echo "XFAIL: $$tst"; \
	      ;; \
	      *) \
	        failed=`expr $$failed + 1`; \
	        echo "FAIL: $$tst"; \
	      ;; \
	      esac; \
	    fi; \
	  done; \
	  if test "$$failed" -eq 0; then \
	    if test "$$xfail" -eq 0; then \
	      banner="All $$all tests passed"; \
	    else \
	      banner="All $$all tests behaved as expected ($$xfail expected failures)"; \
	    fi; \
	  else \
	    if test "$$xpass" -eq 0; then \
	      banner="$$failed of $$all tests failed"; \
	    else \
	      banner="$$failed of $$all tests did not behave as expected ($$xpass unexpected passes)"; \
	    fi; \
	  fi; \
	  dashes=`echo "$$banner" | sed s/./=/g`; \
	  echo "$$dashes"; \
	  echo "$$banner"; \
	  echo "$$dashes"; \
	  test "$$failed" -eq 0; \
	fi

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    $(mkinstalldirs) "$(distdir)/$$dir"; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir) \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
	$(MAKE) $(AM_MAKEFLAGS) check-TESTS
check: check-am
all-am: Makefile $(LIBRARIES) $(PROGRAMS)

installdirs:

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libtool clean-noinstLIBRARIES \
	clean-noinstPROGRAMS mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-compile distclean-generic \
	distclean-libtool distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

uninstall-am: uninstall-info-am

.PHONY: GTAGS all all-am check check-TESTS check-am clean clean-generic \
	clean-libtool clean-noinstLIBRARIES clean-noinstPROGRAMS \
	distclean distclean-compile distclean-generic distclean-libtool \
	distclean-tags distdir dvi dvi-am info info-am install \
	install-am install-data install-data-am install-exec \
	install-exec-am install-info install-info-am install-man \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic mostlyclean \
	mostlyclean-compile mostlyclean-generic mostlyclean-libtool \
	tags uninstall uninstall-am uninstall-info-am

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
