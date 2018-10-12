#include	"db.h"

/* Store a record in the database.
 * Return 0 if OK, 1 if record exists and DB_INSERT specified,
 * -1 if record doesn't exist and DB_REPLACE specified. */

int
db_store(DB *db, const char *key, const char *data, int flag)
{
	int		rc, keylen, datlen;
	off_t	ptrval;

	keylen = strlen(key);
	datlen = strlen(data) + 1;		/* +1 for newline at end */
	if (datlen < DATLEN_MIN || datlen > DATLEN_MAX)
		err_dump("invalid data length");

		/* _db_find() calculates which hash table this new record
		   goes into (db->chainoff), regardless whether it already
		   exists or not.  The calls to _db_writeptr() below
		   change the hash table entry for this chain to point to
		   the new record.  This means the new record is added to
		   the front of the hash chain. */

	if (_db_find(db, key, 1) < 0) {		/* record not found */
		if (flag & DB_REPLACE) {
			rc = -1;
			db->cnt_storerr++;
			goto doreturn;		/* error, record does not exist */
		}

			/* _db_find() locked the hash chain for us; read the
			   chain ptr to the first index record on hash chain */
		ptrval = _db_readptr(db, db->chainoff);

		if (_db_findfree(db, keylen, datlen) < 0) {
				/* An empty record of the correct size was not found.
				   We have to append the new record to the ends of
				   the index and data files */
			_db_writedat(db, data, 0, SEEK_END);
			_db_writeidx(db, key, 0, SEEK_END, ptrval);
				/* db->idxoff was set by _db_writeidx().  The new
				   record goes to the front of the hash chain. */
			_db_writeptr(db, db->chainoff, db->idxoff);
			db->cnt_stor1++;
		} else {
				/* We can reuse an empty record.
				   _db_findfree() removed the record from the free
				   list and set both db->datoff and db->idxoff. */
			_db_writedat(db, data, db->datoff, SEEK_SET);
			_db_writeidx(db, key, db->idxoff, SEEK_SET, ptrval);
				/* reused record goes to the front of the hash chain. */
			_db_writeptr(db, db->chainoff, db->idxoff);
			db->cnt_stor2++;
		}

	} else {						/* record found */
		if (flag & DB_INSERT) {
			rc = 1;
			db->cnt_storerr++;
			goto doreturn;		/* error, record already in db */
		}

			/* We are replacing an existing record.  We know the new
			   key equals the existing key, but we need to check if
			   the data records are the same size. */
		if (datlen != db->datlen) {
			_db_dodelete(db);	/* delete the existing record */

				/* Reread the chain ptr in the hash table
				   (it may change with the deletion). */
			ptrval = _db_readptr(db, db->chainoff);

				/* append new index and data records to end of files */
			_db_writedat(db, data, 0, SEEK_END);
			_db_writeidx(db, key, 0, SEEK_END, ptrval);
				/* new record goes to the front of the hash chain. */
			_db_writeptr(db, db->chainoff, db->idxoff);
			db->cnt_stor3++;

		} else {
				/* same size data, just replace data record */
			_db_writedat(db, data, db->datoff, SEEK_SET);
			db->cnt_stor4++;
		}
	}
	rc = 0;		/* OK */
doreturn:	/* unlock the hash chain that _db_find() locked */
	if (un_lock(db->idxfd, db->chainoff, SEEK_SET, 1) < 0)
		err_dump("un_lock error");
	return(rc);
}
