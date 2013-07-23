/* THIS PROGRAM IS MADE TO BE USED WITH OMNIPRESENCE SOFTWARE WHICH IS AN INDUSTRY ATTENDANCE AUTOMATION SOFTWARE.
 * 	NAME		: Saurajeet Dutta
 * 	MAIL AT		: <vention.gothics@gmail.com>
 * 	INSTITUTE	: Birla Institute Of Technology, Mesra, Ranchi - 2
 *  	LICENSE		: FREE REDISTRIBUTABLE
 * THOUGH WE HAVE TESTED THE BOUNDS OF THIS SOFTWARE BUT STILL WE DONOT PROVIDE ANY WARRANTY OR GUARANTEE OR SUCH. WE WILL NOT BE RESPONSIBLE
 * FOR ANY DAMAGE CAUSED THEREIN DUE TO USE OF THIS SOFTWARE OR ANY OF ITS PARTS.
 */
//#include <stdio.h>
//#include <mysql/mysql.h>
//#include <string.h>
void rnadCopy()
{	char month[6] = "";
	char queryCopy[400]= "INSERT INTO ";
	char queryInit[400] = "INSERT INTO ";
	char attendSHEET[25] = "attendanceSheet";
	MYSQL * connectionWD, *connectionAS;
	MYSQL_RES * resWD, * resAS;
	MYSQL_ROW rowWD, rowAS;
	int retCode = 0,i=0;
	
	//CREATING CONNECTION WITH THE DATABASE
	printf("RNADCP:: Connecting to Database....");
		connectionWD = mysql_init(NULL);
		connectionAS = mysql_init(NULL);
		char * server = "localhost";
		//char * user = "root";
		//char * password = "omni";
		char * database = "omniPresence";
		if (!mysql_real_connect (connectionWD, server, user, password, database, 0, NULL, 0))
		{	printf ("RNADCP:: UNABLE TO CONTACT WORKERS DATABASE...%s\n", mysql_error(connectionWD));
	//		return 1;
		}
		if (!mysql_real_connect (connectionAS, server, user, password, database, 0, NULL, 0))
		{	printf ("RNADCP:: UNABLE TO CONNECT ATTENDANCE SHEET...%s\n", mysql_error(connectionAS));
	//		return 1;
		}
	printf ("done\n");
	//CONNECTED TO DATABASE

	//ASKING FOR INPUT
		printf("RNADCP:: Please Enter the month & year for which the rNad is to be initialised (e.g. 0209 for Feb 2009) ::");
		scanf ("%s",&month);
	//END INPUT

	//SELECTING THE ATTENDANCE SHEET TO BE FILLED
		strcat (attendSHEET, month);
		printf("RNADCP:: AttendanceSheet Selected is %s\n", attendSHEET);
	//ATTENDANCE SHEET SELECTED

	//INITIALISING DATA TO BE COPIED
		char queryWD[25] = "SELECT * FROM workersDB";
		retCode = mysql_query(connectionWD,queryWD);
		if (retCode != 0)
		{	printf ("RNADCP:: ERROR IN PARSING QUERY TO DATABASE...%s\n", mysql_error(connectionWD));
	//		return 1;
		}
		resWD = mysql_use_result (connectionWD);
		if (resWD == NULL)
			printf ("RNADCP:: NO RESULT RETURNED BY QUERY.\n");
	//COPY DATA INITIALISED
	//STARTING TO COPY DATA
	while ((rowWD = mysql_fetch_row(resWD)) != NULL)
	{	//CREATING PARTIAL QUERY
			strcat(queryCopy, attendSHEET);
			strcat (queryCopy, " (rNAD) values ('");
			strcat (queryCopy, rowWD[3]);
			strcat (queryCopy, "') ");
			printf("RNADCP::  Query:: %s\n",queryCopy);
		//PARTIAL QUERY CREATED
			retCode=mysql_query(connectionAS,queryCopy);
		//QUERY MADE & RESET QUERYCOPY
			strcpy(queryCopy,"INSERT INTO ");
			if (retCode != 0)
			{      printf("Already Copied..!!\n");
	//			return 1;
			}
	}
	printf("Copied...\n");
	mysql_close(connectionWD);
	mysql_close(connectionAS);

}
