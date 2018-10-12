#include	<sys/times.h>
#include	"ourhdr.h"

static void	pr_times(clock_t, struct tms *, struct tms *);
static void	do_cmd(char *);

int
main(int argc, char *argv[])
{
	int		i;

	for (i = 1; i < argc; i++)
		do_cmd(argv[i]);	/* once for each command-line arg */
	exit(0);
}
static void
do_cmd(char *cmd)		/* execute and time the "cmd" */
{
	struct tms	tmsstart, tmsend;
	clock_t		start, end;
	int			status;

	fprintf(stderr, "\ncommand: %s\n", cmd);

	if ( (start = times(&tmsstart)) == -1)	/* starting values */
		err_sys("times error");

	if ( (status = system(cmd)) < 0)		/* execute command */
		err_sys("system() error");

	if ( (end = times(&tmsend)) == -1)		/* ending values */
		err_sys("times error");

	pr_times(end-start, &tmsstart, &tmsend);
	pr_exit(status);
}
static void
pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
	static long		clktck = 0;

	if (clktck == 0)	/* fetch clock ticks per second first time */
		if ( (clktck = sysconf(_SC_CLK_TCK)) < 0)
			err_sys("sysconf error");
	fprintf(stderr, "  real:  %7.2f\n", real / (double) clktck);
	fprintf(stderr, "  user:  %7.2f\n",
			(tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
	fprintf(stderr, "  sys:   %7.2f\n",
			(tmsend->tms_stime - tmsstart->tms_stime) / (double) clktck);
	fprintf(stderr, "  child user:  %7.2f\n",
			(tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
	fprintf(stderr, "  child sys:   %7.2f\n",
			(tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}
