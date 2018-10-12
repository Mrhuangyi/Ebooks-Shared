include ../Make.defines

PROGS =	isastream.o strlist t_isastream

all:	${PROGS}

t_isastream: t_isastream.o isastream.o
		  ${LINK.c} -o $@ t_isastream.o isastream.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEMPFILES}
