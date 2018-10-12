#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/stat.h>
#include	<sys/un.h>
#include	<stddef.h>
#include	<time.h>
#include	"ourhdr.h"

#define	STALE	30	/* client's name can't be older than this (sec) */

/* Wait for a client connection to arrive, and accept it.
 * We also obtain the client's user ID from the pathname
 * that it must bind before calling us. */

int			/* returns new fd if all OK, <0 on error */
serv_accept(int listenfd, uid_t *uidptr)
{
	int					clifd, len;
	time_t				staletime;
	struct sockaddr_un	unix_addr;
	struct stat			statbuf;

	len = sizeof(unix_addr);
	if ( (clifd = accept(listenfd, (struct sockaddr *) &unix_addr, &len)) < 0)
		return(-1);		/* often errno=EINTR, if signal caught */

			/* obtain the client's uid from its calling address */
#ifdef	SCM_RIGHTS	/* 4.3BSD Reno and later */
	len -= sizeof(unix_addr.sun_len) - sizeof(unix_addr.sun_family);
#else				/* vanilla 4.3BSD */
	len -= sizeof(unix_addr.sun_family);	/* len of pathname */
#endif
	unix_addr.sun_path[len] = 0;			/* null terminate */

	if (stat(unix_addr.sun_path, &statbuf) < 0)
		return(-2);
#ifdef	S_ISSOCK	/* not defined for SVR4 */
	if (S_ISSOCK(statbuf.st_mode) == 0)
		return(-3);		/* not a socket */
#endif
	if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) ||
		(statbuf.st_mode & S_IRWXU) != S_IRWXU)
		  return(-4);	/* is not rwx------ */

	staletime = time(NULL) - STALE;
	if (statbuf.st_atime < staletime ||
		statbuf.st_ctime < staletime ||
		statbuf.st_mtime < staletime)
		  return(-5);	/* i-node is too old */

	if (uidptr != NULL)
		*uidptr = statbuf.st_uid;	/* return uid of caller */

	unlink(unix_addr.sun_path);		/* we're done with pathname now */

	return(clifd);
}
