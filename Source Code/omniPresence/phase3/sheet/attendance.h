/* THIS PROGRAM IS A PART OF OMNIPRESENCE SOFTWARE. NOT TO BE USED ELSEWHERE. PLEASE DONOT DISSASSEMBLE SOFTWARE COMPONENTS BEFORE PRIOR
 * PERMISSION FROM THE DEVELOPERS
 * 	Name:		Saurajeet Dutta, Jyoti Prakash Nath, Rahul Bose, Purushottam
 * 	MAILING LIST:	<vention.gothics@gmail.com>, <jp2018@gmail.com>, <rahul2016@gmail.com>, <purushottam.prince@gmail.com>
 * 	INSTITUTE:	Birla Institute Of Technology, Extension Centre, Lalpur
 * 	LICENSE:	Freely Redistributable ("GPL V2")
 * THIS PART OF SOFTWARE HAS BEEN DEVELOPED JUST FOR FUN. WE DONOT PROVIDE ANY WARRANTY OR SUCH ON THE SOFTWARE. THOUGH WE HAVE TESTED
 * THE BOUNDS OF THE SOFTWARE ON VARIOUS MACHINES, WE DONOT WANT TO BE HELD RESPONSIBLE FOR ANY DAMAGE CAUSED BY THE USE OF THE SOFTWARE.
 */

#ifndef ATTENDANCE_H_
	#define ATTENDANCE_H_

int makeAttendance (char rNAD[], char date[], char entryTime[], char exitTime[], char status[], char tableName[])
{	//LOCAL VARIABLES
		char queryMakeAttendance[400] = "UPDATE ";
		char attendanceString[15] = "";
 	//END LOCAL VARIABLES

	//CREATE PARTIAL QUERY FOR UPDATION
		strcat (queryMakeAttendance, tableName);
		strcat (queryMakeAttendance, " SET ");
		strcat (queryMakeAttendance, colName);
		strcat (queryMakeAttendance, "= '");
	//END CREATION OF PARTIAL QUERY

	//CHECK FOR ENTRYTIME AND EXIT TIME AND COMPLETE THE QUERY
		strcat (attendanceString, status);
		strcat (attendanceString, ":");
		if (( strcmp(exitTime,"NULL") )== 0 && ( strcmp(entryTime,"NULL") )!=0)
		{	strcat (attendanceString, entryTime);
			strcat (attendanceString, "_");
		}
		else if (( strcmp(entryTime,"NULL") )==0 && ( strcmp(exitTime,"NULL")!=0 ))
		{	strcat (attendanceString, "_");
			strcat (attendanceString, exitTime);
		}
		else if(( strcmp(entryTime,"NULL") )!=0 && ( strcmp(exitTime, "NULL") )!=0)
		{	strcat (attendanceString, entryTime);
			strcat (attendanceString, "_");
			strcat (attendanceString, exitTime);
		}
		else
		{	strcat (attendanceString, "__");
		}
		strcat (queryMakeAttendance, attendanceString);
		strcat (queryMakeAttendance, "' WHERE rNAD='");
		strcat (queryMakeAttendance, rNAD);
		strcat (queryMakeAttendance, "'");
	//END CHECK ATTENDANCE STRING SET AND QUERY COMPLETED

		//printf ("MAKATTEND:: Query:: %s\n", queryMakeAttendance);
	//USING CONNECTIONATTENDANCE SHEET TO EXECUTE QUERY
		retCode = mysql_query (connectionAttendanceSheet, queryMakeAttendance);
		if (retCode == 1)
		{	printf("MAKATTEND:: Unable to Complete Query because of the following error.\n%s\n", mysql_error(connectionAttendanceSheet));
			printf("\nMAKATTEND:: \tDetails: rNAD:%s\n",rNAD);
			return 1;
		}
	//QUERY EXECUTED FUNCTION ACCOMPLISHED
	return 0;	
}	
#endif //ATTENDANCE_H_
