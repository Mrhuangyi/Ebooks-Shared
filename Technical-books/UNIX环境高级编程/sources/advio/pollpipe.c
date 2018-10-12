#include	<sys/types.h>
#include	<poll.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<stropts.h>
#include	<unistd.h>
#include	"ourhdr.h"

int
main(void)
{
	int				i, n, fd[2];
	struct pollfd	fdarr[1];

	if (pipe(fd) < 0)
		err_sys("pipe error");

	for (n = 0; ; n++) {
		fdarr[0].fd = fd[1];
		fdarr[0].events = POLLOUT;
		if ( (i = poll(fdarr, 1, 0)) < 0)
			err_sys("poll error");
		else if (i == 0)
			break;
		if (write(fd[1], "a", 1) != 1)
			err_sys("write error");
	}
	printf("pipe capacity = %d\n", n);
	exit(0);
}
