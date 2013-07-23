#ifndef _PHASE3_H_
	#define _PHASE3_H_
/* THIS PROGRAM IS THE CONTROLLER PROGRAM FOR OMNIPRESENCE DATABASE ACTIVITIES DONE FOR MARKING THE ATTENDANCE FROM PHASE I
 * 	NAME: 		Saurajeet Dutta, JyotiPrakash Nath, Rahul Bose, Purushottam
 * 	MAILING LIST:	<vention.gothics@gmail.com>, <jp2018@gmail.com>, <rahul2016@gmail.com>, <purushottam.prince@gmail.com>
 *	INSTITUTE:	Birla Institute Of Technology, Extension Centre Lalpur, Ranchi, Jharkhand, India
 * 	LICENSE:	GPL V2
 * PLEASE REMEMBER THAT THIS MODULE OR ANY OF THE COUNTERPARTS OF THE SOFTWARE DOES NOT COME WITH A WARRANTY OT SUCH. FOR PROGRAMMATICAL FUN 
 * ONLY. INCASE OF ANY DISPUTES PLEASE DONOT HELD US RESPONSIBLE..
 */

//GLOBAL VARIABLES
	//work variables
		char dayOfEntry[4] = "28";
		char month[4] = "01";
		char year[6] = "2009";
		char attendanceSheet[50] = "attendanceSheet0109";
		char colName[15] = "Attend";
		char * server = "localhost";
		//char * user = "root";
		//char * password = "omni";
		char * database = "omniPresence";
		int info = 0;
		int numberOfAttendancesMade = 0;
		int numberOfGuests = 0;
		MYSQL_RES * resultLastDumpSession;
		MYSQL_RES * resultScanDump;
		MYSQL_RES * resultAttendanceSheet;
		MYSQL_ROW rowLDS;
		MYSQL_ROW rowSD;
		MYSQL_ROW rowAS;
		int retCode = 0;
		char year_tot[2] = "09";

	//connections
		MYSQL * connectionLastDumpSession;
		MYSQL * connectionScanDump;
		MYSQL * connectionAttendanceSheet;
//END GLOBAL VARIABLES

//SEARCH SPECIFIC INITIALISATION
	MYSQL *conn;
	MYSQL_RES * result, * ret;
	MYSQL_ROW row,resultDetails;
//END SEARCH INITIALISATION

//INCLUDE CUSTOM HEADERS
	#include "search/search.h"
	#include "guest/guest.h"
	#include "fetch/fetch.h"
	#include "sheet/absentMarker.h"
	#include "sheet/attendance.h"
	#include "sheet/dateExtracter.h"
//END SEARCH INITIALISATION


//START MAIN
int phase3main (void)
{	//LOCAL VARIABLES
		register unsigned int i = 0;
		register unsigned int rowsProcessed = 0;
		char choiceCleanup = 'Y';
	//END LOCAL VARIABLES

	//INITIALISING SYSTEM
	printf ("ATTENDMOD:: Initialising System Components and Variables...");
	connectionLastDumpSession = mysql_init (NULL);
	connectionScanDump = mysql_init(NULL);
	connectionAttendanceSheet = mysql_init(NULL);
	connectionRecpt = mysql_init(NULL);
	if (!mysql_real_connect(connectionLastDumpSession, server, user, password, database, 0 , NULL, 0))
	{	printf ("\nATTENDMOD:: ERROR IN CONNECTION TO DATABASE: lds: %s\n", mysql_error(connectionLastDumpSession));
		info = 1;
	}
	if (!mysql_real_connect(connectionScanDump, server, user, password, database, 0 , NULL, 0))
	{	printf ("\nATTENDMOD:: ERROR IN CONNECTION TO DATABASE: sd: %s\n", mysql_error(connectionScanDump));
		info = 1;
	}
	if (!mysql_real_connect(connectionAttendanceSheet, server, user, password, database, 0, NULL, 0))
	{	printf ("\nATTENDMOD:: ERROR IN CONNECTION TO DATABASE: as: %s\n", mysql_error(connectionAttendanceSheet));
		info = 1;
	}
	if (!mysql_real_connect(connectionRecpt, server, user, password, database, 0, NULL, 0))
	{	printf ("\nATTENDMOD:: ERROR IN CONNECTION TO DATABASE: pl: %s", mysql_error(connectionRecpt));
		info = 1;
	}
	if (info == 0)	
		printf("DONE\n");
	else
		goto shutdown;
	//END INITIALISATION
	
	//PARSING QUERY AND ACCESSING LAST DUMP SESSION
	retCode = mysql_query(connectionLastDumpSession, "SELECT * FROM lastDumpSession");
	if (retCode == 1)
	{	printf ("ATTENDMOD:: Error parsing query at lastDumpSession: %s\n",mysql_error(connectionLastDumpSession));
		info = 1;
	}
	resultLastDumpSession = mysql_use_result(connectionLastDumpSession);
	if (resultLastDumpSession == NULL)
	{	printf ("ATTENDMOD:: Error in result Obtained from LDS : %s\n", strerror(errno));
		info = 1;
	}
	if (info == 1)
		goto shutdown;
	//CONNECTED TO LAST DUMP SESSION

	//PARSING QUERY AND ACCESSING SCAN DUMP TABLE
	retCode = mysql_query(connectionScanDump, "SELECT * FROM scanDump");
	if (retCode == 1)
	{	printf("ATTENDMOD:: Error Parsing Query at scanDump Table: %s\n", mysql_error(connectionScanDump));
		info =1;
	}
	resultScanDump = mysql_use_result(connectionScanDump);
	if (resultScanDump == NULL)
	{	printf("ATTENDMOD:: Error in result Obtained from SD : %s\n", strerror(errno));
		info = 1;
	}
	if (info == 1)
		goto shutdown;
	//CONNECTED TO SCAN DUMP TABLE

	//PERFORM ATTENDANCE MAKING PROCESS
	while ((rowLDS = mysql_fetch_row(resultLastDumpSession)) != NULL)
	{	i++;
		printf("ATTENDMOD:: Row[%d] at LDS :%s, %s, %s , %d\n", i, rowLDS[0],rowLDS[1],rowLDS[2], atoi(rowLDS[2]));
		selectSheet(rowLDS[0]);
		for(;rowsProcessed < atoi(rowLDS[2]);rowsProcessed++)
		{	rowSD = mysql_fetch_row(resultScanDump);
			if (rowSD != NULL) 
			{	printf("ATTENDMOD:: \t\tRows at SD[%d] %s %s\n",rowsProcessed, rowSD[1], rowSD[2]);
				retCode = fetch(rowSD[1], rowSD[2], rowLDS[0]);
				if (retCode == 0)
					numberOfAttendancesMade++;
				else
					numberOfGuests++;
		
			}
		}
	}
	//ATTENDANCES MADE FOR ALL ENTRIES IN THE SCANDUMP
	printf("ATTENDMOD:: Number Of Attendances Made: %d\n", numberOfAttendancesMade);
	printf("ATTENDMOD:: Number Of Guests detected: %d\n", numberOfGuests);
	
	//PROCEED FOR MARKING THE ABSENTIES
		
	//ABSENTIES MARKED
		retCode = markAbsent();
		printf ("ATTENDMOD:: Absent marker returned :%d.\n", retCode);
	//PROCEED FOR SYSTEM SHUTDOWN
	
	//FILL THE ABSENTLIST TABLE
		char absentDate_P3[3] = "";
		char absentMonth_P3[3] = "";
		char absentYear_P3[3]= "";
		absentDate_P3[0] = colName[6];
		absentDate_P3[1] = colName[7];
		absentMonth_P3[0] = attendanceSheet[15];
		absentMonth_P3[1] = attendanceSheet[16];
		absentYear_P3[0] = attendanceSheet[17];
		absentYear_P3[1] = attendanceSheet[18];
		printf ("ATTENDMOD:: Date of absentList - %s/%s/%s\n", absentDate_P3, absentMonth_P3, absentYear_P3);
		AbsentCheck(&absentDate_P3[0], &absentMonth_P3[0], &absentYear_P3[0]);
	//ABSENT LIST FILLED
	shutdown:
	//CLEAR THE SCANDUMP AND LAST DUMP SESSION
	
	//char choiceCleanup = 'Y';
	printf ("ATTENDMOD:: Do you want to cleanup the scanDump and LastDumpSession Tables: ");
	choiceCleanup = getchar();
	choiceCleanup = getchar();
	if (choiceCleanup == 'Y' || choiceCleanup == 'y')
	{	retCode = mysql_query (connectionLastDumpSession, "TRUNCATE lastDumpSession");
		if (retCode == 1)
			printf ("ATTENDMOD:: Unable to delete all values from the table lds\n");
		retCode = mysql_query (connectionLastDumpSession, "TRUNCATE scanDump");
		if (retCode == 1)
			printf ("ATTENDMOD:: Unable to delete all values from the table sd\n");
	}

	//CALCULATE TOTAL ATTENDANCE
		year_tot[0] = year[2];
		year_tot[1] = year[3];
		totalAttendance (absentMonth_P3, absentYear_P3);

	//COLLECT AND SHUTDOWN SYSTEM
	printf ("ATTENDMOD:: Shutting Down System....");
	mysql_free_result(resultLastDumpSession);
	mysql_free_result(resultScanDump);
	mysql_free_result(resultAttendanceSheet);
	mysql_close(connectionLastDumpSession);
	mysql_close(connectionScanDump);
	mysql_close(connectionAttendanceSheet);
	mysql_close(connectionRecpt);
	printf ("DONE\n");
	return 0;
}
//END MAIN
#endif //_PHASE3_H_
