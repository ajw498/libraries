#!/bin/sh
#
# 1) remove everything after the DO NOT REMOVE
# 2) generate the dependencies, adding them to the end of Makefile.new
# 3) move the Makefile.new back into place
#
# Note that we use && to ensure that Makefile is not changed if an error
# occurs during the process
#
if test -z "$CC"; then
   CC=cc
fi

sed -ne '1,/^# DO NOT REMOVE/p' Makefile > Makefile.new \
    && $CC -MM  $* | sed -e "s/\.o:/\.lo:/" >> Makefile.new \
    && mv Makefile.new Makefile
