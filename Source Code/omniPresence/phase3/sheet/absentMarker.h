#ifndef _ABSENTMARER_H_
	#define _ABSENTMARKER_H_

unsigned int ctrAbsent_VM = 0;

int fillAbsentList();
int markAbsent()
{	
	printf ("VALMOD:: Validator is starting up..");
		//LOCAL VARIABLES
		unsigned short retCode_VM = 0;
		char queryWD_VM[100] = "SELECT name,phno from workersDB WHERE rNad = '";
		char queryWD_VMbck[100] = "";
		char queryAS_VM[100] = "SELECT rNAD ,Attend";
		char queryMA_VM[100] = "UPDATE attendanceSheet";
		char queryMA_VMbck[100] = "UPDATE attendanceSheet";
		//char * server = "localhost";
		//char * user = "root";
		char * password = "omni";
		char * database = "omniPresence";
		unsigned short date_VM = 0;
		char dateStr_VM[4] = "";
		char month_VM[6] = "";
		unsigned int localCtr_VM = 0;
		char attendStatus_VM[20] = "";
		char dateAL_VM[16] = "";
		//END LOCAL VARIABLES

		//MYSQL CONNECTIONS
		MYSQL * connectionAS_VM;
		MYSQL * connectionAS_VM2;
		MYSQL_RES * resultAS_VM;
		MYSQL_ROW rowsAS_VM;
		//END MYSQL CONNECTIONS
		
		//CONNECT TO DATABASE
		connectionAS_VM = mysql_init(NULL);
		connectionAS_VM2 = mysql_init(NULL);
		if (!mysql_real_connect(connectionAS_VM, server, user, password, database, 0, NULL, 0))
		{	printf ("\nError in connection: as : %s\n", mysql_error(connectionAS_VM));
			return 1;
		}
		if (!mysql_real_connect(connectionAS_VM2, server, user, password, database, 0, NULL, 0))
		{	printf ("\nError in connection: as2 : %s\n", mysql_error(connectionAS_VM2));
			return 1;
		}
		//CONNECTED
	printf ("done.\n");
	
	//INPUT THE DATE AND ATTENDANCESHEET FROM THE USER AND START PROCESSING THE INPUT DATE
	printf ("VALMOD:: Please input the month for which the dates are to be processed (e.g. 0209 for Feb 2009) :: ");
	scanf("%s", &month_VM);
	printf ("VALMOD:: Please input the date which you want to process (e.g. 1 for 1st and 20 for 20th) :: ");
	scanf ("%d", &date_VM);
	if (date_VM <= 9)
		sprintf (dateStr_VM, "0%d", date_VM);
	else
		sprintf (dateStr_VM, "%d", date_VM);
	
	strcpy (queryAS_VM, "SELECT rNAD, Attend");
	strcpy (queryWD_VM, "SELECT name,phno from workersDB WHERE rNad = '");
	strcpy (queryWD_VMbck, "SELECT name,phno from workersDB WHERE rNad = '");
	strcat (queryAS_VM, dateStr_VM);
	strcat (queryAS_VM, " FROM attendanceSheet");
	strcat (queryAS_VM, month_VM);

	strcat (queryMA_VM, month_VM);
	strcat (queryMA_VM, " SET Attend");
	strcat (queryMA_VM, dateStr_VM);
	strcat (queryMA_VM, " = 'A' WHERE rNAD = '");
	strcpy (queryMA_VMbck, queryMA_VM);
	//printf ("VALMOD:: Query: #1:%s #2%s.\n", queryAS_VM, queryMA_VM);
	
	//CREATING TODAYS DATE FOR ENTERING THE VALUE IN THE ABSENT LIST TABLE
	strcpy (dateAL_VM, dateStr_VM);
	strcat (dateAL_VM, ".");
	dateAL_VM[3] = month_VM[0];
	dateAL_VM[4] = month_VM[1];
	dateAL_VM[5] = '.';
	dateAL_VM[6] = '2';
	dateAL_VM[7] = '0';
	dateAL_VM[8] = month_VM[2];
	dateAL_VM[9] = month_VM[3];
	dateAL_VM[10] = '\0';
	printf ("VALMOD:: Date: %s.\n",dateAL_VM);
	//DATE CREATED 
	
	//ACCESSING VALUES FROM THE ATTENDANCE SHEET
	retCode_VM = mysql_query(connectionAS_VM, queryAS_VM);
	if (retCode_VM == 1)
	{	printf ("VALMOD:: Error in query Parsed: %s.\n", mysql_error (connectionAS_VM));
		return 2;
	}	
	resultAS_VM = mysql_use_result (connectionAS_VM);
	
	//START PROCESSING THE ENTRIES
	while((rowsAS_VM = mysql_fetch_row(resultAS_VM)) != NULL)
	{	
		sprintf (attendStatus_VM, "%s ", rowsAS_VM[1]);
		if 	(attendStatus_VM[0] == 'P')
			printf ("VALMOD:: %s - %s\t\tPRESENT\n", attendStatus_VM, rowsAS_VM[0]);
		else if (attendStatus_VM[0] == 'L')
			printf ("VALMOD:: %s -    %s\t\tLEAVE\n", attendStatus_VM, rowsAS_VM[0]);
		else if (attendStatus_VM[0] == 'H')
			printf ("VALMOD:: %s - %s\t\tHOLIDAY\n", attendStatus_VM, rowsAS_VM[0]);
		else
		{	printf ("VALMOD:: %s - %s\t\tABSENT\n", attendStatus_VM, rowsAS_VM[0]);
			//MARKING ABSENT IN THE DATABASE
				strcat (queryMA_VM, rowsAS_VM[0]);
				strcat (queryMA_VM, "'");
				//printf ("VALMOD:: \t\t%s.\n", queryMA_VM);
				retCode_VM = mysql_query(connectionAS_VM2, queryMA_VM);
				if (retCode_VM == 1)
				{	printf ("VALMOD:: \t\tQuery returned error : %s.\n", mysql_error(connectionAS_VM2));
				}
				strcpy (queryMA_VM, queryMA_VMbck);
			//MARKED ABSENT
			//SAVE SETTINGS
				strcat (queryWD_VM, rowsAS_VM[0]);
				strcat (queryWD_VM, "'");
				//printf ("VALMOD:: \t\tQuery:%s.\n", queryWD_VM);
				ctrAbsent_VM++;
				strcpy (queryWD_VM, queryWD_VMbck);
			//SETTINGS SAVED
		}
	}
	//ENTRIES PROCESSED
	printf ("VALMOD:: Number of absent found = %d", ctrAbsent_VM);

	//CLEANUP, COLLECT, DISCONNECT AND SHUTDOWN
	printf("VALMOD:: Objective Complete. Shutting Down System..");
	mysql_free_result(resultAS_VM);
	mysql_close(connectionAS_VM);
	mysql_close(connectionAS_VM2);
	printf ("done.\n");
	return EXIT_SUCCESS;
}

int fillAbsentList()
{	
	MYSQL * connectionAL_FA;
	MYSQL_RES * resultAL_FA;
	MYSQL_ROW rowsAL_FA;
	
	int localCtr_FA = 0;
	int retCode_FA = 0;

	//char * server = "localhost";
	//char * user = "root";
	char * password = "omni";
	char * database = "omniPresence";

	//CONNECT
	connectionAL_FA = mysql_init (NULL);
	if (!mysql_real_connect(connectionAL_FA, server, user, password, database, 0, NULL, 0))
	{	printf ("FILLAL:: ERROR IN CONNECTION:");
		return 1;
	}
	//CONNECTED
	//ACCESS THE QUERYWD TABLE AND FILL THE ABSENT LIST
        printf ("VALMOD:: Employees who are absent are:\n");
        for (localCtr_FA = 0; localCtr_FA < ctrAbsent_VM; localCtr_FA++)
        {       //printf ("VALMOD:: %s.\n", queryWDArray[localCtr_FA]);

                //retCode_FA = mysql_query (connectionAL_FA, queryWDArray[localCtr_FA]);
                if (retCode_FA == 1)
                {       printf ("VALMOD:: \tError in parsing query: %s.\n", mysql_error(connectionAL_FA));
                        return 2;
                }
                resultAL_FA = mysql_use_result (connectionAL_FA);
                rowsAL_FA = mysql_fetch_row(resultAL_FA);
                printf ("VALMOD:: Values %s - %s\n", rowsAL_FA[0], rowsAL_FA[1]);
        }
        //FILLED THE ABSENT LIST TABLE
}
#endif //_ABSENTMARKER_H_
