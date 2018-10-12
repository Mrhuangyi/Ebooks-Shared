#include	"calld.h"
#include	<syslog.h>

			/* define global variables */
int			clifd;
int			debug;	/* daemon's command line flag */
int			Debug;	/* Debug controlled by client, not cmd line */
char		errmsg[MAXLINE];
char		*speed;
char		*sysname;
uid_t		uid;
Client		*client = NULL;
int			client_size;
Systems		systems;
Devices		devices;
Dialers		dialers;
volatile sig_atomic_t chld_flag;
enum parity parity = NONE;

int
main(int argc, char *argv[])
{
	int		c;

	log_open("calld", LOG_PID, LOG_USER);

	opterr = 0;		/* don't want getopt() writing to stderr */
	while ( (c = getopt(argc, argv, "d")) != EOF) {
		switch (c) {
		case 'd':		/* debug */
			debug = 1;
			break;

		case '?':
			log_quit("unrecognized option: -%c", optopt);
		}
	}

	if (debug == 0)
		daemon_init();

	loop();		/* never returns */
}
