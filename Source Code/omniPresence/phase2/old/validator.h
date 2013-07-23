#ifndef _VALIDATOR_H_
	#define _VALIDATOR_H_

int validateMain()
{	
	printf ("VALMOD:: Validator is starting up..");
		//LOCAL VARIABLES
		unsigned short retCode_VM = 0;
		char query_VM[50] = "SELECT * from workersDB";
		char queryAS_VM[100] = "SELECT Attend";
		char queryAS_VMbck[100] = "SELECT Attend";
		char * server = "localhost";
		char * user = "root";
		char * password = "omni";
		char * database = "omniPresence";
		unsigned short date_VM = 0;
		char dateStr_VM[4] = "";
		char month_VM[6] = "";
		unsigned int localCtr_VM = 0;
		//END LOCAL VARIABLES

		//MYSQL CONNECTIONS
		MYSQL * connectionAS_VM;
		MYSQL * connectionWD_VM;
		MYSQL * connectionAL_VM;
		MYSQL * connectionAS_VM2;
		MYSQL_RES * resultWD_VM;
		MYSQL_RES * resultAS_VM;
		MYSQL_ROW rowsWD_VM;
		MYSQL_ROW rowsAS_VM;
		//END MYSQL CONNECTIONS
		
		//CONNECT TO DATABASE
		connectionAS_VM = mysql_init(NULL);
		connectionWD_VM = mysql_init(NULL);
		connectionAL_VM = mysql_init(NULL);
		connectionAS_VM2 = mysql_init(NULL);
		if (!mysql_real_connect(connectionWD_VM, server, user, password, database , 0, NULL, 0))
		{	printf("\nError in connection: wd :  %s\n", mysql_error(connectionWD_VM));
			return 1;
		}
		if (!mysql_real_connect(connectionAS_VM, server, user, password, database, 0, NULL, 0))
		{	printf ("\nError in connection: as : %s\n", mysql_error(connectionAS_VM));
			return 1;
		}
		if (!mysql_real_connect(connectionAL_VM, server, user, password, database, 0, NULL, 0))
		{	printf ("\nError in connection: al : %s\n", mysql_error(connectionAL_VM));
			return 1;
		}
		if (!mysql_real_connect(connectionAS_VM2, server, user, password, database, 0, NULL, 0))
		{	printf ("\nError in connection: as2 : %s\n", mysql_error(connectionAS_VM2));
			return 1;
		}
		//CONNECTED
	printf ("done.\n");
	
	//ACCESS THE RNAD FROM WORKERS DATABASE
	retCode_VM = mysql_query(connectionWD_VM, query_VM);
	if (retCode_VM == 1)
	{	printf ("VALMOD:: Error in parsing query: wd : %s\n", mysql_error(connectionWD_VM));
		return 2;
	}
	resultWD_VM = mysql_use_result(connectionWD_VM);
	//RNADS IN BUFFER

	//INPUT THE DATE AND ATTENDANCESHEET FROM THE USER AND START PROCESSING THE INPUT DATE
	printf ("VALMOD:: Please input the month for which the dates are to be processed (e.g. 0209 for Feb 2009) :: ");
	scanf("%s", &month_VM);
	printf ("VALMOD:: Please input the date which you want to process (e.g. 1 for 1st and 20 for 20th) :: ");
	scanf ("%d", &date_VM);
	if (date_VM <= 9)
		sprintf (dateStr_VM, "0%d", date_VM);
	else
		sprintf (dateStr_VM, "%d", date_VM);
	strcat (queryAS_VM, dateStr_VM);
	strcat (queryAS_VMbck, dateStr_VM);

	strcat (queryAS_VM, " FROM attendanceSheet");
	strcat (queryAS_VMbck, " FROM attendanceSheet");
	strcat (queryAS_VM, month_VM);
	strcat (queryAS_VMbck, month_VM);
	
	strcat (queryAS_VM, " WHERE rNAD = '");
	strcat (queryAS_VMbck, " WHERE rNAD = '");

		//START PROCESSING THE ENTRIES
			while((rowsWD_VM = mysql_fetch_row(resultWD_VM)) != NULL)
			{	strcat (queryAS_VM, rowsWD_VM[3]);
				strcat (queryAS_VM, "'");

				if ((retCode_VM = mysql_query(connectionAS_VM, queryAS_VM)) == 1)
				{	printf ("VALMOD:: Error in parsing query : %s.\n", mysql_error(connectionAS_VM));
					return 2;
				}
				
				resultAS_VM = mysql_use_result (connectionAS_VM);
				rowsAS_VM = mysql_fetch_row (resultAS_VM);
				printf("VALMOD:: %s\n", rowsAS_VM[0]);
				strcpy (queryAS_VM, queryAS_VMbck);
			}
		//ENTRIES PROCESSED

	//CLEANUP, COLLECT, DISCONNECT AND SHUTDOWN
	printf("VALMOD:: Objective Complete. Shutting Down System..");
	mysql_free_result(resultWD_VM);
	mysql_free_result(resultAS_VM);
	mysql_close(connectionAS_VM);
	mysql_close(connectionWD_VM);
	mysql_close(connectionAS_VM2);
	mysql_close(connectionAL_VM);
	printf ("done.\n");
	return EXIT_SUCCESS;
}
#endif //_VALIDATOR_H_
