#!/bin/sh
# Helper script to create CA and server certificates.

srcdir=${1-.}

set -ex

mkdir ca
touch ca/index.txt
echo 01 > ca/serial

openssl genrsa -rand ${srcdir}/../configure > ca/key.pem
openssl genrsa -rand ${srcdir}/../configure > client.key

openssl req -x509 -new -key ca/key.pem -out ca/cert.pem <<EOF
US
California
Oakland
Neosign
Random Dept
nowhere.example.com
neon@webdav.org
EOF

openssl req -new -key ${srcdir}/server.key -out server.csr <<EOF
GB
Cambridgeshire
Cambridge
Neon Hackers Ltd
Neon QA Dept
localhost
neon@webdav.org
.
.
EOF

openssl req -new -x509 -key ${srcdir}/server.key -out ssigned.pem <<EOF
GB
Cambridgeshire
Cambridge
Neon Hackers Ltd
Neon Self-Signed Dept
localhost
neon@webdav.org
.
.
EOF

openssl req -new -x509 -key ${srcdir}/server.key -out wrongcn.pem <<EOF
GB
Cambridgeshire
Cambridge
Neon Hackers Ltd
Neon QA Dept
hohost.example.com
neon@webdav.org
.
.
EOF

# Only works with a Linuxy hostname command: continue without it,
# as appropriate tests are skipped if these fail.
hostname=`hostname -s 2>/dev/null` || true
domain=`hostname -d 2>/dev/null` || true
fqdn=`hostname -f 2>/dev/null` || true
if [ "x${hostname}.${domain}" = "x${fqdn}" ]; then
  openssl req -new -key ${srcdir}/server.key -out wildcard.csr <<EOF
GB
Cambridgeshire
Cambridge
Neon Hackers Ltd
Neon Wildcard Cert
*.${domain}
neon@webdav.org
.
.
EOF
  openssl ca -config ${srcdir}/openssl.conf -batch -days 900 -in wildcard.csr \
      -out wildcard.cert
fi

openssl req -new -key client.key -out client.csr <<EOF
GB
Cambridgeshire
Cambridge
Neon Hackers Ltd
Neon Client Cert
ignored.example.com
neon@webdav.org
.
.
EOF

openssl ca -config ${srcdir}/openssl.conf -batch -days 900 -in server.csr \
    -out server.cert

openssl ca -config ${srcdir}/openssl.conf -batch -days 900 -in client.csr \
    -out client.cert

# generate a PKCS12 cert from the client cert: -passOUT because it's the
# passphrase on the OUTPUT cert, confusing...
echo foobar | openssl pkcs12 -export -passout stdin -name "Neon Client Cert" \
   -in client.cert -inkey client.key -out client.p12
