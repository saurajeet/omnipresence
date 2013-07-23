#ifndef DATEXTRACTER_H_
	#define DATEXTRACTER_H_
void selectSheet(char date[])
{	int i,j;
	for(i=4,j=6;i<=5;i++,j++)
	{
		colName[j]=date[i];
	}
	for(i=7,j=15;i<=18;i++,j++)
	{
		if(i==9)
			i+=3;			// to escape ',' in date[]
		attendanceSheet[j]=date[i];
	}
	printf("DTEXTMOD:: \t SELECT SHEET: %s, COL: %s\n",attendanceSheet,colName);
}
#endif //DATEXTRACTER_H_
