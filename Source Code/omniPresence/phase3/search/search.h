#ifndef SEARCH_H_
	#define SEARCH_H_

MYSQL_RES * search(char searchitem[] , int rowno, char tablename[])
{
	//printf("SEARCHMOD:: %s,%d,%s\n ", searchitem, rowno, tablename);
	int i,t;
	char *server  = "localhost";
	char query1[1024] = "describe ";
	char query2[1024] = "select * from ";
	char colname[50] = " ";
	char *db = " ";
	char *dbase = "omniPresence";
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, dbase,0,NULL,0))
	{	printf("SEARCHMOD:: Error in Connection... %s\n",mysql_error(conn));	//close program
		exit (1);
	}
	/*else
		printf("SEARCHMOD:: Connected...\n");
	*/					//creates query1.
	strcat(query1,tablename);
	
	//printf("SEARCHMOD:: \t\t\tQuery1: %s \n",query1);
	t=mysql_query(conn,query1);
	if(t)
		printf("SEARCHMOD:: Error making Query...%s\n",mysql_error(conn));
	else
	//	printf("SEARCHMOD:: Query Successful...\n");
	result=mysql_use_result(conn);
	
	for(i=0;i<=rowno;i++)
	{	row=mysql_fetch_row(result);	//traverses in rows.
	}
	if (rowno == 0)
		i = 2;
	strcpy(colname,row[i-2]);
	//printf("SEARCHMOD:: \t\t\tUse colname %s\n", colname);

	mysql_close(conn);
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, "localhost", "root", "omni", "omniPresence", 0, NULL, 0))
		printf ("SEARCHMOD:: A Connection error has occured.. \n");			

	strcat(query2,tablename);
	strcat(query2," WHERE ");
	strcat(query2,colname);
	strcat(query2," = '");
	strcat(query2,searchitem);
	strcat(query2,"'");			
	//printf("SEARCHMOD:: \t\t\tQuery2: %s \n",query2);
	t=mysql_query(conn,query2);
	if(t)
	{
		printf("SEARCHMOD:: Error making Query...%s\n",mysql_error(conn));
		return NULL;
	}
	//printf("SEARCHMOD:: Query Successful...\n");
	ret=mysql_use_result(conn);
	MYSQL_ROW dummyRow = mysql_fetch_row(ret);
	if (dummyRow == NULL)
		return NULL;
	//mysql_close(conn);
	resultDetails=dummyRow;
	//printf("SEARCHMOD:: %s %s\n", dummyRow[0],dummyRow[1]);
	return ret;
}
#endif //SEARCH_H_
