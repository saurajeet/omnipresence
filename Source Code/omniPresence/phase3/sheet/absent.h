#ifndef _ABSENT_H_
	#define _ABSENT_H_
/*
#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
*/
//This module will check for those employees who are absent on a particular day and will make entries in the absent list

void MakeAbsList(char* rnad, char* absday, char* absmon, char* absyear)
{
	char query[1024]="select name, phno from workersDB where rNad='",name[50]="",phno[20]="";
        MYSQL *connection_AL;
	MYSQL_RES *result_AL;
	MYSQL_ROW row_AL;
        int t;
	char * server = "localhost";
        strcat(query,rnad);
	strcat(query,"'");
        connection_AL=mysql_init(NULL);
        if(!mysql_real_connect(connection_AL, server, user, password, "omniPresence",0,NULL,0))
        {
                printf("ABSLIST:: Error in connection..connection_AL1: %s\n", mysql_error(connection_AL));
                return ;
        }
	
	//printf("\nompi::query2=%s",query);
        t=mysql_query(connection_AL,query);
        if(t)
        {
                printf("ABSLIST:: Error in query::connection_AL1: %s\n", mysql_error(connection_AL));
		mysql_close(connection_AL);
                return ;
        }
	result_AL=mysql_use_result(connection_AL);
	row_AL=mysql_fetch_row(result_AL);
	if(row_AL)
	{
		strcpy(name,row_AL[0]);
		strcpy(phno,row_AL[1]);
	}
	mysql_close(connection_AL);
	t=0;
	strcpy(query,"insert into absentList values('");
	strcat(query,phno);
	strcat(query,"','");
	strcat(query,absday);
	strcat(query,"/");
	strcat(query,absmon);
        strcat(query,"/");
	strcat(query,absyear);
        strcat(query,"','");
	strcat(query,name);
	strcat(query,"')");
	//printf("\nompi::query3=%s",query);
	connection_AL=mysql_init(NULL);
	if(!mysql_real_connect(connection_AL, server, user, password,"omniPresence",0,NULL,0))
        {
                printf("ABSLIST:: Error in connection :connection_AL: %s\n", mysql_error(connection_AL));
                return ;
        }
	t=mysql_query(connection_AL,query);
	if(t)
        {
                printf("ABSLIST:: Error in query::connection_AL, %s\n", mysql_error(connection_AL));
		mysql_close(connection_AL);
                return ;
        }
	mysql_close(connection_AL);
	return;
}

void AbsentCheck(char* day, char* mon, char* year)
{
	char query[1024]="select attend",tempstr[50]="",status=' ';
	MYSQL *connection_AC;
	MYSQL_RES *result_AC;
	MYSQL_ROW row_AC;
	int t;
	char * server = "localhost";
	strcat(query,day);
	strcat(query,",rNAD from ");
	strcat(query,"attendanceSheet");
	strcat(query,mon);
	strcat(query,year);
	//printf("\nompi::query1=%s",query);

	connection_AC=mysql_init(NULL);
	if(!mysql_real_connect(connection_AC, server, user, password,"omniPresence",0,NULL,0))
	{
		printf("ABSLIST:: Error in connection :connection_AC: %s\n", mysql_error(connection_AC));
		return ;
	}
	
	t=mysql_query(connection_AC,query);
	if(t)
	{
		printf("ABSLIST:: Error in query :connection_AC, %s\n", mysql_error(connection_AC));
		mysql_close(connection_AC);
		return ;
	}

	result_AC=mysql_use_result(connection_AC);
	while(row_AC=mysql_fetch_row(result_AC))
	{
		strcpy(tempstr,row_AC[0]);
		status=tempstr[0];
		strcpy(tempstr,row_AC[1]);
		//printf("\nompi::RNAD=%s\tSTATUS=%c",row_AC[1],status);
		if(status=='a'||status=='A')
			MakeAbsList(&tempstr[0],&day[0],&mon[0],&year[0]);
	}
	
	mysql_close(connection_AC);
	return ;
}
/*
int main()
{
	char dayin[4]="31";
	char monin[4]="03";
	char yearin[4]="09";
	AbsentCheck(&dayin[0],&monin[0],&yearin[0]);
	return 0;
}*/
#endif //_ABSENT_H_
