char attendanceSheet[20] = "attendanceSheet0309";
int insert_rnad_in_attend()
{
	MYSQL *conn;
	char query[1024]="insert into ",tempstr;
	int t;
	
	strcat(query,attendanceSheet);
	strcat(query," (rNAD) values('");
	strcat(query,rnad);
	strcat(query,"')");
	printf("\nompi::QUERY ...%s",query);

	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,"localhost","root","omni","omniPresence",0,NULL,0))

	{
		printf("\nompi::Error in connection......\n");
		return 1;
	}
	
	printf("\nompi::Conected....................................................\n");
	t=mysql_query(conn,query);
	if(t)
		printf("\nompi::Error in query, %s\n",mysql_error(conn));
		
	else 
		printf("\nompi::Query executed successfully\n");

	mysql_close(conn);
	return 0;
}
