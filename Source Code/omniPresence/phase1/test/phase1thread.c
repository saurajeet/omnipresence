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
#include <pthread.h>
//END INCLUSIONS

void *phase1main(void *ptr);
void *realtime (void *ptr);

struct info_MAC
{	char MAC[19];
	char date[100];
	char TimeOfEntry[100];
}mac_entry_info;

struct Sequence_Checker
{ 	char l_s_date[100];
	char l_s_time[100];
}check;

main()
{
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int iret1, iret2;

	//Create independent each of the will execute function

	iret1 = pthread_create (&thread1, NULL, phase1main, (void *) message1);
	iret2 = pthread_create (&thread2, NULL, realtime, (void *) message2);

	//Wait till all the threads are complete. Unless we
	// wait we run the risk of executing an exit which ill terminate
	// the process and all threads before the threads have completed.

	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	printf ("\nThread 1 returns : %d\n", iret1);
	printf ("\nThread 2 returns : %d\n", iret2);

	return 0;
}

void *phase1main (void *ptr)
{	printf ("BTSER:: Starting the omniPresence RFID Bluetooth Server...");
	//login_window();
 	inquiry_info *ii = NULL;		// STORES THE INFO RETRIEVED BY DEVICE DISCOVERY, NORMALLY IT IS DYNAMICALLY ALLOCATED
	int max_rsp, num_rsp;			// MAXIMUM NUMBER OF REPONSES TO BE DETECTED IN THE ENQUIRY
	int dev_id ;				// DEVICE HANDLE RETURNED FROM O/S
	int sock; 				// SOCKET DESCRIPTOR RETURNED TO THE RADIO FREQUENCY LAYER
	int len;				// VALUE MULTIPLIED BY 1.24 THAT RETURNS THE TOTAL TIME FOR SCANNING 
	int flags;				// TO SET THE DEVICE FLUSHING THE CONTENTS OF PREVIOUS DISCOVERY
	int i;					// COUNTER VARIABLE
	char addr[19] = { 0 };			// FOR STORING THE BLUETOOTH MAC ADDRESS
	int  Detection = 0;
	int info = 0;				//INFO VARIABLE TO DETECT AND INITIATE SHUTDOWN SEQUENCE
	
	MYSQL *conn;				// DATABASE CONNECTION OBJECT
	MYSQL_RES * result;			// DATABASE RESULT VARIABLE
	MYSQL_RES * res;
	MYSQL_ROW row;				// DATABASE ROW SELECTION
	MYSQL_ROW row1; 	

	char buf[100];                          // FOR STORING TIME & DATE RETURNED BY STRFTIME() 
	time_t now, then,duration;		// TIME VARIABLES                             
	struct tm *cur_time,*tm;		// TIME STRUCTURES
        char * server = "localhost";		// MYSQL SERVER HOSTNAME
	char  user[5]  = "root" ;	        // MYSQL USER LOGIN
	char  password[5] = "omni";		// MYSQL PASSWORD
	char  *database="omniPresence";		// MYSQL DATABASE NAME
	int   retCode = 0;			// TEMPORARY VARIABLE
	
	printf ("done\n");
       
	/*OPENING THE CONNECTION WITH MYSQL SERVER*/
	printf ("BTSER:: Connecting to MySQL Server. Please Be Patient.....");
	conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{	printf ("\nBTSER:: See Whether Connection to MySQL server exists: %s\n", mysql_error(conn));
		info = 1;
		goto shutdown_RFID;
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
		info = 2;
		goto shutdown_RFID;
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

void *realtime (void *ptr)
{	int i = 0;
	MYSQL * connection;
	char * server = "localhost";            // MYSQL SERVER HOSTNAME
	char * user = "root";                   // MYSQL USER LOGIN
	char * password = "omni";               // MYSQL PASSWORD
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
                return 1;
        }

        printf ("connected\n");

       // CONNECTION OPENED

	if (mysql_query(connection, query))
        {       fprintf(stderr, "REALTIMER:: %s\n", mysql_error(connection));
                return 1;
        }
        strcpy (query, querycp);

	//printf("REALTIMER:: Syncronizing   :");	
	for (i=0;i<180;i++)
	{	system("sleep 1");	
		seconds++;
		printf(":");
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
                                return 1;
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
                                return 1;
                        }
			seconds=0;
		}
	}
	mysql_close(connection);	// CLOSING THE MYSQL CONNECTION .
	return 0;
}
