include ../Make.defines

PROGS =	lprps
OBJS  = acct.o alarm.o getstatus.o input.o interrupt.o \
		mail.o main.o message.o output.o \
		pagecount.o sendfile.o tty.o vars.o
DIR = /usr/local/lib

all:	${PROGS}

lprps:	${OBJS}
		${LINK.c} -o $@ ${OBJS} ${LDLIBS}

psif:	psif.o
		${LINK.c} -o $@ psif.o ${LDLIBS}

install:lprps
		mv lprps ${DIR}/lprps

clean:
	rm -f ${PROGS} ${TEMPFILES}
