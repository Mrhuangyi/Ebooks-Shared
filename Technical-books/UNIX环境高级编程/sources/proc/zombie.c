#include	"ourhdr.h"

int
main(void)
{
	pid_t	pid;

	if ( (pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)		/* child */
		exit(0);

	/* parent */
	sleep(4);

	system("ps");

	exit(0);
}
