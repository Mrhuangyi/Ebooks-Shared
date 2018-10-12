include ../Make.defines

PROGS =	areas close daemon deadlock exec1 exec2 \
		mandatory myed open1 open2 readlock \
		texec1 vil writelock

all:	${PROGS}

ttellwait1: ttellwait1.o tellwait.o
		    ${LINK.c} -o $@ ttellwait1.o tellwait.o ${LDLIBS}

ttellwait2: ttellwait2.o tellwait.o
		    ${LINK.c} -o $@ ttellwait2.o tellwait.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEMPFILES} templock
