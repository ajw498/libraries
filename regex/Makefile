# Generated automatically from Makefile.in by configure.
SHELL = /bin/sh

srcdir=.

CC=gcc
RANLIB=ranlib

# You probably want to take -DREDEBUG out of CFLAGS, and put something like
# -O in, *after* testing (-DREDEBUG strengthens testing by enabling a lot of
# internal assertion checking and some debugging facilities).
# Put -Dconst= in for a pre-ANSI compiler.
# Do not take -DPOSIX_MISTAKE out.
# REGCFLAGS isn't important to you (it's for my use in some special contexts).
CFLAGS= -DPOSIX_MISTAKE -O2 -I. -DPHP_NO_ALIASES

# If you have a pre-ANSI compiler, put -o into MKHFLAGS.  If you want
# the Berkeley __P macro, put -b in.
MKHFLAGS=

# Flags for linking but not compiling, if any.
LDFLAGS=

# Extra libraries for linking, if any.
LIBS=

# Internal stuff, should not need changing.
OBJPRODN = regcomp.o regexec.o regerror.o regfree.o
OBJS=$(OBJPRODN) split.o debug.o main.o
H=cclass.h cname.h regex2.h utils.h
REGSRC=regcomp.c regerror.c regexec.c regfree.c
ALLSRC=$(REGSRC) engine.c debug.c main.c split.c

# Stuff that matters only if you're trying to lint the package.
LINTFLAGS=-I. -Dstatic= -Dconst= -DREDEBUG
LINTC=regcomp.c regexec.c regerror.c regfree.c debug.c main.c
JUNKLINT=possible pointer alignment|null effect

# arrangements to build forward-reference header files
.SUFFIXES:	.ih .h .c

.ih.h:
	sh $(srcdir)/mkh $(MKHFLAGS) -p $< >$(srcdir)/$@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

all lib: libregex.a

libregex.a: $(OBJS)
	ar -c libregex.a $(OBJPRODN)

default:	r

purge:
	rm -f *.o

# stuff to build regex.h
REGEXH=regex.h
REGEXHSRC=regex2.h $(REGSRC)
# these are in CVS
#$(REGEXH):	$(REGEXHSRC) mkh
#	sh ./mkh $(MKHFLAGS) -i _REGEX_H_ $(REGEXHSRC) >regex.h
#cmp -s regex.tmp regex.h 2>/dev/null || cp regex.tmp regex.h
#rm -f regex.tmp

# dependencies
regcomp.o regexec.o regerror.o regfree.o debug.o:	utils.h regex.h regex2.h
regcomp.o:	cclass.h cname.h regcomp.h
regexec.o:	engine.c engine.h
regerror.o:	regerror.h
debug.o:	debug.h
main.o:	main.ih

mf.tmp:	Makefile
	sed '/^REGEXH=/s/=.*/=regex.h/' Makefile | sed '/#DEL$$/d' >$@

# various forms of cleanup
tidy:
	rm -f junk* core core.* *.core dtr *.tmp lint

clean:	tidy
	rm -f *.o *.s re libregex.a

install:
	mkdir -p $(PREFIX)/lib $(PREFIX)/include
	cp libregex.a $(PREFIX)/lib
	cp regex.h $(PREFIX)/include
