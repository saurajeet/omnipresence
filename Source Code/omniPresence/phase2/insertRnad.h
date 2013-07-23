//char attendanceSheet_IR[20] = "attendanceSheet0409";
int insert_rnad_in_attend(char generatedRnad[], char attendanceSheet_IR[])
{
	MYSQL *conn;
	char query[1024]="insert into ",tempstr;
	int t;
	char * server = "localhost";	
	strcat(query,attendanceSheet_IR);
	strcat(query," (rNAD) values('");
	strcat(query,generatedRnad);
	strcat(query,"')");
//	printf("\nompi::QUERY ...%s",query);

	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn, server, user, password, "omniPresence",0,NULL,0))

	{
		printf("\nompi::Error in connection......\n");
		return 1;
	}
	
//	printf("\nompi::Conected....................................................\n");
	t=mysql_query(conn,query);
	if(t)
		printf("\nompi::Error in query, %s\n",mysql_error(conn));
		
	else 
//		printf("\nompi::Query executed successfully\n");

	mysql_close(conn);
	return 0;
}
