#include	<sys/types.h>
#include	<sys/stat.h>
#include	<errno.h>
#include	<fcntl.h>
#include	<grp.h>
#include	"ourhdr.h"

int
ptym_open(char *pts_name)
{
	int		fdm;
	char	*ptr1, *ptr2;

	strcpy(pts_name, "/dev/ptyXY");
	  /* array index: 0123456789 (for references in following code) */
	for (ptr1 = "pqrstuvwxyzPQRST"; *ptr1 != 0; ptr1++) {
		pts_name[8] = *ptr1;
		for (ptr2 = "0123456789abcdef"; *ptr2 != 0; ptr2++) {
			pts_name[9] = *ptr2;

						/* try to open master */
			if ( (fdm = open(pts_name, O_RDWR)) < 0) {
				if (errno == ENOENT)	/* different from EIO */
					return(-1);			/* out of pty devices */
				else
					continue;			/* try next pty device */
			}

			pts_name[5] = 't';	/* change "pty" to "tty" */
			return(fdm);		/* got it, return fd of master */
		}
	}
	return(-1);		/* out of pty devices */
}

int
ptys_open(int fdm, char *pts_name)
{
	struct group	*grptr;
	int				gid, fds;

	if ( (grptr = getgrnam("tty")) != NULL)
		gid = grptr->gr_gid;
	else
		gid = -1;		/* group tty is not in the group file */

			/* following two functions don't work unless we're root */
	chown(pts_name, getuid(), gid);
	chmod(pts_name, S_IRUSR | S_IWUSR | S_IWGRP);

	if ( (fds = open(pts_name, O_RDWR)) < 0) {
		close(fdm);
		return(-1);
	}
	return(fds);
}
