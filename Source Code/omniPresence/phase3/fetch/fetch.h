#ifndef FETCH_H_
	#define FETCH_H_

//MYSQL CONNECTIONS
	MYSQL * connectionRecpt;
//END MYSQL CONNECTIONS

int fetch(char sdMAC[19], char entryTime[], char date[])
{	MYSQL_RES *searchResult;
	searchResult=search(sdMAC,0,"workersDB");
	if(searchResult==NULL)
	{	printf("FETCHMOD:: \t\t\tFound a Guest for MAC: %s\n", sdMAC);
		retCode = makeGuestEntry(sdMAC, entryTime, "*", date, "");
		if (retCode == 0)
			printf("FETCHMOD:: \t\t\tEntered in Guest Database..\n");
		else
			printf("FETCHMOD:: \t\t\tError in adding to Guest Database..\n");
		return 1;
	}
	else
	{	printf("FETCHMOD:: \t\t\tMAKE ATTENDENCE for %s (EID:%s)\n", resultDetails[1], resultDetails[2]);
		retCode = makeAttendance(resultDetails[3], date, entryTime, "NULL", "P", attendanceSheet);
		if (retCode == 0)
		{	//QUERY CREATION 
				char queryPresent[100] = "INSERT INTO presentList VALUES ('";
				strcat (queryPresent, resultDetails[4]);
				strcat (queryPresent, "','");
				strcat (queryPresent, date);
				strcat (queryPresent, "','");
				strcat (queryPresent, resultDetails[1]);
				strcat (queryPresent, "')");
				//printf ("FETCHMOD:: QUERY FOR POST PROCESSING: %s\n", queryPresent);
			//END QUERY CREATION
			
			retCode = mysql_query (connectionRecpt, queryPresent);
			if (retCode == 1)
			{	printf ("FETCHMOD:: \t\tQuery Injection Failed For PostProcessing Attendance Making Process\n");
				printf ("FETCHMOD:: \t\t%s\n", mysql_error(connectionRecpt));
			}
			else
				printf ("FETCHMOD:: \t\t\tAttendance Made for the above employee\n");
		}
		else
			printf ("FETCHMOD:: \t\t\tError in Making Attendance\n");
	}	
	return 0;
}
#endif //FETCH_H_
