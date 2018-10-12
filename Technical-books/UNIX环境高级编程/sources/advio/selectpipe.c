#include	<sys/types.h>
#include	<sys/time.h>
#include	"ourhdr.h"

int
main(void)
{
	int				i, n, fd[2];
	fd_set			writeset;
	struct timeval	tv;

	if (pipe(fd) < 0)
		err_sys("pipe error");
	FD_ZERO(&writeset);

	for (n = 0; ; n++) { /* write 1 byte at a time until pipe is full */
		FD_SET(fd[1], &writeset);
		tv.tv_sec = tv.tv_usec = 0;		/* don't wait at all */
		if ( (i = select(fd[1]+1, NULL, &writeset, NULL, &tv)) < 0)
			err_sys("select error");
		else if (i == 0)
			break;
		if (write(fd[1], "a", 1) != 1)
			err_sys("write error");
	}
	printf("pipe capacity = %d\n", n);
	exit(0);
}
