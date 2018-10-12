include ../Make.defines

PROGS =	echoall echoarg exec1 exec2 fork1 fork2 \
		pracct pruids \
		shell1 shell2 sleeper system.o \
		systest1 systest2 systest3 \
		tcloexec tellwait1 tellwait2s tellwait3s tellwait2p tellwait3p \
		test1 times1 tuids vfork1 vfork2 vfork3 wait1 zombie

all:	${PROGS}

systest1.o:
		${NOANSICOMPILE.c} systest1.c

# We want to link with our own version of system() for systest[12].
systest1: system.o systest1.o
		  ${LINK.c} -o $@ systest1.o system.o ${LDLIBS}

systest2: system.o systest2.o
		  ${LINK.c} -o $@ systest2.o system.o ${LDLIBS}

# Version using signals.
tellwait2s: ../signals/tellwait.o tellwait2.o
		  ${LINK.c} -o $@ tellwait2.o ../signals/tellwait.o ${LDLIBS}

tellwait3s: ../signals/tellwait.o tellwait3.o
		  ${LINK.c} -o $@ tellwait3.o ../signals/tellwait.o ${LDLIBS}

# Version using stream pipe
tellwait2p: ../pipe/tellwait.o tellwait2.o
		  ${LINK.c} -o $@ tellwait2.o ../pipe/tellwait.o ${LDLIBS}

tellwait3p: ../pipe/tellwait.o tellwait3.o
		  ${LINK.c} -o $@ tellwait3.o ../pipe/tellwait.o ${LDLIBS}

# Under SunOS we need the System V version of times(2)
times1:	times1.o
		$(LINK.c) -o $@ times1.o $(LDLIBS) $(S5LIB)

clean:
	rm -f ${PROGS} ${TEMPFILES}
