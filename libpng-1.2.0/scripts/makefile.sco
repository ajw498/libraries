# makefile for SCO OSr5  ELF and Unixware 7 with Native cc
# Contributed by Mike Hopkirk (hops@sco.com) modified from Makefile.lnx
#   force ELF build dynamic linking, SONAME setting in lib and RPATH in app
# Copyright (C) 1998 Greg Roelofs
# Copyright (C) 1996, 1997 Andreas Dilger
# For conditions of distribution and use, see copyright notice in png.h

CC=cc

# where make install puts libpng.a, libpng.so*, and png.h
prefix=/usr/local

# Where the zlib library and include files are located
#ZLIBLIB=/usr/local/lib
#ZLIBINC=/usr/local/include
ZLIBLIB=../zlib
ZLIBINC=../zlib

CFLAGS= -dy -belf -I$(ZLIBINC) -O3
LDFLAGS=-L. -L$(ZLIBLIB) -lpng -lz -lm

#RANLIB=ranlib
RANLIB=echo

# read libpng.txt or png.h to see why PNGMAJ is 3.  You should not
# have to change it.
PNGMAJ = 3
PNGMIN = 1.2.0
PNGVER = $(PNGMAJ).$(PNGMIN)

INCPATH=$(prefix)/include
LIBPATH=$(prefix)/lib

OBJS = png.o pngset.o pngget.o pngrutil.o pngtrans.o pngwutil.o \
	pngread.o pngrio.o pngwio.o pngwrite.o pngrtran.o \
	pngwtran.o pngmem.o pngerror.o pngpread.o

OBJSDLL = $(OBJS:.o=.pic.o)

.SUFFIXES:      .c .o .pic.o

.c.pic.o:
	$(CC) -c $(CFLAGS) -KPIC -o $@ $*.c

all: libpng.a libpng.so pngtest

libpng.a: $(OBJS)
	ar rc $@ $(OBJS)
	$(RANLIB) $@

libpng.so: libpng.so.$(PNGMAJ)
	ln -f -s libpng.so.$(PNGMAJ) libpng.so

libpng.so.$(PNGMAJ): libpng.so.$(PNGVER)
	ln -f -s libpng.so.$(PNGVER) libpng.so.$(PNGMAJ)

libpng.so.$(PNGVER): $(OBJSDLL)
	$(CC) -G  -Wl,-h,libpng.so.$(PNGMAJ) -o libpng.so.$(PNGVER) \
	 $(OBJSDLL)

pngtest: pngtest.o libpng.so
	LD_RUN_PATH=.:$(ZLIBLIB) $(CC) -o pngtest $(CFLAGS) pngtest.o $(LDFLAGS)

test: pngtest
	./pngtest

install: libpng.a libpng.so.$(PNGVER)
	-@mkdir $(INCPATH) $(LIBPATH)
	cp png.h pngconf.h $(INCPATH)
	chmod 644 $(INCPATH)/png.h $(INCPATH)/pngconf.h
	cp libpng.a libpng.so.$(PNGVER) $(LIBPATH)
	chmod 755 $(LIBPATH)/libpng.so.$(PNGVER)
	-@/bin/rm -f $(LIBPATH)/libpng.so.$(PNGMAJ) $(LIBPATH)/libpng.so
	(cd $(LIBPATH); ln -f -s libpng.so.$(PNGVER) libpng.so.$(PNGMAJ); \
	 ln -f -s libpng.so.$(PNGMAJ) libpng.so)

clean:
	/bin/rm -f *.o libpng.a libpng.so* pngtest pngout.png

DOCS = ANNOUNCE CHANGES INSTALL KNOWNBUG LICENSE README TODO Y2KINFO
writelock:
	chmod a-w *.[ch35] $(DOCS) scripts/*

# DO NOT DELETE THIS LINE -- make depend depends on it.

png.o png.pic.o: png.h pngconf.h
pngerror.o pngerror.pic.o: png.h pngconf.h
pngrio.o pngrio.pic.o: png.h pngconf.h
pngwio.o pngwio.pic.o: png.h pngconf.h
pngmem.o pngmem.pic.o: png.h pngconf.h
pngset.o pngset.pic.o: png.h pngconf.h
pngget.o pngget.pic.o: png.h pngconf.h
pngread.o pngread.pic.o: png.h pngconf.h
pngrtran.o pngrtran.pic.o: png.h pngconf.h
pngrutil.o pngrutil.pic.o: png.h pngconf.h
pngtrans.o pngtrans.pic.o: png.h pngconf.h
pngwrite.o pngwrite.pic.o: png.h pngconf.h
pngwtran.o pngwtran.pic.o: png.h pngconf.h
pngwutil.o pngwutil.pic.o: png.h pngconf.h
pngpread.o pngpread.pic.o: png.h pngconf.h

pngtest.o: png.h pngconf.h
