srcdir = .


NONPORTABLE = \
	testshm \
	testprocmutex \
	testglobalmutex \

PROGRAMS = \
	client \
	sendfile \
	server \
	testfile \
	testdir \
	testnames \
	testflock \
	testproc \
	testsock \
	testthread \
	testlock \
	testlockperf \
	testargs \
	testshmproducer \
	testshmconsumer \
	testpipe \
	testoc \
	testsockopt \
	testpoll \
	testhash \
	occhild \
	testuser \
	testsockets \
	testrand \
	testdup \
	testatomic \
	testmutexscope \
	testall


TARGETS = $(PROGRAMS) $(NONPORTABLE)

# bring in rules.mk for standard functionality
include /home/cross/libraries/apr/build/rules.mk

LOCAL_LIBS=../libapr-${APR_MAJOR_VERSION}.la

CLEAN_TARGETS = testfile.tmp testdso mod_test.slo

INCDIR=../include
INCLUDES=-I$(INCDIR)

CFLAGS=$(MY_CFLAGS)

all: $(PROGRAMS) $(NONPORTABLE)

check: $(PROGRAMS) $(NONPORTABLE)
	for prog in $(PROGRAMS) $(NONPORTABLE); do \
		./$$prog; \
		if test $$i = 255; then \
			echo "$$prog failed"; \
			break; \
		fi \
	done

testfile: testfile.lo $(LOCAL_LIBS)
	$(LINK) testfile.lo $(LOCAL_LIBS) $(ALL_LIBS)

testdir: testdir.lo $(LOCAL_LIBS)
	$(LINK) testdir.lo $(LOCAL_LIBS) $(ALL_LIBS)

testnames: testnames.lo $(LOCAL_LIBS)
	$(LINK) testnames.lo $(LOCAL_LIBS) $(ALL_LIBS)

testflock: testflock.lo $(LOCAL_LIBS)
	$(LINK) testflock.lo $(LOCAL_LIBS) $(ALL_LIBS)

testdso: testdso.lo mod_test.la libmod_test.la $(LOCAL_LIBS)
	$(LINK) testdso.lo $(LOCAL_LIBS) $(ALL_LIBS)

testoc: testoc.lo occhild $(LOCAL_LIBS)
	$(LINK) testoc.lo $(LOCAL_LIBS) $(ALL_LIBS)

occhild: occhild.lo $(LOCAL_LIBS)
	$(LINK) occhild.lo $(LOCAL_LIBS) $(ALL_LIBS)

# FIXME: -prefer-pic is only supported with libtool-1.4+
mod_test.slo: mod_test.c
	$(LIBTOOL) --mode=compile $(COMPILE) -prefer-pic -c $< && touch $@

mod_test.la: mod_test.slo $(LOCAL_LIBS)
	$(LINK) --mode=link $(COMPILE) -rpath $(shell pwd) -avoid-version -module mod_test.lo $(LT_LDFLAGS) $(ALL_LDFLAGS) -o $@

libmod_test.la: mod_test.slo $(LOCAL_LIBS)
	$(LINK) --mode=link $(COMPILE) -rpath $(shell pwd) -avoid-version mod_test.lo $(LT_LDFLAGS) $(ALL_LDFLAGS) -o $@

testargs: testargs.lo $(LOCAL_LIBS)
	$(LINK) testargs.lo $(LOCAL_LIBS) $(ALL_LIBS)

testproc: testproc.lo $(LOCAL_LIBS)
	$(LINK) testproc.lo $(LOCAL_LIBS) $(ALL_LIBS)

testthread: testthread.lo $(LOCAL_LIBS)
	$(LINK) testthread.lo $(LOCAL_LIBS) $(ALL_LIBS)

testlock: testlock.lo $(LOCAL_LIBS)
	$(LINK) testlock.lo $(LOCAL_LIBS) $(ALL_LIBS)

testlockperf: testlockperf.lo $(LOCAL_LIBS)
	$(LINK) testlockperf.lo $(LOCAL_LIBS) $(ALL_LIBS)

testsock: testsock.lo client server sendfile $(LOCAL_LIBS)
	$(LINK) testsock.lo $(LOCAL_LIBS) $(ALL_LIBS)

client: client.lo $(LOCAL_LIBS)
	$(LINK) client.lo $(LOCAL_LIBS) $(ALL_LIBS)

server: server.lo $(LOCAL_LIBS)
	$(LINK) server.lo $(LOCAL_LIBS) $(ALL_LIBS)

sendfile: sendfile.lo $(LOCAL_LIBS)
	$(LINK) sendfile.lo $(LOCAL_LIBS) $(ALL_LIBS)

testshm: testshm.lo $(LOCAL_LIBS) testshmproducer testshmconsumer
	$(LINK) testshm.lo $(LOCAL_LIBS) $(ALL_LIBS)

testshmproducer: testshmproducer.lo $(LOCAL_LIBS)
	$(LINK) testshmproducer.lo $(LOCAL_LIBS) $(ALL_LIBS)

testshmconsumer: testshmconsumer.lo $(LOCAL_LIBS)
	$(LINK) testshmconsumer.lo $(LOCAL_LIBS) $(ALL_LIBS)

testpipe: testpipe.lo $(LOCAL_LIBS)
	$(LINK) testpipe.lo $(LOCAL_LIBS) $(ALL_LIBS)

testsockopt: testsockopt.lo $(LOCAL_LIBS)
	$(LINK) testsockopt.lo $(LOCAL_LIBS) $(ALL_LIBS)

testpoll: testpoll.lo $(LOCAL_LIBS)
	$(LINK) testpoll.lo $(LOCAL_LIBS) $(ALL_LIBS)

testhash: testhash.lo $(LOCAL_LIBS)
	$(LINK) testhash.lo $(LOCAL_LIBS) $(ALL_LIBS)

testsockets: testsockets.lo $(LOCAL_LIBS)
	$(LINK) testsockets.lo $(LOCAL_LIBS) $(ALL_LIBS)

testuser: testuser.lo $(LOCAL_LIBS)
	$(LINK) testuser.lo $(LOCAL_LIBS) $(ALL_LIBS)

testprocmutex: testprocmutex.lo $(LOCAL_LIBS)
	$(LINK) testprocmutex.lo $(LOCAL_LIBS) $(ALL_LIBS)

testglobalmutex: testglobalmutex.lo $(LOCAL_LIBS)
	$(LINK) testglobalmutex.lo $(LOCAL_LIBS) $(ALL_LIBS)

testatomic: testatomic.lo $(LOCAL_LIBS)
	$(LINK) testatomic.lo $(LOCAL_LIBS) $(ALL_LIBS)

testdup: testdup.lo $(LOCAL_LIBS)
	$(LINK) testdup.lo $(LOCAL_LIBS) $(ALL_LIBS)

testrand: testrand.lo $(LOCAL_LIBS)
	$(LINK) testrand.lo $(LOCAL_LIBS) $(ALL_LIBS)

testmutexscope: testmutexscope.lo $(LOCAL_LIBS)
	$(LINK) testmutexscope.lo $(LOCAL_LIBS) $(ALL_LIBS)

testall: testall.lo testtime.lo teststr.lo testvsn.lo testipsub.lo testmmap.lo testud.lo testtable.lo testsleep.lo testpools.lo testfmt.lo CuTest.lo $(LOCAL_LIBS)
	$(LINK) testall.lo testtime.lo teststr.lo testvsn.lo testipsub.lo testmmap.lo testud.lo testtable.lo testsleep.lo testpools.lo testfmt.lo CuTest.lo $(LOCAL_LIBS) $(ALL_LIBS)


# DO NOT REMOVE
