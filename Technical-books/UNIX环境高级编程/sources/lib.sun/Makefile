include ../Make.defines

#
# Makefile for misc library.
#

AR	= ar
LIBMISC	= ../libmisc.a
COMM_OBJ   = atexit.o bufargs.o exit.o cliconn.o clrfl.o \
			 daemoninit.o error.o errorlog.o lockreg.o locktest.o \
			 openmax.o pathalloc.o popen.o prmask.o \
			 ptyfork.o ptyopen.o readn.o recvfd.o \
			 senderr.o sendfd.o servaccept.o servlisten.o \
			 setfl.o signal.o signalintr.o \
			 sleep.o sleepus.o spipe.o strerror.o \
			 tellwait.o ttymodes.o writen.o
NOANSI_OBJ = prexit.o	# Sun's <sys/wait.h> ain't ANSI C
BSD_OBJ	   =
S5_OBJ	   = semaph.o
XENIX_OBJ  =
RANLIB     = ranlib

all:
	make `systype.sh`

${COMM_OBJ}:
${BSD_OBJ}:
${S5_OBJ}:
${XENIX_OBJ}:

lib:	${OBJS}
	${AR} rv ${LIBMISC} $?
	${RANLIB} ${LIBMISC}

bsd:
	make "CFLAGS = -O" \
		"OBJS = $(COMM_OBJ) $(BSD_OBJ)" "RANLIB = ranlib" lib

sun:
	make "CFLAGS = $(CFLAGS) -O" \
		"OBJS = $(COMM_OBJ) $(BSD_OBJ) $(S5_OBJ)" "RANLIB = ranlib" lib
	make "CFLAGS = $(NOANSICFLAGS) -O" \
		"OBJS = $(NOANSI_OBJ)" "RANLIB = ranlib" lib

sys5:
	make "CFLAGS = -O -g -I/usr/netinclude" \
		"OBJS = $(COMM_OBJ) $(S5_OBJ)" "RANLIB = ls -l" lib

xenix:
	make "CFLAGS = -O -Ml -I/usr/include/exos" \
		"OBJS = $(COMM_OBJ) $(XENIX_OBJ)" "RANLIB = ls -l" lib

clean:
	rm -f *.o a.out core temp.* $(LIBMISC)
