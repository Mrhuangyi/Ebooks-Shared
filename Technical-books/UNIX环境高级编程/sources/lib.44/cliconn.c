/* Create a client endpoint and connect to a server. */

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/stat.h>
#include	<sys/un.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	"ourhdr.h"

#define	CLI_PATH	"/var/tmp/"		/* +5 for pid = 14 chars */
#define	CLI_PERM	S_IRWXU			/* rwx for user only */

int			/* returns fd if all OK, -1 on error */
cli_conn(const char *name)
{
	int					fd, len;
	struct sockaddr_un	unix_addr;

				/* create a Unix domain stream socket */
	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		return(-1);

				/* fill socket address structure w/our address */
	memset(&unix_addr, 0, sizeof(unix_addr));
	unix_addr.sun_family = AF_UNIX;
	sprintf(unix_addr.sun_path, "%s%05d", CLI_PATH, getpid());
	len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) +
		  strlen(unix_addr.sun_path) + 1;
	unix_addr.sun_len = len;
#ifdef	notdef
	if (len != 16)
		err_quit("length != 16");	/* hack */
#endif

	unlink(unix_addr.sun_path);		/* in case it already exists */
	if (bind(fd, (struct sockaddr *) &unix_addr, len) < 0)
		return(-1);
	if (chmod(unix_addr.sun_path, CLI_PERM) < 0)
		return(-1);

				/* fill socket address structure w/server's addr */
	memset(&unix_addr, 0, sizeof(unix_addr));
	unix_addr.sun_family = AF_UNIX;
	strcpy(unix_addr.sun_path, name);
	len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) +
		  strlen(unix_addr.sun_path) + 1;
	unix_addr.sun_len = len;

	if (connect(fd, (struct sockaddr *) &unix_addr, len) < 0)
		return(-1);

	return(fd);
}
