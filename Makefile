
all: stamp-zlib stamp-png stamp-jpeg stamp-gd stamp-oslib stamp-openssl stamp-expat stamp-neon stamp-apr stamp-aprutil stamp-xml stamp-xslt stamp-gettext stamp-sablot stamp-sshlib

stamp-zlib:
	./build-zlib $(PREFIX)
	touch stamp-zlib

stamp-png: stamp-zlib
	./build-png $(PREFIX)
	touch stamp-png

stamp-jpeg:
	./build-jpeg $(PREFIX)
	touch stamp-jpeg

stamp-gd: stamp-jpeg stamp-png
	./build-gd $(PREFIX)
	touch stamp-gd

stamp-oslib:
	./build-oslib $(PREFIX)
	touch stamp-oslib

stamp-openssl:
	./build-openssl $(PREFIX)
	touch stamp-openssl

stamp-expat:
	./build-expat $(PREFIX)
	touch stamp-expat

stamp-neon: stamp-expat stamp-openssl
	./build-neon $(PREFIX)
	touch stamp-neon

stamp-apr: stamp-expat
	./build-apr $(PREFIX)
	touch stamp-apr

stamp-aprutil: stamp-apr
	./build-aprutil $(PREFIX)
	touch stamp-aprutil

stamp-xml:
	./build-xml $(PREFIX)
	touch stamp-xml

stamp-xslt: stamp-xml
	./build-xslt $(PREFIX)
	touch stamp-xslt

stamp-gettext:
	./build-gettext $(PREFIX)
	touch stamp-gettext

stamp-sablot: stamp-xml
	./build-sablot $(PREFIX)
	touch stamp-sablot

stamp-sshlib:
	./build-sshlib $(PREFIX)
	touch stamp-sshlib


clean:
	rm -f stamp-*
