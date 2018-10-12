#include	"db.h"
#include	<stdio.h>

/* Print and reset the accumulated statistics. */

void
db_stats(DB *db)
{
	fprintf(stderr, "%d: del=%ld+%ld, fetch=%ld+%ld, next=%ld, "
					"store=%ld(%ld+%ld+%ld+%ld+%ld)\n", getpid(),
				db->cnt_delok, db->cnt_delerr,
				db->cnt_fetchok, db->cnt_fetcherr,
				db->cnt_nextrec,
				(db->cnt_stor1 + db->cnt_stor2 + db->cnt_stor3 + 
				 db->cnt_stor4 + db->cnt_storerr),
				db->cnt_stor1, db->cnt_stor2, db->cnt_stor3, 
				db->cnt_stor4, db->cnt_storerr);

	db->cnt_delok = db->cnt_delerr =
	db->cnt_fetchok = db->cnt_fetcherr = db->cnt_nextrec =
	db->cnt_stor1 = db->cnt_stor2 = db->cnt_stor3 =
	db->cnt_stor4 = db->cnt_storerr = 0;
}
