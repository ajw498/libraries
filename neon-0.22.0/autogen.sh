#!/bin/sh
rm -f ltconfig ltmain.sh config.cache aclocal.m4
# create a .version file for configure.in
test -f .version || echo 0.0.0-dev > .version
set -e
echo -n "aclocal... "
${ACLOCAL:-aclocal} -I macros
echo -n "autoheader... "
${AUTOHEADER:-autoheader}
echo -n "libtoolize... "
${LIBTOOLIZE:-libtoolize} --copy --force >/dev/null
echo -n "autoconf... "
${AUTOCONF:-autoconf} -Wall
echo okay.
# remove the autoconf cache
rm -rf autom4te*.cache
