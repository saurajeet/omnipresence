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

#ifndef _PHASE1_H_
	#define _PHASE1_H_

struct info_MAC
{	char MAC[19];
	char date[100];
	char TimeOfEntry[100];
}mac_entry_info;

struct Sequence_Checker
{ 	char l_s_date[100];
	char l_s_time[100];
}check;

int phase1main()
{	
	printf ("BTSER:: Starting the omniPresence RFID Bluetooth Server...");
	login_window();
 	inquiry_info *ii = NULL;		// STORES THE INFO RETRIEVED BY DEVICE DISCOVERY, NORMALLY IT IS DYNAMICALLY ALLOCATED
	int max_rsp, num_rsp;			// MAXIMUM NUMBER OF REPONSES TO BE DETECTED IN THE ENQUIRY
	int dev_id ;				// DEVICE HANDLE RETURNED FROM O/S
	int sock; 				// SOCKET DESCRIPTOR RETURNED TO THE RADIO FREQUENCY LAYER
	int len;				// VALUE MULTIPLIED BY 1.24 THAT RETURNS THE TOTAL TIME FOR SCANNING 
	int flags;				// TO SET THE DEVICE FLUSHING THE CONTENTS OF PREVIOUS DISCOVERY
	int i;					// COUNTER VARIABLE
	char addr[19] = { 0 };			// FOR STORING THE BLUETOOTH MAC ADDRESS
	int  Detection = 0;
	
	MYSQL *conn;				// DATABASE CONNECTION OBJECT
	MYSQL_RES * result;			// DATABASE RESULT VARIABLE
	MYSQL_RES * res;
	MYSQL_ROW row;				// DATABASE ROW SELECTION
	MYSQL_ROW row1; 	

	char buf[100];                          // FOR STORING TIME & DATE RETURNED BY STRFTIME() 
	time_t now, then,duration;		// TIME VARIABLES                             
	struct tm *cur_time,*tm;		// TIME STRUCTURES
        char * server = "localhost";		// MYSQL SERVER HOSTNAME
	char  user[5] ;			        // MYSQL USER LOGIN
	char  password[5] ;			// MYSQL PASSWORD
	char  *database="omniPresence" ;	// MYSQL DATABASE NAME
	int   retCode = 0;			// TEMPORARY VARIABLE
	
	printf ("done\n");
       
	/*OPENING THE CONNECTION WITH MYSQL SERVER*/
	printf ("BTSER:: Connecting to MySQL Server. Please Be Patient.....");
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, uname, pswd, database, 0, NULL, 0))
	{	printf ("\nBTSER:: See Whether Connection to MySQL server exists: %s\n", mysql_error(conn));
		return 1;
	}
	printf ("connected\n");
	/*CONNECTION OPENED*/

	char query[1024] = "insert into scanDump (mAC, time, date) values ('"; 	// SQL QUERY FOR DUMPING MAC 
 	char querycp[1024] = "insert into scanDump (mAC, time, date) values('";	// SQL QUERY 
	char steal[50] ="select * from timestore";	                        // SQL QUERY FOR RETREIVING DATA ABT TIME	
	char feed[100] ="insert into lastDumpSession values ('"; 	        // SQL QUERY
	char feedcp[100] ="insert into lastDumpSession values('"; 		// SQL QUERY
        char lastSession[100]="select date,time from lastDumpSession"; 
	char stealnow[100]="select sl from scanDump where time='";             	// SQL QUERY
	
	/*PROCEEDING WITH SERVER ACTIVITIES*/
	time(& now);                                                            // READING SYSTEM TIME
        cur_time=localtime(& now );
      	then=now + (60);
        time(& duration);
        (void) strftime((mac_entry_info.TimeOfEntry),sizeof (mac_entry_info.TimeOfEntry),"%H:%M",cur_time);
	(void) strftime((mac_entry_info.date),sizeof (mac_entry_info.date),"%a,%d,%m,%Y",cur_time);
       	printf("BTSER:: SYSTEM Date :%s\n",mac_entry_info.date);
	printf("BTSER:: SYSTEM Time :%s\n",mac_entry_info.TimeOfEntry);
	
	/*READING LAST DUMP SESSION TIME & DATE FROM DATABASE*/
	printf ("BTSER:: Checking system date and time.\n");
	if(mysql_query(conn,lastSession))
	{	
		fprintf(stderr,"BTSER:: %s\n",mysql_error(conn));
		return 2;
	}
	res=mysql_use_result(conn);
	while((row1=mysql_fetch_row(res))!=NULL)
	{       strcpy(check.l_s_date,row1[0]);
		strcpy(check.l_s_time,row1[1]);
	}
	printf("BTSER:: LAST SESSION :: Date %s\n ",check.l_s_date);	
	printf("BTSER:: LAST SESSION :: Time %s\n",check.l_s_time);
        
	if(strcmp(mac_entry_info.date,check.l_s_date)<0)
	{	
		printf("BTSER:: System Date has been changed, the program will not continue, shutting down server\n");
		system("kill $(pidof realtimer");
		mysql_close(conn);
		return 3;
	}
	else if(strcmp(mac_entry_info.date,check.l_s_date)==0)
	{	
		if(strcmp(mac_entry_info.TimeOfEntry,check.l_s_time)<0)
		{
			printf("BTSER:: System TIME has been changed, the program will not continue, shutting down server\n");
	                system("kill $(pidof realtimer)");
			mysql_close(conn);
        		return 3;
		}
	}
	
	dev_id = hci_get_route(NULL);		// GETTING DEVICE HANDLE FROM O/S
	sock = hci_open_dev( dev_id );		// GETTING SOCKET FROM THE O/S
	if (dev_id < 0 || sock < 0)
	{ 	printf ("BTSER:: Please see whether bluetooth service exists and then restart server.\n");
		return 4;
	}
	len = 8;
	max_rsp = 255;
	
	/*STARTING BLUETOOTH SCAN*/          
	while(difftime(duration,now)<60)               // SCAN FOR 1 MINUTE
        {	flags = IREQ_CACHE_FLUSH;		// FLUSH OUT THE REQUEST QUEUE
		ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
		num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
		if( num_rsp < 0) perror("hci_inquiry");

		for (i = 0; i < num_rsp; i++)
		{ 	
			Detection=1;
			ba2str(&(ii+i)->bdaddr, addr);
			printf("BTSER:: %s \n", addr);
												
			if (mysql_query(conn, steal))
                        {       fprintf(stderr, "BTSER:: %s\n", mysql_error(conn));
                                return 2;
                        }
                        result = mysql_use_result(conn);
			while ((row = mysql_fetch_row(result)) != NULL)
			{	
				strcpy(mac_entry_info.TimeOfEntry,row[0]);
				strcat(mac_entry_info.TimeOfEntry,":");
				strcat(mac_entry_info.TimeOfEntry,row[1]);
				printf("BTSER:: %s\t\n", mac_entry_info.TimeOfEntry);
		        }   
			/* CREATE A RUNTIME SQL QUERY */
			strcat (query, addr);
			strcat (query, "','");
			strcat (query, mac_entry_info.TimeOfEntry);
			strcat (query, "','");
			strcat (query, mac_entry_info.date);
			strcat (query, "')");
			if (mysql_query(conn, query))
			{	fprintf(stderr, "BTSER:: %s\n", mysql_error(conn));
				return 2;
			}
			strcpy (query, querycp);
		}
		
		free( ii );
		time(& duration);
	}

	if(Detection==0)                                 //Executes if no mobile is detected during whole scan session                        
	{	
		printf("BTSER:: No Bluetooth Mobiles Detected \n Shutting down Server \n");
		system ("kill $(pidof realtimertest)");
		return 0;
	}
	
	strcat(stealnow,mac_entry_info.TimeOfEntry);
        strcat(stealnow,"'");
        //printf("\n%s\n",stealnow);
	
	if (mysql_query(conn,stealnow))
	{	
		fprintf(stderr, "BTSER:: %s\n",mysql_error(conn));
		return 2;
	}
	
	result=mysql_use_result(conn);
	while ((row = mysql_fetch_row(result)) != NULL)		// creating query for last update session
        {      	strcpy (feed,feedcp);
                //strcat(feed,row[0]);
                //strcat(feed,"','");
                strcat(feed,mac_entry_info.date);
                strcat(feed,"','");
                strcat(feed,mac_entry_info.TimeOfEntry);
                strcat(feed,"','");
                strcat (feed, row[0]);
                strcat (feed, "')");
        }

	if (mysql_query(conn, feed))
        {      
		fprintf(stderr, "BTSER:: %s\n",mysql_error(conn));
                return 2;
        }
	
	printf ("BTSER:: Shutting down Server...");
	close( sock );
	mysql_close(conn);
	system ("kill $(pidof realtimertest)");
	printf ("done\nPlease run the omniPresence Attendence Marker for recording the attendance\n");
	return 0;
}

#endif //_PHASE1_H_
