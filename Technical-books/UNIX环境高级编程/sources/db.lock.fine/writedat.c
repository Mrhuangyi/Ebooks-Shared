#include	"db.h"
#include	<sys/uio.h>		/* struct iovec */

/* Write a data record.  Called by _db_dodelete() (to write
   the record with blanks) and db_store(). */

void
_db_writedat(DB *db, const char *data, off_t offset, int whence)
{
	struct iovec	iov[2];
	static char		newline = '\n';

		/* If we're appending, we have to lock before doing the lseek()
		   and write() to make the two an atomic operation.  If we're
		   overwriting an existing record, we don't have to lock. */
	if (whence == SEEK_END)		/* we're appending, lock entire file */
		if (writew_lock(db->datfd, 0, SEEK_SET, 0) < 0)
			err_dump("writew_lock error");

	if ( (db->datoff = lseek(db->datfd, offset, whence)) == -1)
		err_dump("lseek error");
	db->datlen = strlen(data) + 1;	/* datlen includes newline */

	iov[0].iov_base = (char *) data;
	iov[0].iov_len  = db->datlen - 1;
	iov[1].iov_base = &newline;
	iov[1].iov_len  = 1;
	if (writev(db->datfd, &iov[0], 2) != db->datlen)
		err_dump("writev error of data record");

	if (whence == SEEK_END)
		if (un_lock(db->datfd, 0, SEEK_SET, 0) < 0)
			err_dump("un_lock error");
}
