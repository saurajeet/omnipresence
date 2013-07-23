#ifndef _SHOWSTATUS_H_
	#define _SHOWSTATUS_H_	
/*
//INCLUDE GLIBC HEADERS
#include<mysql/mysql.h>
#include<stdio.h>
#include<string.h>
//END INCLUSION*/

char attendanceSheet_SS[20]="attendanceSheet";
char showStatus(char empid[],char date[])
{	char * server = "localhost";
	char retstr[1024]="",query[1024]="select workersDB.name, attend",ch=' ';
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t;

	strcat(query,date);
	strcat(query," from ");
	strcat(query,attendanceSheet);
	strcat(query,",workersDB  where workersDB.empID='");
	strcat(query,empid);
	strcat(query,"' and workersDB.rNAD=");
	strcat(query,attendanceSheet);
	strcat(query,".rnad ;");
	printf("\nSHOWSTAT:: QUERY...%s\n",query);

	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, "omniPresence", 0, NULL, 0))
	{	printf("\nSHOWSTAT:: Error in connection...............");
		return ch;
	}
	
	t=mysql_query(conn,query);
	if(t)
	{
		printf("\nSHOWSTAT:: Error in query");
		return ch;
	}
	res=mysql_use_result(conn);
	row=mysql_fetch_row(res);
	if(row)
	{
		strcpy(retstr,row[1]);
		ch=retstr[0];
	}
	printf ("SHOWSTAT:: Selected employee is %s\n", row[0]);
	
	mysql_close(conn);
	return ch;
}

int showstatusMain()
{
	char at_po ='b';
	char eID_SS[10] = "";
	char dateSTR_SS[3] = "";
	int date_SS = 0;
	char ip_SS[6] = "";
	printf ("SHOWSTAT:: Please input the month and year (e.g. 0209 for Feb 2009) :: ");
	scanf ("%s", &ip_SS);
	strcat (attendanceSheet_SS, ip_SS);
	printf ("SHOWSTAT:: Please input the date for which you would like to see the status (e.g 1 for 1st) :: ");
	scanf  ("%d", &date_SS);
	if (date_SS <= 9)
		sprintf (dateSTR_SS , "0%d", date_SS);
	else
		sprintf (dateSTR_SS, "%d", date_SS);
	printf ("SHOWSTAT:: Please enter the employee id for whom you want to see the attendance :: ");
	scanf ("%s", &eID_SS);
	at_po = showStatus(eID_SS, date_SS);
	printf("SHOWSTAT:: Status:%c\n",at_po);
	return 0;
}
#endif //_SHOWSTATUS_H_
