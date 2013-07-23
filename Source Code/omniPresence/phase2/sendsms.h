/* THIS PROGRAM OR SOFTWARE IS EXPLICITELY MADE FOR OMNIPRESENCE RFID SYSTEMS. PLEASE DONOT USE INDEPENDENTLY WITH ANY OTHER MODULE
 * THIS PROGRAM OR CODE WHEN CALLED WOULD BE NOTIFYING THE EMPLOYEES IN THE WORKERS DATABASE BY SHORT MESSAGING SERVICE. THIS MODULE
 * WOULD USE EXTERNAL CELLULAR NETWORK THAT MAY INCURR EXTRA CHARGES AS APPLICABLE BY DIFFERENT NETWORKS AND COUNTRY DOMAINS. THIS
 * MODULE IS TESTED AND IMPLEMENTED USING INDIAN CELLULAR NETWORKS LIKE AIRTEL AND BSNL.
 * THIS MODULE WILL ALSO USE AN ADDITIONAL DRIVER PACKAGE KNOWN AS GNOKII OR XGNOKII. PLEASE MAKE SURE THAT YOU HAVE IT INSTALLED.
 *
 *	MODULE NAME		: OmniPresence Short Message Notifier
 *	AUTHORS			: Saurajeet Dutta, Jyoti Prakash Nath, Purushottam, Rahul Bose
 *	MAILING  		: <vention.gothics@gmail.com>,<jp2018@gmail.com>, <purushottam.prince@gmail.com>, <rahul2016@gmail.com>
 *	LICENSE			: Freely Redistributable ("GPL v2")
 *
 * THIS SOFTWARE OR ANY OF ITS PARTS COMES WITH NO WARRANTY OR SUCH. THOUGH THIS SOFTWARE HAS BEEN TESTED ON MANY CONFIGURATIONS,
 * WE WONT BE HELD RESPONSIBLE FOR ANY KIND OF DAMAGE CAUSED TO YOUR SYSTEM DUE TO USE OF THIS SOFTWARE.
 */
 /*
//GLIBC HEADER INCLUSIONS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
//END HEADER INCLUSIONS
*/

int notifyMain(void)
{	//MYSQL CONNECTION VARIABLES
		MYSQL * connectionPresentList;
		MYSQL * connectionAbsentList;
		MYSQL_RES * resultPresentList;
		MYSQL_RES * resultAbsentList;
		MYSQL_ROW rowsPresentList;
		MYSQL_ROW rowsAbsentList;
	//END MYSQL CONNECTION VARIABLES

	//LOCAL VARIABLES
		char queryPresentList[30] = "SELECT * FROM presentList";
		char queryAbsentList[30] = "SELECT * FROM absentList";
		char command[300] = "echo \"omniPresence Message Center: Dear ";
		char commandbck[300] = "echo \"omniPresence Message Center: Dear ";
		char gnokiicommand[50] = " | gnokii --sendsms ";
		char gnokiicommandbck[50] = " | gnokii --sendsms ";
		char fileCommand[50] = " >> sms.txt";
		char * server = "localhost";
		char * database = "omniPresence";
		register int ctr = 0;
		int retCode = 0;
		char sigsegvHandler[50] = "";
		char ch = 'y';
	//END LOCAL VARIABLES

	//PROCEEDING FOR CONNECTION
		printf("SENDSMS:: Connecting to the database....");
		connectionPresentList = mysql_init (NULL);
		connectionAbsentList = mysql_init (NULL);
		if (!mysql_real_connect(connectionPresentList, server ,user, password, database,0, NULL, 0))
		{	printf ("\nSENDSMS:: Unable to connect to the database: pl: %s\n", mysql_error(connectionPresentList));
			printf ("\nSENDSMS:: Shutting down to prevent loss of data\n");
			return 1;
		}
		if (!mysql_real_connect (connectionAbsentList, server, user, password, database, 0, NULL, 0))
		{	printf ("\nSENDSMS:: Unable to connect to the database: al: %s\n", mysql_error(connectionAbsentList));
			printf ("\nSENDSMS:: Shutting down notifier to prevent loss of data. Please try again later.\n");\
			return 1;
		}
		printf("connected\n");
	//CONNECTED

	printf ("SENDSMS:: Do you want to actually send sms or redirect sms to file (sms.txt) [Y(sendsms)/N(file)] :: ");
	ch = getchar();
	ch = getchar();
	if (ch == 'y' || ch == 'Y')
	{	//PARSING QUERY AND GETTING RESULTS FROM THE ABSENT LIST
         	       retCode = mysql_query(connectionAbsentList, queryAbsentList);
	                if (retCode == 1)
	                {       printf("SENDSMS:: ERROR: Query doesnot reflect a value. %s\n", mysql_error(connectionAbsentList));
	                }
	                resultAbsentList = mysql_use_result(connectionAbsentList);
	                if (resultAbsentList == NULL)
	                {       printf ("SENDSMS:: ERROR: Result returned is null. Please check the database consistency.\n");
	                }
	        //END PARSING VALUES FROM THE ABSENT LIST TABLE
	
	        //ACCESS DATABASE AND SEND SMS TO ABSENTEES
	        while((rowsAbsentList = mysql_fetch_row(resultAbsentList)) != NULL)
	        {       //CREATE QUERY
				//printf ("SENDSMS:: %s, %s, %d\n", rowsAbsentList[0], rowsAbsentList[2], strlen(rowsAbsentList[0]));
				sprintf (sigsegvHandler, "%s ", rowsAbsentList[2]);
	                        strcat (command, sigsegvHandler);
	                        strcat (command, ", You were absent on ");
				//printf ("here");
				sprintf (sigsegvHandler, "%s ", rowsAbsentList[1]);
	                        strcat (command, sigsegvHandler);
	                        strcat (command, ". Please do not delete this message until next of the month. ");
	                        strcat (command, "Thankyou\"");
				//printf ("here");
				sprintf (sigsegvHandler, "%s ", rowsAbsentList[0]);
	                        strcat (gnokiicommand, sigsegvHandler);
	                        strcat (command, gnokiicommand);
	                //END QUERY CREATION
	                printf ("SENDSMS:: SMS QUERY: %s\n", command);
	                retCode = system (command);
	                strcpy (command, commandbck);
	                strcpy (gnokiicommand, gnokiicommandbck);
	        }
		printf ("\n\nSENDSMS:: SMS SENT TO ABSENT LIST, PROCEEDING TO PROCESS PRESENT LIST IN 5 SECONDS.\n\n");
		sleep(5);

		//PARSING QUERY AND GETTING RESULTS FROM THE PRESENT TLIST
			retCode = mysql_query(connectionPresentList, queryPresentList);
			if (retCode == 1)
			{	printf("SENDSMS:: ERROR: Query doesnot reflect a value. %s\n", mysql_error(connectionPresentList));
			}
			resultPresentList = mysql_use_result(connectionPresentList);
			if (resultPresentList == NULL)
			{	printf ("SENDSMS:: ERROR: Result returned is null.\n");
			}
		//END PARSING VALUES FROM THE PRESENT LIST TABLE
		
		//ACCESS DATABASE AND SEND SMS TO PRESENT EMPLOYEES
		while((rowsPresentList = mysql_fetch_row(resultPresentList)) != NULL)
		{	//CREATE QUERY
				strcat (command, rowsPresentList[2]);
				strcat (command, ", Your Attendance for ");
				strcat (command, rowsPresentList[1]);
				strcat (command, " has been marked Present. Please do not delete this message until next of the month. ");
				strcat (command, "Thankyou\"");
				strcat (gnokiicommand, rowsPresentList[0]);
				strcat (command, gnokiicommand);
			//END QUERY CREATION
			printf ("SENDSMS:: SMS QUERY: %s\n", command);
			retCode = system (command);
			strcpy (command, commandbck);
			strcpy (gnokiicommand, gnokiicommandbck);
		}
	
		mysql_free_result(resultPresentList);
		mysql_free_result(resultAbsentList);
		printf ("SENDSMS :: SMS Sent to Present Employees.\n");
	}
	else
	{	printf ("SENDSMS:: Redirect to file selected.\n");
	}
	//COLLECT AND SHUTDOWN SYSTEM
	printf("SENDSMS:: System is quitting.\n");
	mysql_close (connectionAbsentList);
	mysql_close(connectionPresentList);
	return 0;
}
