include ../Make.defines

PROGS =	call
OBJS = call.o escape.o loop.o main.o put.o take.o takeput.o

all:	${PROGS}

${OBJS}: call.h

call:	${OBJS}
		${LINK.c} -o $@ ${OBJS} ${LDLIBS}

clean:
		rm -f ${PROGS} ${TEMPFILES}
