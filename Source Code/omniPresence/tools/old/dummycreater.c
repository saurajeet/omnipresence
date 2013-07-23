#include<stdio.h>
#include<mysql/mysql.h>
#include<stdlib.h>
#include<string.h>
#include"sheet/sheetCreater.h"
int main()
{	int retCode = 0;
	char month[3] = "";
	printf("Please Enter Month For Which attendanceSheet is to be created:");
	scanf ("%s",&month);
	printf("RETCODE = %d",  retCode=attendanceSheetCreater(month,"09"));
	return 0;
}
