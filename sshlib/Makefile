
CC	=	gcc
COPTS	=	-mthrowback -Wall -Iunix -I. -Icharset -mpoke-function-name -std=gnu9x
LINK	=	gcc
LINKOPTS=	#-rescan
VPATH	=	charset unix
LIBS	=	librossh.a
#\
#		ADFS::Venice.$.Code.gcc.!gcc.bin.arm-riscos-aof.3_3.apcs32.arch3.unixlib.o.unixlib \
#		ADFS::Venice.$.Code.gcc.!gcc.bin.arm-riscos-aof.3_3.apcs32.arch3.unixlib.o.libgcc

OBJS	=	test.o

SSHOBJS	= 	be_all.o cmdline.o ldisc.o logging.o misc.o portfwd.o proxy.o \
		settings.o signal.o ssh.o sshaes.o sshblowf.o \
		sshbn.o sshcrc.o sshcrcda.o sshdes.o sshdh.o sshdss.o \
		sshmd5.o sshpubk.o sshrand.o sshrsa.o sshsh512.o sshsha.o \
		sshzlib.o tree234.o ux_x11.o roagentc.o uxcons.o \
		uxmisc.o uxnet.o uxnoise.o uxplink.o uxproxy.o uxsel.o \
		rostore.o version.o wildcard.o x11fwd.o

.SUFFIXES:	.o .c

# default target
test:		$(OBJS) $(LIBS)
		$(LINK) $(LINKOPTS) -o $@ $(OBJS) $(LIBS)

clean:;		rm -f $(OBJS) $(SSHOBJS)
		rm -f test
		rm -f librossh.a

librossh.a:	$(SSHOBJS)
		libfile -c $@ $(SSHOBJS)

install:
		cp librossh.a $(PREFIX)/lib/librossh.a

.c.o:;		$(CC) $(COPTS) -c -o $@ $<
