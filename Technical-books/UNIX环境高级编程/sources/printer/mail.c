#include	"lprps.h"

static FILE	*mailfp;
static char	temp_file[L_tmpnam];
static void	open_mailfp(void);

/* Called by proc_input_char() when it encounters characters
 * that are not message characters.  We have to send these
 * characters back to the user. */

void
mail_char(int c)
{
	static int	done_intro = 0;

	if (in_job && (done_intro || c != '\n')) {
		open_mailfp();
		if (done_intro == 0) {
			fputs("Your PostScript printer job "
				  "produced the following output:\n", mailfp);
			done_intro = 1;
		}
		putc(c, mailfp);
	}
}

/* Called by proc_msg() when an "Error" or "OffendingCommand" key
 * is returned by the PostScript interpreter.  Send the key and
 * val to the user. */

void
mail_line(const char *msg, const char *val)
{
	if (in_job) {
    	open_mailfp();
  		fprintf(mailfp, msg, val);
	}
}

/* Create and open a temporary mail file, if not already open.
 * Called by mail_char() and mail_line() above. */

static void
open_mailfp(void)
{
	if (mailfp == NULL) {
		if ( (mailfp = fopen(tmpnam(temp_file), "w")) == NULL)
			log_sys("open_mailfp: fopen error");
	}
}

/* Close the temporary mail file and send it to the user.
 * Registered to be called on exit() by atexit() in main(). */

void
close_mailfp(void)
{
	char	command[1024];

	if (mailfp != NULL) {
		if (fclose(mailfp) == EOF)
			log_sys("close_mailfp: fclose error");
		sprintf(command, MAILCMD, loginname, hostname, temp_file);
		system(command);
		unlink(temp_file);
	}
}
