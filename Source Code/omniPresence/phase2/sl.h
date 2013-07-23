#ifndef _SL_H_
	#define _SL_H_

int sanctionLeaveMain()
{	//LOCAL VARIABLES
		char * server = "localhost";
		//char * user = "root";
		//char * password = "omni";
		char * database = "omniPresence";
		char choiceSL = 'Y';
		char eID[10] = "";
		char querySL[100] = "SELECT rNad,name FROM workersDB";
		char querySL2[100] = "UPDATE attendanceSheet";
		char querySL2bck[100] = "UPDATE attendanceSheet";
		char sheetSelectSL[60] = "";
		unsigned short retCodeSL = 0;
		char rowsAS_SLstr[50] = "";
		unsigned short noOfLeaves = 0;
		unsigned short noOfLeavesbck = 0;
		unsigned short localCtr_SL = 0;
		unsigned short day_SL = 0;
		unsigned short free_res_SL = 0;
		char day_SLstr[4] = "";
	//END LOCAL VARIABLES

	//MYSQL CONNECTIONS
		MYSQL * connectionAS_SL;
		MYSQL_RES * resultAS_SL;
		MYSQL_ROW rowsAS_SL;
		MYSQL * connectionAS_SL2;
	//END MYSQL CONNECTIONS

	//INITIALISE CONNECTION
		printf ("SANCLV:: Connecting to the database.....");
		connectionAS_SL = mysql_init (NULL);
		connectionAS_SL2 = mysql_init (NULL);
		if  (!mysql_real_connect (connectionAS_SL,  server, user, password, database, 0, NULL, 0))
		{	printf ("\nSANCLV:: #1: Error connecting to the database : %s.", mysql_error (connectionAS_SL));
			return 1;
		}
		if (!mysql_real_connect(connectionAS_SL2, server, user, password, database, 0, NULL, 0))
		{	printf ("\nSANCLV:: #2 Error connecting to the database : %s.", mysql_error (connectionAS_SL2));
			return 2;
		}
		else
			printf ("connected.\n");
	//CONNECTED

	//PROCEED NOW
	printf ("SANCLV:: Please enter a valid employee ID for whom you want to sanction the leave :: ");
	scanf ("%s", &eID);
	printf("SANCLV:: Employee ID selected is : %s\n", eID);
	printf("SANCLV::  Do you want to proceed and sanction leave [Y/N] :: ");
	choiceSL = getchar();
	choiceSL = getchar();
	if (choiceSL == 'Y' || choiceSL == 'y')
	{	printf("SANCLV:: \t\tFOR WHICH MONTH ::");
		scanf ("%s", &sheetSelectSL);

		strcat (querySL2, sheetSelectSL);
		strcat (querySL2bck, sheetSelectSL);
		strcat (querySL2, " SET Attend");
		strcat (querySL2bck, " SET Attend");
		
		strcat (querySL, " WHERE empID = '");
		strcat (querySL, eID);
		strcat (querySL , "'");
		//printf ("SANCLV:: Query: %s\n", querySL);

		//INJECT QUERY AND GET RNAD
		retCodeSL = mysql_query (connectionAS_SL, querySL);
		if (retCodeSL == 1)
		{	printf ("SANCLV:: Query didn't reflect value, because the employee doesn't exist.");
			printf ("Input a valid employeeID and retry. Exiting...\n");
			return 2;
		}
		resultAS_SL = mysql_use_result (connectionAS_SL);
		free_res_SL =1;
		if (resultAS_SL == NULL)
		{	printf ("SANCLV:: No value can be accessed from the database. Exiting..\n");
			return 2;
		}
		
		rowsAS_SL = mysql_fetch_row (resultAS_SL);
		if (rowsAS_SL[0] == NULL)
		{	printf ("SANCLV:: Please see to it that the eID is genuine and valid. Entry returned NULL.\n");
			return 3;
		}
		//RNAD AND NAME IN BUFFER
		
		printf ("SANCLV:: Selected employee is %s.\n", rowsAS_SL[1]);
		printf ("SANCLV:: Do you want to continue: [Y/N] :: ");
		choiceSL = getchar();
		choiceSL = getchar();
		if (choiceSL == 'Y' || choiceSL == 'y')
		{	printf ("SANCLV:: How many leaves do you want to assign :: ");
			scanf ("%d", &noOfLeaves);
			noOfLeavesbck = noOfLeaves;
			printf ("SANCLV:: No. of Leaves to be assigned : %d\n", noOfLeaves);
			for (localCtr_SL = 0; localCtr_SL < noOfLeaves; localCtr_SL++)
			{	printf ("SANCLV:: Please enter the leave[%d] [e.g. 1 for 1st, 20 for 20th] ::", (localCtr_SL + 1));
				scanf ("%d",&day_SL);
				if (day_SL <= 9)
					sprintf (day_SLstr, "0%d", day_SL);
				else
					sprintf (day_SLstr, "%d", day_SL);
				
				//CREATE THE QUERY
				strcat (querySL2, day_SLstr);
				strcat (querySL2, " = 'L' WHERE rNAD = '");
				sprintf (rowsAS_SLstr, "%s", rowsAS_SL[0]);
				strcat (querySL2, rowsAS_SLstr);
				strcat (querySL2, "'");
				//printf ("SANCLV:: Query : %s\n", querySL2);
				//END CREATION OF QUERY
				
				//INJECT THE QUERY
				retCodeSL = mysql_query(connectionAS_SL2, querySL2);
				if (retCodeSL == 1)
				{	printf ("SANCLV:: Query didnot reflect a change in the database. Objective Failed.\n");
					printf ("SANCLV:: %s. Exiting...\n", mysql_error(connectionAS_SL2));
					return 2;
				}
				//INJECTION COMPLETE
				noOfLeaves = noOfLeavesbck;
				//printf ("SANCLV:: %d, %d.\n", noOfLeaves, localCtr_SL);
				strcpy (querySL2, querySL2bck);
			}
			printf ("SANCLV:: Leave assigned. Objective Accomplished.\n");
			//you can send smses here
		}
		else
			printf ("SANCLV:: Leave Assignment Cancelled: USER ABORT.\n");
	}
	else
		printf("SANCLV:: Leave assignment cancelled: USER ABORT.\n");

	if (free_res_SL == 1)
		mysql_free_result (resultAS_SL);
	mysql_close (connectionAS_SL);
	mysql_close (connectionAS_SL2);
	return 0;
}

#endif //_SL_H_
