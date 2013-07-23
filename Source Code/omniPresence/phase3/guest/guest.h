/* THIS PROGRAM IS DESIGNED FOR OMNIPRESENCE SOFTWARE WHICH IS AN ATTENDANCE MAKING SOFTWARE
 * THIS MODULE IS TO BE USED WITH THE ABOVE SPECIFIED SOFTWARE ONLY
 * 	NAME:		 Saurajeet Dutta
 * 	INSTITUTE:	 Birla Institute Of Technology
 *	DATE:		 January 28, 2009
 * 	EMAIL:	 	 vention.gothics@gmail.com
 *	LICENSE:	 GPL V2
 * PLEASE TAKE A NOTE THAT THE SOFTWARE DOESNOT PROVIDE ANY WARRANTY OR SUCH. ONLY FOR PROGRAMMING FUN!!
 */

#ifndef GUEST_H_
	#define GUEST_H_

	int makeGuestEntry( char guestMAC[], char guestEntry[], char guestExit[], char DateOfEntry[], char nameOfGuest[])
	{
		//LOCAL DECLARATIONS
		MYSQL *connectionGuest;
		char queryGuest[400] = "INSERT INTO guestDB (GuestMAC, GuestEntry, GuestExit, DateOfEntry, NameOfGuest) VALUES ('";
		char * database = "omniPresence";
		//char * server = "localhost";
		//char * user = "root";
		char * password = "omni";
		//END LOCAL DECLARATIONS

		//CREATE QUERY
		strcat (queryGuest, guestMAC);
		strcat (queryGuest, "','");
		strcat (queryGuest, guestEntry);
		strcat (queryGuest, "','");
		strcat (queryGuest, guestExit);
		strcat (queryGuest, "','");
		strcat (queryGuest, DateOfEntry);
		strcat (queryGuest, "','");
		strcat (queryGuest, nameOfGuest);
		strcat (queryGuest, "')");
		//END CREATE QUERY

		//printf ("GUESTMOD:: Query: %s\n",queryGuest);

		//CONNECTING TO DATABASE
		connectionGuest = mysql_init(NULL);
		
		if (!mysql_real_connect (connectionGuest, server, user, password, database, 0 ,NULL, 0))
		{	printf ("GUESTMOD:: ERROR IN CONNECTION\n");
			return 1;
		}

		//INJECTING QUERY
		if (mysql_query(connectionGuest, queryGuest))
		{	printf ("GUESTMOD:: ERROR IN INJECTING QUERY \n %s", mysql_error(connectionGuest));
			return 2;
		}
		
		//CLOSING CONNECTION
		mysql_close(connectionGuest);
		return 0;
	}
#endif 		//GUEST_H_
