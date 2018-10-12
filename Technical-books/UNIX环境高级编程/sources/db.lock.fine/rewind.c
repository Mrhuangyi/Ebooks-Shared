#include	"db.h"

/* Rewind the index file for db_nextrec().
 * Automatically called by db_open().
 * Must be called before first db_nextrec().
 */

void
db_rewind(DB *db)
{
	off_t	offset;

	offset = (db->nhash + 1) * PTR_SZ;		/* +1 for free list ptr */

		/* We're just setting the file offset for this process
		   to the start of the index records; no need to lock.
		   +1 below for newline at end of hash table. */

	if ( (db->idxoff = lseek(db->idxfd, offset+1, SEEK_SET)) == -1)
		err_dump("lseek error");
}
