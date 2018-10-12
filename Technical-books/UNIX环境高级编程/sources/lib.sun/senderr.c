#include	"ourhdr.h"

/* Used when we had planned to send an fd using send_fd(),
 * but encountered an error instead.  We send the error back
 * using the send_fd()/recv_fd() protocol. */

int
send_err(int clifd, int errcode, const char *msg)
{
	int		n;

	if ( (n = strlen(msg)) > 0)
		if (writen(clifd, msg, n) != n)	/* send the error message */
			return(-1);

	if (errcode >= 0)
		errcode = -1;	/* must be negative */

	if (send_fd(clifd, errcode) < 0)
		return(-1);

	return(0);
}
