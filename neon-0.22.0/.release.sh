#!/bin/sh

set -ex

major=`echo $1 | sed "s/\..*//g"`
minor=`echo $1 | sed "s/^[0-9]*\.\(.*\)\.[0-9]*$/\1/g"`
rel=`echo $1 | sed "s/^.*\./\1/g"`
version=$1

for f in config.hw; do
in=$f.in
out=$f
sed -e "s/@VERSION@/$version/g" \
    -e "s/@MAJOR@/$major/g" \
    -e "s/@MINOR@/$minor/g" \
    -e "s/@RELEASE@/$release/g" < $in > $out
done

echo $1 > .version

# for the documentation:
date +"%e %B %Y" | tr -d '\n' > doc/date.xml
echo -n $1 > doc/version.xml

# Try to create a valid Makefile
tmp=`mktemp /tmp/neon-XXXXXX`
sed -e "s/@SET_MAKE@//g" -e "s|@SHELL@|/bin/sh|g" < Makefile.in > $tmp
make -f $tmp docs
rm -f $tmp
