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

AUTOMAKE_OPTIONS = 1.2 gnits

RM = rm -f

projectsdir = $(pkgdatadir)/projects

PROJECTS = TP KDE GNOME
SCRIPTFILES = team-address \
	TP/trigger TP/team-address \
	KDE/trigger KDE/team-address \
	GNOME/trigger GNOME/team-address

DATAFILES = index \
	TP/teams.url TP/teams.html \
	KDE/teams.url KDE/teams.html \
	GNOME/teams.url GNOME/teams.html

EXTRA_DIST = $(SCRIPTFILES) $(DATAFILES)
subdir = projects
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
DIST_SOURCES =
DIST_COMMON = ChangeLog Makefile.am Makefile.in
all: all-am

.SUFFIXES:

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnits  projects/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status
uninstall-info-am:
tags: TAGS
TAGS:


DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	$(mkinstalldirs) $(distdir)/GNOME $(distdir)/KDE $(distdir)/TP
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
check: check-am
all-am: Makefile

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

clean-am: clean-generic clean-libtool mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-generic distclean-libtool

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am: install-data-local

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic mostlyclean-libtool

uninstall-am: uninstall-info-am uninstall-local

.PHONY: all all-am check check-am clean clean-generic clean-libtool \
	distclean distclean-generic distclean-libtool distdir dvi \
	dvi-am info info-am install install-am install-data \
	install-data-am install-data-local install-exec install-exec-am \
	install-info install-info-am install-man install-strip \
	installcheck installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-generic \
	mostlyclean-libtool uninstall uninstall-am uninstall-info-am \
	uninstall-local


install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(projectsdir)
	@for p in $(PROJECTS); do \
	  echo "$(mkinstalldirs) $(DESTDIR)$(projectsdir)/$$p"; \
	  $(mkinstalldirs) $(DESTDIR)$(projectsdir)/$$p; \
	done
	@for f in $(SCRIPTFILES); do \
	  echo "$(INSTALL_SCRIPT) $(srcdir)/$$f $(DESTDIR)$(projectsdir)/$$f"; \
	  $(INSTALL_SCRIPT) $(srcdir)/$$f $(DESTDIR)$(projectsdir)/$$f; \
	done
	@for f in $(DATAFILES); do \
	  echo "$(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(projectsdir)/$$f"; \
	  $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(projectsdir)/$$f; \
	done

installdirs-local:
	$(mkinstalldirs) $(DESTDIR)$(projectsdir)
	@for p in $(PROJECTS); do \
	  echo "$(mkinstalldirs) $(DESTDIR)$(projectsdir)/$$p"; \
	  $(mkinstalldirs) $(DESTDIR)$(projectsdir)/$$p; \
	done

uninstall-local:
	@for f in $(SCRIPTFILES); do \
	  echo "$(RM) $(DESTDIR)$(projectsdir)/$$f"; \
	  $(RM) $(DESTDIR)$(projectsdir)/$$f; \
	done
	@for f in $(DATAFILES); do \
	  echo "$(RM) $(DESTDIR)$(projectsdir)/$$f"; \
	  $(RM) $(DESTDIR)$(projectsdir)/$$f; \
	done

# One more automake bug.
installdirs: installdirs-local
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
