/* Sun doesn't provide atexit() yet.
 * We need this version of exit() to go with our atexit(). */

#include	<stdio.h>		/* _cleanup() */
#include	<unistd.h>		/* _exit() */
#include	"atexit.h"
#include	"ourhdr.h"

void
exit(int status)
{
	struct atexit	*p;
	int				i;

	if ( (p = __atexit) != 0) {	/* we have some functions to call */
		if ( (i = p->ind) <= 0)
			err_dump("p->ind = %d", p->ind);
		while (--i >= 0)
			(*p->fns[i])();	/* call in reverse order */
	}

	_cleanup();			/* standard I/O cleanup */
	_exit(status);		/* the real thing */
}
