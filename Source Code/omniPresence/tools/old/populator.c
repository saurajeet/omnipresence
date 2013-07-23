/* THIS PROGRAM IS TO BE USED WITH OMNIPRESENCE SOFTWARES ONLY. PLEASE USE IT WITH COMMAND CENTRAL ONLY.
 * THIS PROGRAM POPULATES THE WORKERS DB POPULATES WITH DUMMY VALUES IN THE WORKERS DB AND THE ATTENANCE TABLE.
 * 	NAME		: Saurajeet Dutta
 *	PROGRAM NAME	: Populator
 *	INSTITUTE	: Birla Institute Of Technology, Extension Centre Lalpur, Ranchi - 834002
 *	MAILING LIST	: <vention.gothics@gmail.com>
 * 	DATE		: March 10, 2009. Tuesday
 * 	LICENSE		: Freely Redistributable (GPL v2)
 * THIS PROGRAM OR ANY PART OF IT HAS BEEN DEVELOPED FOR DEVELOPMENT FUN, WE DONOT COVER ANY GUARANTEE OR WARRANTY OR AS SUCH.
 * THOUGH THE SOFTWARE HAS BEEN TESTED TO BE IN THE BOUNDS, BUT WE WILL NOT BE RESPONSIBLE FOR DAMAGE OF ANY PART OF THE SYSTEM.
*/

//INCLUDE GLIBC HEADERS
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <errno.h>
//END INCLUSION GLIBC HEADERS

#define MAX_POPULATION_WORKERSDB 25	//always check that this value is greater than NO_POPULATION_WORKERSDB macro
#define NO_POPULATION_WORKERSDB 22	//if u change this value please make sure that you make a corresponding SQL entry in query variable
#define MAX_POPULATION_SCANDUMP 50	//always check that this value is greater than NO_POPULATION_SCANDUMP macro
#define NO_POPULATION_SCANDUMP 39	//if u change this value please see that you make a corresponding SQL entry in the queryScanDump
int main(void)
{
		//LOCAL VARIABLES
			int i=0;
			char ch1[5] = "0109";
			char ch2[3] = "20"; 
			char * server = "localhost";
			char * user = "root";
			char * password = "omni";
			char * database = "omniPresence";
			int retCode = 0;
			char choice = 'Y';
			int stateWDB = 0;
			int stateAS = 0;
			int stateSD = 0;
			MYSQL * connectionPopulator;
			MYSQL * connectionPopulator2;
			MYSQL_RES * resultPopulator;
			MYSQL_RES * resultPopulator2;
			MYSQL_ROW rowsPopulator;
			MYSQL_ROW rowsPopulator2;
		//END LOCAL VARIABLES

	printf ("POPULATOR FOR OMNIPRESENCE\n");
	printf ("NOTE: PLEASE TRUNCATE THE WORKERSDB, SCANDUMP, ATTENDANCESHEET AND LASTDUMPSESSION BEFORE YOU CONTINUE.\n");
	printf ("      PLEASE CHECK THE VALUES IN THE DATABASE BEFORE YOU START THE RFID SERVER ELSE THE SERVER MAY AUTOLOCK ITSELF.\n");
	printf ("      YOU CAN PRESS CTRL + C TO STOP THE PROGRAM IMMEDIATELY IF YOU HAVENT DONE THE ABOVE CHANGES TO THE DB.\n");
	char query[MAX_POPULATION_WORKERSDB][200] = 
	{	"INSERT INTO workersDB VALUES ('00:01:02:03:04:05',	'Abhijeet Sinha',	'VG01',	'rn31245',	'+919835594096')",
		"INSERT INTO workersDB VALUES ('00:05:06:07:08:09',	'Dipu Kumar',		'VG02',	'rn21322',	'+919905730557')",
		"INSERT INTO workersDB VALUES ('00:09:10:11:12:13',	'Jayanto Sengupta',	'VG03',	'rn09843',	'+919939166399')",
		"INSERT INTO workersDB VALUES ('00:13:14:15:16:17',	'Karan Bagaria',	'VG04',	'rn17459',	'+919334389492')",
		"INSERT INTO workersDB VALUES ('00:17:18:19:20:21',	'Karunesh',		'VG05',	'rn78462',	'+919835773525')",
		"INSERT INTO workersDB VALUES ('00:21:22:23:24:25',	'Mahendra Rai',		'VG06',	'rn09383',	'+919934106124')",
		"INSERT INTO workersDB VALUES ('00:25:26:27:28:29',	'Pallava Ray',		'VG07',	'rn82752',	'+919973861659')",
		"INSERT INTO workersDB VALUES ('00:29:30:31:32:33',	'Pankaj',		'VG08',	'rn39201',	'+919955493960')",
		"INSERT INTO workersDB VALUES ('00:33:34:35:36:37',	'Piyush Thapa',		'VG09',	'rn94301',	'+919934177063')",
		"INSERT INTO workersDB VALUES ('00:37:38:39:40:41',	'Prashant',		'VG10',	'rn09212',	'+919905721187')",
		"INSERT INTO workersDB VALUES ('00:41:42:43:44:45',	'Priyaranjan Kumar',	'VG11',	'rn85940',	'+919798385707')",
		"INSERT INTO workersDB VALUES ('00:45:46:47:48:49',	'Purushottam',		'VG12',	'rn94831',	'+919955346626')",
		"INSERT INTO workersDB VALUES ('00:49:50:51:52:53',	'Rahul Bose',		'VG13',	'rn84221',	'+919931564570')",
		"INSERT INTO workersDB VALUES ('00:53:54:55:56:57',	'Raj Shankar',		'VG14',	'rn95042',	'+919939260520')",
		"INSERT INTO workersDB VALUES ('00:57:58:59:60:61',	'Shrawan Kumar Yadav',	'VG15',	'rn03847',	'+919973283889')",
		"INSERT INTO workersDB VALUES ('00:61:62:63:64:65',	'Snigdharaj Sinha',	'VG16',	'rn82236',	'+919334384214')",
		"INSERT INTO workersDB VALUES ('00:65:66:67:68:69',	'Vikash Pathak',	'VG17',	'rn65423',	'+919835276275')",
		"INSERT INTO workersDB VALUES ('00:69:70:71:72:73',	'Vishal Anand',		'VG18',	'rn43322',	'+919835942314')",
		"INSERT INTO workersDB VALUES ('00:1F:5C:FA:19:B6',	'Saurajeet Dutta',	'VG19',	'rn93465',	'+919470367873')",
		"INSERT INTO workersDB VALUES ('00:77:78:79:80:81',	'Satyaveer Singh',	'VG20',	'rn11234',	'+919931100797')",
		"INSERT INTO workersDB VALUES ('00:81:82:83:84:85',	'Shivendra Pratik',	'VG21',	'rn76423',	'+919708569154')",
		"INSERT INTO workersDB VALUES ('00:18:E4:1A:5D:2B',	'Jyoti Prakash Nath',	'VG22',	'rn56483',	'+919934193632')"
	};
	char queryScanDump[MAX_POPULATION_SCANDUMP][100] =
	{	"INSERT INTO scanDump (mAC, time) VALUES ('00:18:E4:1A:5D:2B',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:21:22:24:24:25',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:1F:5C:FA:19:B6',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:18:E4:1A:5D:2B',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:69:70:71:72:73',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:41:42:43:44:45',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:05:06:07:08:09',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:21:22:23:24:25',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:53:54:55:56:57',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:33:34:35:36:37',	'08 :52')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:77:78:79:80:81',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:09:10:11:12:13',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:65:66:67:68:69',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:37:38:39:40:41',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:21:22:23:24:25',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:01:02:03:04:05',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:25:26:27:28:29',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:41:42:43:44:45',	'08 :53')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:81:82:83:84:85',	'08 :54')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:1A:2B:3C:4D:5C',	'08 :54')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:1A:2B:3C:4D:5C',	'08 :54')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:57:58:59:60:61',	'08 :54')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:69:70:71:72:73',	'08 :54')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:77:78:79:80:81',	'08 :55')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:57:58:59:60:61',	'08 :55')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:53:54:55:56:57',	'08 :55')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:57:58:59:60:61',	'08 :56')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:31:31:31:31:31',	'08 :56')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:69:70:71:72:73',	'08 :56')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:A1:B2:C3:D4:C5',	'08 :57')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:31:31:31:31:31',	'08 :57')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:A1:B2:C3:D4:C5',	'08 :58')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:A1:B2:C3:D4:C5',	'08 :58')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:77:78:79:80:81',	'08 :58')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:1F:5C:FA:19:B6',	'08 :59')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:21:22:23:24:25',	'08 :59')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:60:70:71:72:73',	'08 :59')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:53:54:55:56:57',	'08 :59')",
		"INSERT INTO scanDump (mAC, time) VALUES ('00:41:42:43:44:45',	'08 :59')"
	};

	//CONNECTING TO THE MYSQL SERVER
	printf ("POPMOD:: Connecting to the database server.....");
	connectionPopulator = mysql_init (NULL);
	if (!mysql_real_connect(connectionPopulator, server, user, password, database, 0, NULL, 0))
	{	printf("\nPOPMOD:: ERROR CONNECTING TO THE DATABASE: wdb: %s\n",mysql_error(connectionPopulator));
		return 1;
	}
	printf("connected\n");
	//CONNECTED

	//CHECKING THE CONSISTENCY OF THE WORKERS DATABASE AND FILLING WITH VALUES
	printf ("POPMOD:: Populate WORKERS DATABASE [Y/N]:");
	choice = getchar();	
	if (choice == 'y' || choice == 'Y')
	{	retCode = mysql_query (connectionPopulator, "select * from workersDB");
		if (retCode == 1)
		{	printf ("POPMOD:: Error Parsing query to the Workers Database:\n %s\n",mysql_error(connectionPopulator));
			return 1;
		}
		resultPopulator = mysql_use_result (connectionPopulator);
		if (resultPopulator == NULL)
		{	printf("POPMOD:: Error in result obtained from workers Database\n");
			return 1;
		}
		for (i=0;i<NO_POPULATION_WORKERSDB;i++)
	        {       printf ("POPMOD:: %s\n",query[i]);
	        }
		i = 0;
		while ((rowsPopulator = mysql_fetch_row(resultPopulator)) != NULL)
		{	i++;
		}
		if (i>20)
		{	printf ("POPMOD:: The workers database has already been populated earlier. Do you still want to populate it [Y/N]:");
			choice = getchar();
			choice = getchar();
			if (choice == 'y' || choice == 'Y')
			{	for (i = 0 ; i < NO_POPULATION_WORKERSDB ; i++)
				{	retCode = mysql_query (connectionPopulator, query[i]);
					if (retCode == 1)
						printf ("POPMOD:: Error in Populating entry %d\n", i);
				}
			}
		}
		else
		{	for (i = 0 ; i < NO_POPULATION_WORKERSDB ; i++)
	                {       retCode = mysql_query (connectionPopulator, query[i]);
	                        if (retCode == 1)
	                        printf ("POPMOD:: Error in Populating entry %d\n", (i+1));
	                }
		}
		printf ("POPMOD:: Workers Database Populated\n");
		stateWDB = 1;
	}
	else
		printf ("POPMOD:: Workers database not populated: USER ABORT\n");
	//FILLED WORKERS DATABASE WITH VALUES

	//POPULATE ATTENDANCE TABLE
	printf ("POPMOD:: Populate Attendance Table [Y/N]: ");
	choice = getchar();
	choice = getchar();
	if (choice == 'y' || choice == 'Y')
	{
		//GET INPUT
			printf ("POPMOD:: Please input the month suffix (e.g. 0209 for Feb 2009) for the table to be selected : ");
			scanf ("%s", &ch1);
			printf ("POPMOD:: Please input the date to which entries must be processed: ");
			scanf ("%s", &ch2);
		//END INPUT

		//VARIABLES AGAIN
			char tableName[23] = "attendanceSheet";
			char attendDate[10] = "Attend";
			char attendDateBck[10] = "Attend";
			int ch2int = 0;
		//END VARIABLES
		
		//PREPARING INPUT TO BE PROCESSED
			strcat(tableName, ch1);
			//strcat(attendDate, ch2);
			ch2int = atoi ((const) &ch2);
			printf ("POPMOD:: Tablename Selected : \t\t%s\n", tableName);
			//printf ("POPMOD:: Attendance Date Selected: \t%s\n", attendDate);
			printf ("POPMOD:: Date Entered is : %d\n", ch2int);
		//END PREPARATION

		//CONNECT TO DATABASE
		connectionPopulator2 = mysql_init(NULL);
		if (!mysql_real_connect(connectionPopulator2, server, user, password, database, 0, NULL, 0))
		{	printf("POPMOD:: ERROR IN CONNECTING TO DATABASE: as: %s", mysql_error(connectionPopulator));
			return 1;
		}
		//CONNECTED
		
		//PARSING QUERY
			char query2[200] = "INSERT INTO ";
			strcat (query2, tableName);
			strcat (query2, " (rNAD) VALUES('");
			char query2bck[200] = "";
			strcpy (query2bck, query2);
			char query3[200] = "UPDATE ";
			strcat (query3, tableName);
			strcat (query3, " SET ");
			char query3bck[200] = "";
			strcpy (query3bck, query3);

			//BUFFER THE WORKERS TABLE
			retCode = mysql_query(connectionPopulator2, "SELECT rNad FROM workersDB");
			if (retCode == 1)
			{	printf ("POPMOD:: Error in reading workersDB table for bufferring: %s\n", mysql_error(connectionPopulator2));
			}
			resultPopulator2 = mysql_use_result (connectionPopulator2);
			//BUFFERING COMPLETE

			//COPYING RNAD FROM WORKERS TABLE TO ATTENDANCE TABLE
			i = 0;
	                while ((rowsPopulator2 = mysql_fetch_row(resultPopulator2)) != NULL)
        	        {       i++;
				//printf ("POPMOD:: %s\n", rowsPopulator2[0]);
				strcat (query2, rowsPopulator2[0]);
				strcat (query2, "')");
				printf ("POPMOD:: Query[%d]: %s\n", i, query2);
				retCode = mysql_query(connectionPopulator, query2);
				if (retCode == 1)
				{	printf("POPMOD:: Error in Injecting query[%d]: %s\n", i, mysql_error(connectionPopulator2));
				}
				strcpy (query2, query2bck);
                	}
			//COPYING COMPLETE
			
			//FILLING THE ATTENDDATES UPTO WHICH IT HAS BEEN INPUTTED
			char num_str[3] = "";
			printf("POPMOD:: Populate attendance dates: [Y/N]: ");
			choice = getchar();
			choice = getchar();
			if (choice == 'y' || choice == 'Y')
			{	for (i = 1; i < ch2int; i++)
				{	sprintf (num_str, "%d", i);		//ITOA
					strcat (attendDate, num_str);
					strcat (query3, attendDate);
					strcat (query3, "='P:0852:1705'");
					printf ("POPMOD:: Query[%d]: %s\n", i, query3);
					retCode = mysql_query (connectionPopulator2, query3);
					if (retCode == 1)
					{	printf ("POPMOD:: Error injecting query[%d] to database Server", i);
					}
					strcpy (query3, query3bck);
					strcpy (attendDate, attendDateBck);
				}
			}
			//FILLING OF THE ATTENDDATES COMPLETE
		//QUERY PARSED
		printf ("POPMOD:: Attendance Table Populated\n");
		stateAS = 1;
	}	
	else
		printf ("POPMOD:: Attendance Table Not Populated : USER ABORT \n");
	//END POPULATE ATTENDANCE TABLE

	//FILLING SCANDUMP TABLE
		
		//WORK VARIABLES
			char day[4] = "Mon";
			char dateLDS[20] = "";
			int len = 0;
			char time[7] = "08 :59";
			char queryLDS[100] = "INSERT INTO lastDumpSession VALUES ('";
			char noSD[3] = "";
		//END WORK VARIABLES
		
	printf("POPMOD:: Populate Scandump table [Y/N]: ");
	choice = getchar();
	choice = getchar();
	if (choice == 'y' || choice == 'Y')
	{	//GET INPUT
		//if (stateAS = 0)
                {       printf ("POPMOD:: Please input the month suffix (e.g. 0209 for Feb 2009) for the table to be selected : ");
                        scanf ("%s", &ch1);
                        printf ("POPMOD:: Please input the date to which entries must be processed: ");
                        scanf ("%s", &ch2);
		}
                printf ("POPMOD:: Please enter the day of the date (%s %s) [3 letters e.g \"Mon\" for Monday][OPTIONAL]: ", ch2 ,ch1);
		scanf ("%s", &day);
		//END INPUT
			//PREPARING INPUT
				strcpy (dateLDS, day);
				strcat (dateLDS, ",");
				strcat (dateLDS, ch2);
				strcat (dateLDS, ",");
				strcat (dateLDS, ch1);
				dateLDS[9]= '\0';
				strcat (dateLDS, ",2009");
				strcat (queryLDS, dateLDS);
				strcat (queryLDS, "', '");
				strcat (queryLDS, time);
				strcat (queryLDS, "','");
				sprintf(noSD, "%d", NO_POPULATION_SCANDUMP);
				strcat (queryLDS, noSD);
				strcat (queryLDS, "')");
			//INPUT PREPARED

			//INJECT QUERY
			for (i = 0 ; i < NO_POPULATION_SCANDUMP ; i++)
                        {       retCode = mysql_query (connectionPopulator, queryScanDump[i]);
                                if (retCode == 1)
                                	printf ("POPMOD:: Error in Populating entry %d\n", (i+1));
                        }
			retCode = mysql_query (connectionPopulator, queryLDS);
                	//END INJECTION
		printf ("POPMOD:: Query LDS: %s\n", queryLDS);
		if (retCode == 1)
			printf ("POPMOD:: Error in Updating Last Dump Session\n");
		printf ("POPMOD:: Date updated to the lastDumpSession is %s at time %s\n", dateLDS, time);
		printf ("POPMOD:: ScanDump Table and the lastDumpSession has been artificially updated\n");
	}
	else
		printf ("POPMOD:: ScanDump Table update failed : USER ABORT\n");
	//SCANDUMP TABLE FILLED
	
	printf ("POPULATOR FOR OMNPRESENCE SHUTTED DOWN SUCCESSFULLY\n");
	return 0;
}
