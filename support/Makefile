# For gcc
CC= gcc
# For ANSI compilers
#CC= cc

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g
# For SCO ODT
#EXTRA_LIBS= -lcrypt_i

RM= /bin/rm -f
#--- You shouldn't have to edit anything else. ---

.c.o: 
	$(CC) -c $(CFLAGS) $<

all: htpasswd unescape inc2shtml

aux: $(OBJS)
	make all CC=gcc CFLAGS=-O2

ibm: $(OBJS)
	make all CC=gcc

sunos: $(OBJS)
	make all CC=gcc

solaris: $(OBJS)
	make all CC=gcc
hp-gcc: $(OBJS)
	make all CC=gcc

hp-cc:
	make all CC=cc CFLAGS=-Ae

sgi: $(OBJS)
	make all CC=cc

decmips: $(OBJS)
	make all CC=cc

decaxp: $(OBJS)
	make all CC=cc

netbsd: $(OBJS)
	make all CC=cc EXTRA_LIBS=-lcrypt

linux: $(OBJS)
	make all CC=gcc

svr4: $(OBJS)
	make all CC=cc

tar: htpasswd unescape
	$(RM) htpasswd unescape

htpasswd: htpasswd.c
	$(CC) $(CFLAGS) htpasswd.c -o htpasswd $(EXTRA_LIBS)

unescape: unescape.c
	$(CC) $(CFLAGS) unescape.c -o unescape

inc2shtml: inc2shtml.c
	$(CC) $(CFLAGS) inc2shtml.c -o inc2shtml
	
clean:
	rm -f htpasswd unescape inc2shtml

