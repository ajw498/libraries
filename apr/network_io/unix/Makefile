srcdir = .


TARGETS = \
	sendrecv.lo \
	sockets.lo \
	sockopt.lo \
	sockaddr.lo \
	inet_ntop.lo \
	inet_pton.lo

# bring in rules.mk for standard functionality
include /home/cross/libraries/apr/build/rules.mk

INCDIR=../../include
OSDIR=$(INCDIR)/arch/unix
DEFOSDIR=$(INCDIR)/arch/unix
INCLUDES=-I$(INCDIR) -I$(OSDIR) -I$(DEFOSDIR)

# DO NOT REMOVE
