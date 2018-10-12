#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include	"ourhdr.h"

/* Create a server endpoint of a connection. */

int			/* returns fd if all OK, <0 on error */
serv_listen(const char *name)
{
	int					fd, len;
	struct sockaddr_un	unix_addr;

					/* create a Unix domain stream socket */
	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return(-1);

	unlink(name);	/* in case it already exists */

					/* fill in socket address structure */
	memset(&unix_addr, 0, sizeof(unix_addr));
	unix_addr.sun_family = AF_UNIX;
	strcpy(unix_addr.sun_path, name);
#ifdef	SCM_RIGHTS	/* 4.3BSD Reno and later */
	len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) +
		  strlen(unix_addr.sun_path) + 1;
	unix_addr.sun_len = len;
#else				/* vanilla 4.3BSD */
	len = strlen(unix_addr.sun_path) + sizeof(unix_addr.sun_family);
#endif
					/* bind the name to the descriptor */
	if (bind(fd, (struct sockaddr *) &unix_addr, len) < 0)
		return(-2);

	if (listen(fd, 5) < 0)	/* tell kernel we're a server */
		return(-3);

	return(fd);
}
