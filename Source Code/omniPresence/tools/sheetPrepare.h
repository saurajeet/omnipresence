#ifndef _SHEETPREPARE_H_
	#define _SHEETPREPARE_H_

int prepareSheetMain()
{	//LOCAL VARIABLES
	char sheetNAME_PS[35] = "attendanceSheet";
	char monthYear_PS[7] = "";
	char query_PS[70] = "UPDATE ";
	char query_PSbck[70] = "UPDATE ";
	char * server = "localhost";
	//char * user = "root";
	//char * password = "omni";
	char * database = "omniPresence";
	char choice_PS = 'Y';
	unsigned short noOfHolidays = 0;
	unsigned short holidaysBCK = 0;
	unsigned short localCtr_PS = 0;
	unsigned short day_PS = 0;
	char day_PSstr[3] = "";
	unsigned short retCode = 0;
	char queryCopy[400]= "INSERT INTO ";
        char queryInit[400] = "INSERT INTO ";
        char attendSHEET[25] = "attendanceSheet";
        int i=0;
	//END LOCAL VARIABLES

	//LOCAL MYSQL CONNECTIONS
	MYSQL * connectionAS_PS;
        MYSQL * connectionWD;
	MYSQL * connectionAS;
        MYSQL_RES * resWD;
	MYSQL_RES * resAS;
        MYSQL_ROW rowWD;
	MYSQL_ROW rowAS;
	//END LOCAL MYSQL CONNECTIONS
	
	//CONNECTING TO THE DATABASE
	printf("PREPSHEET:: CONNECTING TO THE DATABASE.....");
	connectionAS_PS = mysql_init(NULL);
	connectionWD = mysql_init(NULL);
	connectionAS = mysql_init(NULL);
	if (!mysql_real_connect(connectionAS_PS, server, user, password, database, 0,NULL,0))
	{	printf ("\nPREPSHEET:: ERROR CONNECTING TO DATABASE ..%s\n", mysql_error(connectionAS_PS));
		return 1;
	}
	if (!mysql_real_connect (connectionWD, server, user, password, database, 0, NULL, 0))
	{       printf ("PREPSHEET:: UNABLE TO CONTACT WORKERS DATABASE...%s\n", mysql_error(connectionWD));
		return 1;
	}
	if (!mysql_real_connect (connectionAS, server, user, password, database, 0, NULL, 0))
	{       printf ("PREPSHEET:: UNABLE TO CONNECT ATTENDANCE SHEET...%s\n", mysql_error(connectionAS));
		return 1;
	}
	printf ("CONNECTED.\n");
	//CONNECTED

	//PROCEED FOR INPUT
	printf ("PREPSHEET:: Please enter the month & year for which you want to prepare the attendanceSheet.(e.g. 0209 for Feb 2009) ::");
	scanf  ("%s", &monthYear_PS);
	strcat (sheetNAME_PS, monthYear_PS);
	printf ("PREPSHEET:: Sheet Selected for Preparation is %s.\n", sheetNAME_PS);
	printf ("PREPSHEET:: Do you want to continue [Y/N] ::");
	choice_PS = getchar();
	choice_PS = getchar();
	if (choice_PS == 'y' || choice_PS == 'Y')
	{	
		//ASK FOR COPYING THE VALUES FROM WORKERSDB TO ATTENDANCESHEET
		printf ("PREPSHEET:: Do you want to make entries for the workers in the selected attendance sheet [Y/N] :: ");
		choice_PS = getchar();
		choice_PS = getchar();
		if (choice_PS == 'y' || choice_PS == 'Y')
		{	//INITIALISING DATA TO BE COPIED
	                char queryWD[25] = "SELECT * FROM workersDB";
	                retCode = mysql_query(connectionWD,queryWD);
	                if (retCode != 0)
        	        {       printf ("PREPSHEET:: ERROR IN PARSING QUERY TO DATABASE...%s\n", mysql_error(connectionWD));
	        //              return 1;
	                }
	                resWD = mysql_use_result (connectionWD);
	                if (resWD == NULL)
	                        printf ("PREPSHEET:: NO RESULT RETURNED BY QUERY.\n");
	        //COPY DATA INITIALISED
	        //STARTING TO COPY DATA
	        	while ((rowWD = mysql_fetch_row(resWD)) != NULL)
		        {       //CREATING PARTIAL QUERY
		                        strcat(queryCopy, sheetNAME_PS);
		                        strcat (queryCopy, " (rNAD) values ('");
		                        strcat (queryCopy, rowWD[3]);
		                        strcat (queryCopy, "') ");
		                        printf("PREPSHEET::  Query:: %s\n",queryCopy);
		                //PARTIAL QUERY CREATED
		                        retCode=mysql_query(connectionAS,queryCopy);
		                //QUERY MADE & RESET QUERYCOPY
		                        strcpy(queryCopy,"INSERT INTO ");
		                        if (retCode != 0)
		                        {      printf("Already Copied..!!\n");
		        //                      return 1;
		                 	}
	        	}
        		printf("PREPSHEET:: EMPLOYEE ENTRIES INITIALISED\n");
		}
		else
			printf ("PREPSHEET:: EMPLOYEE ENTRIES NOT CREATED :: USER ABORT.\n");
		//COPIED OR ABORTED
		
		printf("PREPSHEET:: Please enter the number of holidays in this month including the sundays ::");
		scanf ("%d", &noOfHolidays);
		holidaysBCK = noOfHolidays;
		//printf("PREPSHEET:: nO. OF hOLIDAYS: %d-%d\n",noOfHolidays, holidaysBCK);
		strcpy (query_PSbck, "UPDATE ");
		strcat (query_PS, sheetNAME_PS);
		strcat (query_PSbck, sheetNAME_PS);
		strcat (query_PS, " SET Attend");
		strcat (query_PSbck, " SET Attend");
		//printf ("PREPSHEET:: Str: %s.\n", query_PS);
		//printf ("PREPSHEET:: Str: %s.\n", query_PSbck);
		for (localCtr_PS = 0; localCtr_PS < noOfHolidays; localCtr_PS++)
		{	printf ("PREPSHEET:: Please enter the holiday[%d] (e.g. 1 for 1st, 20 for 20th) :: ", (localCtr_PS + 1));
			scanf  ("%d", &day_PS);
			if (day_PS <=9)
				sprintf (day_PSstr, "0%d", day_PS);
			else
				sprintf (day_PSstr, "%d", day_PS);
			strcat (query_PS, day_PSstr);
			strcat (query_PS, "='H'");
			//printf ("PREPSHEET:: Query: %s, NoOfHoldays: %d\n", query_PS, noOfHolidays);
			retCode = mysql_query (connectionAS_PS, query_PS);
			if (retCode == 1)
				printf ("PREPSHEET:: There was some error in executing the query.\n");
			strcpy (query_PS, query_PSbck);
			strcpy (day_PSstr, "");
			noOfHolidays = holidaysBCK;

		}
		printf ("PREPSHEET:: Attendance Sheet has been Prepared.\n");
	}
	else
		printf("PREPSHEET:: Attendance Sheet preparation Cancelled : USER ABORT.\n ");

	//SHUTTING DOWN SHEETPREPARE
	//mysql_free_result(resWD);
	//mysql_free_result(resAS);
	mysql_close(connectionWD);
	mysql_close(connectionAS_PS);
	mysql_close(connectionAS);
	return 0;	
}

#endif //_SHEETPREPARE_H_
