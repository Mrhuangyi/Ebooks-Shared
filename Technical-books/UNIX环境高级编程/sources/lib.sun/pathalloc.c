#include	<errno.h>
#include	<limits.h>
#include	"ourhdr.h"

#ifdef	PATH_MAX
static int	pathmax = PATH_MAX;
#else
static int	pathmax = 0;
#endif

#define	PATH_MAX_GUESS	1024	/* if PATH_MAX is indeterminate */
						/* we're not guaranteed this is adequate */
char *
path_alloc(int *size)
				/* also return allocated size, if nonnull */
{
	char	*ptr;

	if (pathmax == 0) {		/* first time through */
		errno = 0;
		if ( (pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
			if (errno == 0)
				pathmax = PATH_MAX_GUESS;	/* it's indeterminate */
			else
				err_sys("pathconf error for _PC_PATH_MAX");
		} else
			pathmax++;		/* add one since it's relative to root */
	}

	if ( (ptr = malloc(pathmax + 1)) == NULL)
		err_sys("malloc error for pathname");

	if (size != NULL)
		*size = pathmax + 1;
	return(ptr);
}
