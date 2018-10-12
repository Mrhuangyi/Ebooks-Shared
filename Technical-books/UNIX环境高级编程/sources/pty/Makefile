include ../Make.defines

PROGS =	add2 add2stdio cop copt2500 \
		pipe4 pipe5 pipeawk pty ptysig ptysigchild slowout

all:	${PROGS}

pty:	main.o loop.o driver.o
		${LINK.c} -o pty main.o loop.o driver.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEMPFILES}
