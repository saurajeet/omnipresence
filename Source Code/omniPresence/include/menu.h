
#ifndef _MENU_H_
	#define _MENU_H_
void showMenu()
{	printf("\t\t\tCOMMANDS                                            PURPOSE\n");
	printf("\t\t\t-----------------------------------------------------------------------------------------------\n");
	printf("\t\t\t HELP                     : View the available list of commands in OmniPresence Command Central.\n");
	printf("\t\t\t QUIT                     : Exit from OmniPresence Command Central.\n");
	printf("\t\t\t ABOUT                    : View about OmniPresence Command Central (O.P.C.C.) and its developers.\n");
	printf("\t\t\t PHASE3                   : Start phase 3 for marking attendance from scanDump and lastDumpSession.\n");
	printf("\t\t\t CREATE_TABLE             : Create a table for a particular month.\n");
	printf("\t\t\t MENU                     : View the available list of commands in omniPresence Command Central.\n");
	printf("\t\t\t EXIT                     : Exit from OmniPresence Command Central.\n");
	printf("\t\t\t POPULATE                 : Populate & prepare the database with dummy values (For Presentation).\n");
	printf("\t\t\t PHASE1                   : Start the RFID server to detect available devices in a Piconet.\n");
	printf("\t\t\t WORKERS                  : Show all the workers working in this organisation.\n");
	printf("\t\t\t PREPARE                  : Prepare a sheet at the start of the month (Marks the holidays).\n");
	printf("\t\t\t FEODB                    : Open oobase Front End Window.\n");
	printf("\t\t\t SANCTION_LEAVE           : Sanction leaves for the employees.\n");
	printf("\t\t\t VALIDATE                 : Validates the attendanceSheet and prepares for sending SMSes.\n");
	printf("\t\t\t SHOW_INFO                : Shows the information of the employees for an Employee ID.\n");
	printf("\t\t\t SHOW_STATUS              : Opens a query tool for getting attendance status of an employee.\n");
	printf("\t\t\t USERADD                  : Adds a user in workers Database of the omniPresence.\n");
	printf("\t\t\t NOTIFY                   : Notifies the employees of their attendance status using SMS.\n");
	printf("\t\t\t AUTHENTICATE             : Authenticates the user in the omniPresence. (Opens Login Screen).\n");
	printf("\t\t\t BACKUP                   : Takes perodic backup of the complete omniPresence Database.\n");
	printf("\t\t\t SHOW_MD                  : Show Month Details for a given employee.\n");
	printf("\t\t\t-----------------------------------------------------------------------------------------------\n");

}

void showAbout()
{	printf("\t\t\t                                          OMNIPRESENCE\n");
	printf("\t\t\t-------------------------------------------------------------------------------------------------\n");
	printf("\t\t\tThis is software based on RFID (Radio Frequency Identification) System. It uses short range radio\n");
	printf("\t\t\tservice like bluetooth to detect devices in a Piconet and record it in a backend MYSQL database.\n");
	printf("\t\t\tThis system also processes the recorded device information and use it mark attendances of staffs\n");
	printf("\t\t\tworking in an organisation. OmniPresence also takes the responsibility to notify the present as \n");
	printf("\t\t\twell as the absent staffs by using Short Messaging Service facility of a local cellular network.\n");
	printf("\t\t\tFor more information type \"HELP\" or \"MENU\" at the OPCC prompt to view the available commands\n");
	printf("\t\t\tlist.\n\n");
	printf("\t\t\t                                    SOFTWARE VERSION: 0.0.1\n");
	printf("\t\t\t        DEVELOPED AT Birla Institute Of Technlogy, Extension Centre Lalpur, Ranchi, INDIA\n");
	printf("\t\t\t                                               BY\n");
	printf("\t\t\t                  Saurajeet Dutta - <vention.gothics@gmail.com> - BCA/2004/06\n");
	printf("\t\t\t                      Jyoti Prakash Nath - <jp2018@gmail.com> - BCA/2018/06\n");
	printf("\t\t\t                         Rahul Bose - <rahul2016@gmail.com> - BCA/2016/06\n");
	printf("\t\t\t                   Purushottam - <purushottam.prince@gmail.com> - BCA/2042/06\n");
	printf("\t\t\t-------------------------------------------------------------------------------------------------\n");
}

void clearScreen()
{	int clrscr_OPCC = 0;
	for (clrscr_OPCC = 0; clrscr_OPCC <= 5500; clrscr_OPCC++)
		printf (" ");
	for (clrscr_OPCC = 0; clrscr_OPCC <= 5500; clrscr_OPCC++)
		printf ("\b");
	//printf ("Hellp\bo\n");
	clearOPCC = 1;
}
#endif //_MENU_H_
