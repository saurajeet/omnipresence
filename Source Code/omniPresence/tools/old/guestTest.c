#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>
#include "guest/guest.h"

int main()
{	char mAC[] = "00:45:ed:5f:2c:14";
	char entryTime[] = "18 : 52";
	char exitTime[] = "19 : 20";
	char dateOfEntry[] = "Jan 28, 2009";
	char nameOfGuest[] = "W.H. Gates";
	int retCode = 0;

	retCode = makeGuestEntry (mAC, entryTime, exitTime, dateOfEntry, nameOfGuest);
	if (retCode = 0)
		printf("GUESTTEST:: Entry Made Succesfully");
	else
		printf ("GUESTTEST:: Some Error Occurred, Entry Not Made:: RETCODE = %d", retCode);

	return 0 ;
}
