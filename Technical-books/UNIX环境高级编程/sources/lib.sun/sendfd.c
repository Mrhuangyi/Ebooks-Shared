#include	<sys/types.h>
#include	<sys/socket.h>		/* struct msghdr */
#include	<sys/uio.h>			/* struct iovec */
#include	<errno.h>
#include	<stddef.h>
#include	"ourhdr.h"

/* Pass a file descriptor to another process.
 * If fd<0, then -fd is sent back instead as the error status. */

int
send_fd(int clifd, int fd)
{
	struct iovec	iov[1];
	struct msghdr	msg;
	char			buf[2];	/* send_fd()/recv_fd() 2-byte protocol */

	iov[0].iov_base = buf;
	iov[0].iov_len  = 2;
	msg.msg_iov     = iov;
	msg.msg_iovlen  = 1;
	msg.msg_name    = NULL;
	msg.msg_namelen = 0;

	if (fd < 0) {
		msg.msg_accrights    = NULL;
		msg.msg_accrightslen = 0;
		buf[1] = -fd;	/* nonzero status means error */
		if (buf[1] == 0)
			buf[1] = 1;	/* -256, etc. would screw up protocol */
	} else {
		msg.msg_accrights    = (caddr_t) &fd;	/* addr of descriptor */
		msg.msg_accrightslen = sizeof(int);		/* pass 1 descriptor */
		buf[1] = 0;		/* zero status means OK */
	}
	buf[0] = 0;			/* null byte flag to recv_fd() */

	if (sendmsg(clifd, &msg, 0) != 2)
		return(-1);

	return(0);
}
