srcdir = .


TARGETS = \
	proc.lo \
	procsup.lo \
	thread.lo \
	threadpriv.lo \
	signals.lo

# bring in rules.mk for standard functionality
include /home/cross/libraries/apr/build/rules.mk

INCDIR=../../include
DEFOSDIR=$(INCDIR)/arch/unix
INCLUDES=-I$(INCDIR) -I$(DEFOSDIR)

# DO NOT REMOVE
