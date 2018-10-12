include ../Make.defines

PROGS =	getpw44bsd getpwnam.o prtime \
		tgetpwnam tstrftime uname

all:	${PROGS}

# We want to link with our own version of getpwnam().
tgetpwnam: getpwnam.o tgetpwnam.o
		   ${LINK.c} -o $@ tgetpwnam.o getpwnam.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEMPFILES}
