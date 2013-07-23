/* THIS SOFTWARE IS A INTEGRATED PART OF OMNIPRESENCE WHICH IS AN INDUSTRY AUTOMATION SOFTWARE. NOT TO BE USED SEPERATELY
 * THIS MODULE IS NAMED AS OMNIPRESENCE COMMAND CENTRAL, AND COORDINATES ALL MAJOR ACTIVITIES RELATED TO OMNIPRESENCE
 *
 *	AUTHORS		: Saurajeet Dutta, Jyoti Prakash Nath, Rahul Bose, Purushottam
 *	MAILING LISTS	: <vention.gothics@gmail.com>,<jp2018@gmail.com>,<rahul2016@gmail.com>,<purushottam.prince@gmail.com>
 *	INSTITUTE	: Birla Institute Of Technology, Extension Centre Lalpur, Ranchi, Jharkhand, India PIN:834001
 *	PROGRAM NAME	: OMNIPRESENCE COMMAND CENTRAL (O.P.C.C.)
 *	LICENSE		: FREELY REDISTRIBUTABLE ("GPL V2")
 *
 * WE DONOT PROVIDE ANY WARRANTY OR SUCH THAT WOULD COVER ANY KIND OF HARM CAUSED BY THE SOFTWARE. THOUGH WE HAVE TESTED THE BOUNDS
 * OF THIS SOFTWARE BEFORE DEPLOYMENT. PLEASE DONOT HOLD US RESPONSIBLE. (JUST FOR PROGRAMMATICAL FUN)
 */

/*********************************************************************************************************
					OMNIPRESENCE COMMAND CENTRAL
*********************************************************************************************************/

//GLOBAL VARIABLE DECLARATION
static char user[10] = "";
static char password[10] = "";
static short shutdownOPCC = 0;
static unsigned long noOfCommands = 0;
int clearOPCC = 0;
//END VARIABLE DECLARATION

//INCLUDE GLIBC HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <sys/socket.h>
#include <mysql/mysql.h>
#include <time.h>
#include <limits.h>
#include <gtk/gtk.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <pthread.h>
//END GLIBC HEADERS

//INCLUDE COMPONENTS
#include "phase1/include/login.h"
#include "phase1/phase1.h"
#include "phase1/realtime.h"
#include "phase2/rnadgen.h"
#include "phase2/insertRnad.h"
#include "phase2/userAdd.h"
#include "phase2/showInfo.h"
#include "phase2/showStatusGTK.h"
#include "phase2/sl.h"
#include "phase2/sendsms.h"
#include "phase2/include/fileSearch.h"
#include "phase2/backup.h"
#include "phase2/include/parser.h"
#include "phase2/showMonthDetails.h"
#include "phase3/sheet/caltotal.h"
#include "phase3/sheet/absent.h"
#include "phase3/phase3.h"
#include "tools/sheetPrepare.h"
#include "tools/showWDB.h"
#include "tools/populate.h"
#include "tools/sheetCreater.h"
#include "tools/createTable.h"
//END INCLUSION OF COMPONENTS

//INCLUDE CUSTOM HEADERS
#include "include/menu.h"
#include "include/command.h"
#include "include/registry.h"
//END CUSTOM HEADERS

int main(int argc, char *argv[0])
{	printf("System:: Starting OmniPresence Command Central...");
	strcpy(user, uname);
	strcpy(password, pswd);
	//LOCAL VARIABLES AND CONNECTIONS
		unsigned short retCode = 0;
		int errno;
		char ch='N';
		char module[50] = " ";
		unsigned int selectedOperation = 0;	
	//END LOCAL VARIABLES
	printf("done\n");
	
	//INITIATING GRAPHICAL SYSTEM
	printf ("System:: Initiating graphical environment.....");
	gtk_init(&argc, &argv);
	printf ("done.\n");
	//INITIATED
	
	login_window();
	strcpy (user, uname);
	strcpy (password, pswd);
	//printf ("System:: User: %s,\t\t Password: %s\n", user, password);
	
	//GENERATE PROMPT AND PARSE VALUES
	printf("System:: Generating Prompt\nReady for input with a smile.\n");
	fflush (stdin);
	while (shutdownOPCC != 1 || clearOPCC != 1)
	{	//printf ("\nCLEAROPCC = %d", clearOPCC);
		if (clearOPCC == 1)
		{	printf("\n \033[34;47mOPCC (^_^):: ");
                        scanf("%s", &module);
                        changeToUpper(module);
                        printf("\033[35;m");
			//int clrscr_OPCC = 0;
                        //for (clrscr_OPCC = 0; clrscr_OPCC <= 5500; clrscr_OPCC++)
                                //printf (" ");
			//printf ("Till Here");
                        //for (clrscr_OPCC = 0; clrscr_OPCC <= 5500; clrscr_OPCC++)
                                //printf ("\b");
		}
		else
		{	printf("\n \033[34;47mOPCC (^_^):: ");
			scanf("%s", &module);
			changeToUpper(module);
			printf("\033[35;m");
		}
		noOfCommands++;
		selectedOperation = commandLineProcessor(commandLineASCII);
		if (selectedOperation == 0)
		{	break;
		}
		else if (selectedOperation == 5)
		{	continue;
		}
		else
		{	retCode = callFunction(selectedOperation);
		}	
	}

	//COLLECT AND SHUTDOWN SYSTEM
	printf("System:: Shutting down OmniPresence Command Central\n");
	return 0;
}
