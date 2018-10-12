#include	"lprps.h"

char	*loginname;
char	*hostname;
char	*acct_file;
char	eofc = '\004';			/* Control-D = PostScript EOF */

int		psfd = STDOUT_FILENO;
int		start_page = -1;
int		end_page = -1;
int		debug;
int		in_job;

volatile sig_atomic_t	intr_flag;
volatile sig_atomic_t	alrm_flag;

enum status		status = INVALID;
