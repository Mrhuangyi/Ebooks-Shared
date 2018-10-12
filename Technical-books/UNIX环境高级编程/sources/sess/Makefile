include ../Make.defines

PROGS =	orphan recycle test1 tdaemon1 tdaemon2 tsetsid tsusp tsusp1

all:	${PROGS}

orphan:	orphan.o
		$(LINK.c) -o $@ orphan.o $(LDLIBS) $(S5LIB)

clean:
	rm -f ${PROGS} ${TEMPFILES}
