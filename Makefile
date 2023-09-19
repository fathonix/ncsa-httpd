
all:
	@echo Please choose a system type.
	@echo Valid types are ibm, sunos, sgi, decmips, decaxp, hp-cc,
	@echo hp-gcc, solaris, netbsd, svr4, linux, aux
	@echo If you do not have one of these systems, you must edit
	@echo src/Makefile, cgi-src/Makefile, and support/Makefile

clean:
	(cd src ; make clean)
	(cd cgi-src ; make clean)
	(cd support ; make clean)

tar-clean: clean
	rm -f httpd

aux:
	cd src ; make aux ; cd ../cgi-src ; make aux ; cd ../support ; make aux

ibm:
	cd src ; make ibm ; cd ../cgi-src ; make ibm ; cd ../support ; make ibm

sunos:
	cd src ; make sunos ; cd ../cgi-src ; make sunos ; cd ../support ; make sunos

solaris:
	cd src ; make solaris ; cd ../cgi-src ; make solaris ; cd ../support ; make solaris 

sgi:
	cd src ; make sgi ; cd ../cgi-src ; make sgi ; cd ../support ; make sgi

decmips:
	cd src ; make decmips ; cd ../cgi-src ; make decmips ; cd ../support ; make decmips

decaxp:
	cd src ; make decaxp ; cd ../cgi-src ; make decaxp ; cd ../support ; make decaxp

hp-gcc:
	cd src ; make hp-gcc ; cd ../cgi-src ; make hp-gcc ; cd ../support ; make hp-gcc

hp-cc:
	cd src ; make hp-cc ; cd ../cgi-src ; make hp-cc ; cd ../support ; make hp-cc

netbsd:
	cd src ; make netbsd ; cd ../cgi-src ; make netbsd ; cd ../support ; make netbsd

linux:
	cd src ; make linux ; cd ../cgi-src ; make linux ; cd ../support ; make linux

svr4:
	cd src ; make svr4 ; cd ../cgi-src ; make svr4 ; cd ../support ; make svr4
