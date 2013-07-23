/*
#include<stdio.h>
#include<string.h>
#include<mysql/mysql.h>
*/
void MarkTA(char rnadin[], int ta, char Day[], char Year[])
{
	char query[1024]="update attendanceSheet",strTA[10]="";
        MYSQL *connection_AS_TA_MTA;
        MYSQL_RES *res;
        MYSQL_ROW row;
        int t;

	sprintf(strTA,"%d",ta);
        strcat(query,Day);
        strcat(query,Year);
	strcat(query," set Totalattend='");
	strcat(query,strTA);
	strcat(query,"' where rNAD='");
	strcat(query,rnadin);
	strcat(query,"'");

        connection_AS_TA_MTA=mysql_init(NULL);
        if(!mysql_real_connect(connection_AS_TA_MTA,"localhost","root","omni","omniPresence",0,NULL,0))
        {
                printf("\ntotalAttendance::Error in connection...............");
                return ;
        }

        t=mysql_query(connection_AS_TA_MTA,query);
        if(t)
        {
	        printf("\ntotalAttendance::Error in query %s",mysql_error(connection_AS_TA_MTA));
		mysql_close(connection_AS_TA_MTA);
                return ;
        }
	mysql_close(connection_AS_TA_MTA);
	return;
}

void totalAttendance(char day[], char year[])
{
	char retstr[1024]="",query[1024]="select * from attendanceSheet",ch=' ',rnad[50]="";
	MYSQL *connection_AS_TA;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t,TA,count=0;

	strcat(query,day);
	strcat(query,year);
	
	connection_AS_TA=mysql_init(NULL);
	if(!mysql_real_connect(connection_AS_TA,"localhost","root","omni","omniPresence",0,NULL,0))
	{
		printf("\ntotalAttendance::Error in connection...............");
		return ;
	}
	
	t=mysql_query(connection_AS_TA,query);
	if(t)
	{
		printf("\ntotalAttendance::Error in query %s",mysql_error(connection_AS_TA));
		mysql_close(connection_AS_TA);
		return ;
	}
	
	res=mysql_use_result(connection_AS_TA);
	while(row=mysql_fetch_row(res))
	{
		TA=0;
		strcpy(rnad,row[0]);
		for(count=1;count<32;count++)
		{
			if(row[count])
			{	strcpy(retstr,row[count]);
				ch=retstr[0];
				if(ch=='p'||ch=='P')
					TA++;
			}
		}	
		
		MarkTA(&rnad[0],TA,&day[0],&year[0]);
		
	}
	
	mysql_close(connection_AS_TA);
	return ;
}

/*
int main()
{
	char dayin[10]="03", yearin[10]="09";
	totalAttendance(&dayin[0],&yearin[0]);
	return 0;
}*/
