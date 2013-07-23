/* THIS PROGRAM IS MADE FOR AUTOMATICALLY DETECT AND MARKING PRESENCE OF DEVICES WITHIN A BLUETOOTH SPACE
 * 	AUTHOR		: Saurajeet Dutta, Amit Abhinav Singh, Anurag Pandey, Jyoti Prakash Nath
 *	CONSULTANCY	: <vention.gothics@gmail.com>, <amitabhaDJ@sify.com>, <anuragbuddy@gmail.com>, <jp2018@gmail.com>
 *	PROGRAM	NAME	: OmniPresence
 *	OCCUPATION	: Just a student man!
 * 	INSTITUTION	: Birla Institute Of Technology, Lalpur, Ranchi - 834001
 *	COMMUNITY	: Research and Development Wing
 *	TEAM		: Advanced C/C++ Research Team
 *	iNsPirAtion	: MY TEAM Members
 *	TakenAbackBy	: My Typing Speed! (Only 300 cps)
 * 	LICENSE		: Freely Redistributable (FREE) ("GPL v2")
 * WE DONOT COVER ANY RESPONSIBILITY OF HARM CAUSED BY THE USE OF THIS TECHNOLOGY, THOUGH BOUNDS OF THIS S/W HAS BEEN TESTED BEFORE
 * DEPLOYMENT. FOR ANY LEGAL ACTIONS, PROCEEDINGS SHOULD BE IN COURTS OF RANCHI ONLY!
 */
/*
//HEADER INCLUSIONS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <mysql/mysql.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <limits.h>
//END INCLUSIONS
*/

#ifndef _REALTIME_H_
	#define _REALTIME_H_

void *realtime (void *ptr)
{	int i = 0;
	MYSQL * connection;
	char * server = "localhost";            // MYSQL SERVER HOSTNAME
	//char * user = "root";                   // MYSQL USER LOGIN
	//char * password = "omni";               // MYSQL PASSWORD
	char * database = "omniPresence";       // MYSQL DATABASE NAME
	int retCode = 0;                        // TEMPORARY VARIABLE
	char query[256] = "update timestore set hr = '";
	char querycp[256] = "update timestore set hr = ";
	int temp1=0,temp2=0;
	int hour ;				//TO STORE CURRENT HOUR .
	int minutes ;				//TO STORE CURRENT MINUTE . 
	int seconds ;				//TO STORE CURRENT SECONDS .
	char hourC[2]=""; 			//TO STORE HOUR IN STRING .
	char minutesC[2]="";			//TO STORE MINUTES IN STRING .
	char tempC1,tempC2;
	time_t curTime;
	struct tm * timevar;
	int info = 0;

	/*GETTING THE CURRENT SYSTEM TIME*/

	time(&curTime);
	timevar = localtime(&curTime);
        hour=(*timevar).tm_hour;
	minutes=(*timevar).tm_min;
	seconds=(*timevar).tm_sec;
	
	/*
        	CONVERTING INTEGER TO a STRING.
                                        	*/
	temp1=hour/10;
        temp2=hour%10;
        int n1=48+temp1,n2=48+temp2;
        tempC1=((n1));	
	tempC2=((n2));
	hourC[0]=tempC1;
	hourC[1]=tempC2;
	temp1=minutes/10;
	temp2=minutes%10;
	n1=48+temp1;
	n2=48+temp2;
	minutesC[0]=n1;
	minutesC[1]=n2;
	
	/* 	CONSTRUCTING A QUERY 	*/
	
	strcat(query, hourC);
	strcat(query," ', min = '");
	strcat(query,minutesC);
	strcat(query,"'");

	//CONNECTING PROCEDURE WITH MYSQL SERVER .

	connection = mysql_init(NULL);

	//OPENING THE CONNECTION WITH MYSQL SERVER .

        printf ("\nREALTIMER:: Connecting to MySQL Server. Please Be Patient.....");

        connection = mysql_init(NULL);

        if(!mysql_real_connect(connection, server, user, password, database, 0, NULL, 0))
        {       printf ("\nREALTIMER:: See Whether Connection to MySQL server exists\n");
                info = 1;
		goto shutdown_Realtimer;
        }

        printf ("connected\n");

       // CONNECTION OPENED

	if (mysql_query(connection, query))
        {       fprintf(stderr, "REALTIMER:: %s\n", mysql_error(connection));
                info = 2;
		goto shutdown_Realtimer;
        }
        strcpy (query, querycp);

	//printf("REALTIMER:: Syncronizing   :");	
	for (i=0;i<180 && (shutdown_realtimer == 0);i++)
	{	system("sleep 1");	
		seconds++;
		//printf(":");
		/*
		UPDATING THE VALUE OF HOUR AFTER THE MINUTES BECOME 60.            */
		if (minutes==59 && seconds==59)
                {
                        hour=hour++;
                        temp1=hour/10;
                        temp2=hour%10;
                        n1=(48+temp1),n2=(48+temp2);
                        tempC1=((n1));
                        tempC2=((n2));
                        hourC[0]=tempC1;
                        hourC[1]=tempC2;
                        strcpy(query,"update timestore set hr ='");
                        strcat(query,hourC);
                        strcat(query,"'");
                        if (mysql_query(connection, query))
                        {       fprintf(stderr, "REALTIMER:: %s\n", mysql_error(connection));
                                info = 2;
				goto shutdown_Realtimer;
                        }
			
		}
		if (seconds==59)
		{   
		/*
			UPDATING THE MINUTES COLOUMN OF THE TABLE TIMESTORE
			WHEN SECONDS BECOMES 60.
		*/
			minutes++;
			minutes=minutes%60;
			temp1=minutes/10;
        		temp2=minutes%10;
		        n1=(48+temp1);
		        n2=(48+temp2);
		        minutesC[0]=n1;
	        	minutesC[1]=n2;
		        strcpy(query,"update timestore set ");
			strcat(query,"min='");
			strcat(query,minutesC);
			strcat(query,"'");
			if (mysql_query(connection, query))
                        {       fprintf(stderr, "REALTIMER:: %s\n", mysql_error(connection));
                                info = 2;
				goto shutdown_Realtimer;
                        }
			seconds=0;
		}
	}
	shutdown_Realtimer:
	mysql_close(connection);	// CLOSING THE MYSQL CONNECTION .
	return ;
}

#endif //_REALTIME_H_
