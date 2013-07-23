#ifndef SHEETCREATER_H_
	#define SHEETCREATER_H_
int attendanceSheetCreater(char month[4],char year[4])
{	char * server = "localhost";
	MYSQL *sheetconn;
	int date=1,t;
	char strDate[4] = "0";
	char query[1024]="CREATE TABLE 	";
	char tableName[25]="attendanceSheet";
	char colName[12]="Attend";
	strcat(tableName,month);
	strcat(tableName,year);
	printf("Table Name:: %s",tableName);
	strcat(query,tableName);
	strcat(query," ( rNAD varchar(16) primary key not null, ");
	strcat(query,"Attend01 varchar(16), Attend02 varchar(16), Attend03 varchar(16), Attend04 varchar(16), ");	
        strcat(query,"Attend05 varchar(16), Attend06 varchar(16), Attend07 varchar(16), Attend08 varchar(16), ");
        strcat(query,"Attend09 varchar(16), Attend10 varchar(16), Attend11 varchar(16), Attend12 varchar(16), ");
        strcat(query,"Attend13 varchar(16), Attend14 varchar(16), Attend15 varchar(16), Attend16 varchar(16), ");
        strcat(query,"Attend17 varchar(16), Attend18 varchar(16), Attend19 varchar(16), Attend20 varchar(16), ");
        strcat(query,"Attend21 varchar(16), Attend22 varchar(16), Attend23 varchar(16), Attend24 varchar(16), ");
        strcat(query,"Attend25 varchar(16), Attend26 varchar(16), Attend27 varchar(16), Attend28 varchar(16), ");
        strcat(query,"Attend29 varchar(16), Attend30 varchar(16), Attend31 varchar(16), Totalattend varchar(5) ) ");
	sheetconn=mysql_init(NULL);
	if(!mysql_real_connect(sheetconn, server, user, password ,"omniPresence",0,NULL,0))
	{		printf("SHEETCREATER:: Error Connecting Database... %s\n",mysql_error(sheetconn));
			exit(1);
	}
	t=mysql_query(sheetconn,query);
	if(t)
		printf("SHEETCREATER:: Error in Query...%s\n",mysql_error(sheetconn));
	else
		printf("SHEETCREATER:: Query Completed... Table created..\n");
	mysql_close(sheetconn);
}
#endif //SHEETCREATER_H_
