srcdir = .


TARGETS = \
	copy.lo \
	dir.lo \
	fileacc.lo \
	filedup.lo \
	filepath.lo \
	filestat.lo \
	flock.lo \
	fullrw.lo \
	open.lo \
	pipe.lo \
	readwrite.lo \
	seek.lo \
	mktemp.lo

# bring in rules.mk for standard functionality
include /home/cross/libraries/apr/build/rules.mk

INCDIR=../../include
OSDIR=$(INCDIR)/arch/unix
DEFOSDIR=$(INCDIR)/arch/unix
INCLUDES=-I$(INCDIR) -I$(OSDIR) -I$(DEFOSDIR)

# DO NOT REMOVE
