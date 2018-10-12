#include	<sys/types.h>
#include	<sys/time.h>
#include	<errno.h>
#include	<signal.h>
#include	<syslog.h>		/* since we're a daemon */
#include	"ourhdr.h"

#define	EXIT_SUCCESS	0	/* defined by BSD spooling system */
#define	EXIT_REPRINT	1
#define	EXIT_THROW_AWAY	2

#define	DEF_DEVICE	"/dev/ttyb"	/* defaults for debug mode */
#define	DEF_BAUD	B19200

							/* modify following as appropriate */
#define	MAILCMD		"mail -s \"printer job\" %s@%s < %s"

#define	OBSIZE	1024	/* output buffer */
#define	IBSIZE	1024	/* input buffer */
#define	MBSIZE	1024	/* message buffer */

				/* declare global variables */
extern char	*loginname;
extern char	*hostname;
extern char	*acct_file;
extern char	 eofc;		/* PS end-of-file (004) */
extern int	 debug;		/* true if interactive (not a daemon) */
extern int	 in_job;	/* true if sending user's PS job to printer */
extern int	 psfd;		/* file descriptor for PostScript printer */
extern int	 start_page;/* starting page# */
extern int	 end_page;	/* ending page# */
extern volatile sig_atomic_t	intr_flag; /* set if SIGINT is caught */
extern volatile sig_atomic_t	alrm_flag; /* set if SIGALRM goes off */

extern enum status {	/* printer status */
	INVALID, UNKNOWN, IDLE, BUSY, WAITING
} status;

				/* global function prototypes */
void	do_acct(void);				/* acct.c */

void	clear_alrm(void);			/* alarm.c */
void	handle_alrm(void);
void	set_alrm(unsigned int);

void	get_status(void);			/* getstatus.c */

void	init_input(int);			/* input.c */
void	proc_input_char(int);
void	proc_some_input(void);
void	proc_upto_eof(int);

void	clear_intr(void);			/* interrupt.c */
void	handle_intr(void);
void	set_intr(void);

void	close_mailfp(void);			/* mail.c */
void	mail_char(int);
void	mail_line(const char *, const char *);

void	msg_init(void);				/* message.c */
void	msg_char(int);
void	proc_msg(void);

void	out_char(int);				/* output.c */

void	get_page(int *);			/* pagecount.c */

void	send_file(void);			/* sendfile.c */

void	block_write(const char *, int);	/* tty.c */
void	tty_flush(void);
void	set_block(void);
void	set_nonblock(void);
void	tty_open(void);
