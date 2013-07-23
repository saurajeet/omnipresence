#ifndef _TABLECREATOR_H_
	#define _TABLECREATOR_H_

//#include "sheetCreater.h"
int crTablmain()
{	int retCode = 0;
	char month[3] = "";
	char yearAS[3] = "";
	printf("SHEETCRT:: Please Enter Month For Which attendanceSheet is to be created:");
	scanf ("%s",&month);
	printf("SHEETCRT:: Please Enter Year for which attendanceSheet is to be created:");
	scanf ("%s", &yearAS);
	retCode=attendanceSheetCreater(month, yearAS);
	return 0;
}

#endif //TABLECREATOR_H_
