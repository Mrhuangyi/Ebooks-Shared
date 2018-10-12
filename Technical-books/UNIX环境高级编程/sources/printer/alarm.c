#include	"lprps.h"

static void
sig_alrm(int signo)			/* SIGALRM handler */
{
	alrm_flag = 1;
	return;
}

void
handle_alrm(void)
{
	log_ret("printer not responding");
	sleep(60);		/* it will take at least this long to warm up */

	exit(EXIT_REPRINT);
}

void		/* Establish the signal handler and set the alarm. */
set_alrm(unsigned int nsec)
{
	alrm_flag = 0;
	if (signal_intr(SIGALRM, sig_alrm) == SIG_ERR)
		log_sys("set_alrm: signal_intr error");
	alarm(nsec);
}

void
clear_alrm(void)
{
	alarm(0);
	if (signal(SIGALRM, SIG_IGN) == SIG_ERR)
		log_sys("clear_alrm: signal error");
	alrm_flag = 0;
}
