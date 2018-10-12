#include	<sys/types.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"ourhdr.h"
#include	"db.h"

/* Use the undocmuented _db_hash() function to determine the hash
 * statistics of a database. */

void doit(char *);

main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("tstats <db>");

	doit(argv[1]);
	exit(0);
}

long	cntr[NHASH_DEF];

void doit(char *pathname)
{
	DB		*db;
	char	key[IDXLEN_MAX], *ptr;
	hash_t	hash;
	int		i, nrec;

	if ( (db = db_open(pathname, O_RDONLY, 0)) == NULL)
		err_sys("db_open error");

	nrec = 0;
	while ( (ptr = db_nextrec(db, key)) != NULL) {
		nrec++;
		hash = _db_hash(db, key);
		cntr[hash]++;
	}

	printf("total #records = %d\n", nrec);
	for (i = 0; i < NHASH_DEF; i++) {
		printf("%3d: %6ld\n", i, cntr[i]);
	}

	if ( (i = _db_checkfree(db)) < 0)
		printf("corrupted free list\n");
	else
		printf("%d records on free list\n", i);

	exit(0);
}
