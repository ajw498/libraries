#!/bin/sh
# Helper script to create CA and server certificates.

srcdir=${1-.}

OPENSSL=${OPENSSL-openssl}
CONF=${srcdir}/openssl.conf
REQ="${OPENSSL} req -config ${CONF}"
CA="${OPENSSL} ca -config ${CONF} -batch"
REQDN=reqDN
export REQDN

set -ex

mkdir ca
touch ca/index.txt
echo 01 > ca/serial

${OPENSSL} genrsa -rand ${srcdir}/../configure > ca/key.pem
${OPENSSL} genrsa -rand ${srcdir}/../configure > client.key

${REQ} -x509 -new -key ca/key.pem -out ca/cert.pem <<EOF
US
California
Oakland
Neosign
Random Dept
nowhere.example.com
neon@webdav.org
EOF

# Function to generate appropriate output for `openssl req'.
csr_fields() {
OU=${1-"Neon QA Dept"}
CN=${2-"localhost"}
cat <<EOF
GB
Cambridgeshire
Cambridge
Neon Hackers Ltd
${OU}
${CN}
neon@webdav.org
.
.
EOF
}

csr_fields | ${REQ} -new -key ${srcdir}/server.key -out server.csr

csr_fields "Upper Case Dept" lOcALhost | \
${REQ} -new -key ${srcdir}/server.key -out caseless.csr

csr_fields "Use AltName Dept" nowhere.example.com | \
${REQ} -new -key ${srcdir}/server.key -out altname.csr

csr_fields "Two AltName Dept" nowhere.example.com | \
${REQ} -new -key ${srcdir}/server.key -out altname2.csr

csr_fields "Third AltName Dept" nowhere.example.com | \
${REQ} -new -key ${srcdir}/server.key -out altname3.csr

csr_fields "Fourth AltName Dept" localhost | \
${REQ} -new -key ${srcdir}/server.key -out altname4.csr

csr_fields "Self-Signed" | \
${REQ} -new -x509 -key ${srcdir}/server.key -out ssigned.pem

csr_fields "Bad Hostname Department" nohost.example.com | \
${REQ} -new -x509 -key ${srcdir}/server.key -out wrongcn.pem

# Only works with a Linuxy hostname command: continue without it,
# as appropriate tests are skipped if these fail.
hostname=`hostname -s 2>/dev/null` || true
domain=`hostname -d 2>/dev/null` || true
fqdn=`hostname -f 2>/dev/null` || true
if [ "x${hostname}.${domain}" = "x${fqdn}" ]; then
  csr_fields "Wildcard Cert Dept" "*.${domain}" | \
  ${REQ} -new -key ${srcdir}/server.key -out wildcard.csr
  ${CA} -days 900 -in wildcard.csr -out wildcard.cert
fi

csr_fields "Neon Client Cert" ignored.example.com | \
${REQ} -new -key client.key -out client.csr

### requests using special DN.

REQDN=reqDN.doubleCN
csr_fields "Double CN Dept" "nohost.example.com
localhost" | ${REQ} -new -key ${srcdir}/server.key -out twocn.csr

REQDN=reqDN.CNfirst
echo localhost | ${REQ} -new -key ${srcdir}/server.key -out cnfirst.csr

### don't put ${REQ} invocations after here

for f in server client twocn caseless cnfirst; do
  ${CA} -days 900 -in ${f}.csr -out ${f}.cert
done

${CA} -extensions altExt -days 900 -in altname.csr -out altname.cert
${CA} -extensions altExt2 -days 900 -in altname2.csr -out altname2.cert
${CA} -extensions altExt3 -days 900 -in altname3.csr -out altname3.cert
${CA} -extensions altExt4 -days 900 -in altname4.csr -out altname4.cert

# generate a PKCS12 cert from the client cert: -passOUT because it's the
# passphrase on the OUTPUT cert, confusing...
echo foobar | ${OPENSSL} pkcs12 -export -passout stdin -name "Neon Client Cert" \
   -in client.cert -inkey client.key -out client.p12
