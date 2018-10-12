include ../Make.defines

PROGS =	calld
OBJS = childdial.o cliargs.o client.o ctlstr.o debug.o devfile.o dialfile.o \
	   expectstr.o lock.o loop.o main.o request.o \
	   sendstr.o sigchld.o sysfile.o ttydial.o ttyopen.o

all:	${PROGS}

${OBJS}:calld.h

sigchld.o:
		${NOANSICOMPILE.c} sigchld.c

calld:	${OBJS}
		${LINK.c} -o $@ ${OBJS} ${LDLIBS}

clean:
		rm -f ${PROGS} ${TEMPFILES}
