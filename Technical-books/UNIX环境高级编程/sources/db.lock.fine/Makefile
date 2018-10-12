include ../Make.defines

DBLIB = libdb.a
DBLIBOBJS =	alloc.o checkfree.o close.o delete.o dodelete.o \
			fetch.o find.o findfree.o free.o \
			hash.o nextrec.o open.o \
			readdat.o readidx.o readptr.o rewind.o \
			stats.o store.o writedat.o writeidx.o writeptr.o

PROGS =	t1 t3 t4
LDLIBS = ${DBLIB} ${LIB}

all:	${DBLIB} ${PROGS}

lib:	${DBLIB}

${DBLIB}: ${DBLIB}(${DBLIBOBJS})
	ar rv $@ $?
	ranlib $@

# The following way to make a library only appears to work under SunOS.
# Under other systems just do "cc -c -O [a-su-z]*.c" then
# "ar rv libdb.a [a-su-z]*.o".

${DBLIB}(%.o): %.o
	@true

#t2:	t2.o tellwait.o
#		$(LINK.c) -o $@ t2.o tellwait.o $(LDLIBS)

t3:	t3.o
	${LINK.c} -o $@ t3.o ${LDLIBS}

clean:
	rm -f ${DBLIB} ${DBLIBOBJS} ${PROGS} ${TEMPFILES} *.dat *.idx
