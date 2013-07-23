
#ifndef REGISTRY_H_
	#define REGISTRY_H_

int callFunction(int regID)
{	if (regID == 10)
	{	retCode = phase3main();
		if (retCode == 0)
			printf("System:: Phase 3 shutted down succesfully.\n");
		else
			printf("System:: Phase 3 shutted down but with some errors.\n");
	}
	else if (regID == 11)
	{	retCode = crTablmain();
		if (retCode == 0)
			printf("System:: Table Creator ended successfully.\n");
		else
			printf ("System:: Table Creator ended but with some errors.\n");
	}
	else if (regID == 20)
	{	pthread_t thread1, thread2;
		char *message1 = "BTSERV::";
		char *message2 = "REALTIMER::";
		int iret1, iret2;
	
		//Create independent each of the will execute function
	
		iret1 = pthread_create (&thread1, NULL, phase1main, (void *) message1);
		iret2 = pthread_create (&thread2, NULL, realtime, (void *) message2);
	
		//Wait till all the threads are complete. Unless we
		// wait we run the risk of executing an exit which ill terminate
		// the process and all threads before the threads have completed.
	
		pthread_join (thread1, NULL);
		pthread_join (thread2, NULL);
	
		printf ("%s returned : %d\n", message1, iret1);
		printf ("%s returned : %d\n", message2, iret2);
	}
	else if (regID == 21)
	{	retCode = populateMain();
		if (retCode == 0)
			printf ("System:: Populator ended successfully.\n");
		else
			printf ("System:: Populator ended but with some errors.\n");
	}
	else if (regID == 22)
	{	retCode = showWDBmain();
		if (retCode == 0)
			printf("System:: Showing all workers.\n");
		else
			printf("System:: Some Error occurred while accessing database of workers.\n");
	}
	else if (regID == 23)
	{	retCode = prepareSheetMain();
		if (retCode == 0)
			printf ("System:: Sheet Creater Ended Successfully.\n");
		else
			printf ("System:: Sheet Creater Ended but with some errors.\n");
	}
	else if (regID == 24)
	{	retCode = system("oobase /usr/share/omniPresence/omniPresenceFE.odb");
		if (retCode == 0)
			printf ("System:: FEODB ended successfully.\n");
		else
			printf ("System:: FEODB ended but withsuccessfully.\n");
	}
	else if (regID == 25)
	{	retCode = sanctionLeaveMain();
		if (retCode == 0)
			printf ("System:: Sanction Leave ended successfully.\n");
		else if (retCode == 1)
		{	printf ("System:: Sanction Leave ended but with Database Connection Error.");
			printf (" You might not have rights to access or wrong authentication parameters have been entered.\n");
		}
		else if (retCode == 2)
			printf ("System:: Sanction Leave ended but with Query Error. Please check the database consistency and values.\n");
		
		else
			printf ("System:: Sanction Leave ended but with some errors.\n");
	}
	else if (regID == 26)
	{	//retCode = validateMain();
		if (retCode == 0)
			printf ("System:: Sheet Validator Ended successfully.\n");
		else
			printf ("System:: Sheet Validator Ended but with some errors.\n");
	}
	else if (regID == 27)
	{	retCode = showInfoMain();
		if (retCode == 0)
			printf ("System:: Show Information Module Ended successfully.\n");
		else
			printf ("System:: Show Information Module Ended Successfully but with some errors.\n");
	}
	else if (regID == 28)
	{	retCode = showStatusGTKMain();
		if (retCode == 0)
			printf ("System:: Show Status Module Ended Successfully.\n");
		else
			printf ("System:: Show Status Module Ended but with some errors.\n");
	}
	else if (regID == 29)
	{	retCode = userAddMain();
		if (retCode == 0)
			printf ("System:: User addition module exited successfully.\n");
		else
			printf ("System:: User addition module ended but with some errors.\n");
	}
	else if (regID == 30)
	{	retCode = notifyMain();
		if (retCode == 0)
			printf ("System:: Notification module ended successfully.\n");
		else
			printf ("System:: Notification module ended but woth some errors.\n");
	}
	else if (regID == 31)
	{	retCode = login_window();
		if (retCode == 0)
		{	printf ("System:: Authentication module ended successfully.\n"); 
			strcpy (user, uname);
			strcpy (password, pswd);
		}
		else
			printf ("System:: Authentication module ended but with some errors.\n");
	}
	else if (regID == 32)
	{	retCode = bckMain();
		if (retCode == 0)
			printf ("System:: Backup Completed Succssfully.\n");
		else
			printf ("System:: Some Error popped out in the backup module.\n");
	}
	else if (regID == 33)
	{	retCode = SMDmain();
		if (retCode == 0)
			printf ("System:: Show Month Details Module Ended Successfully.\n");
		else
			printf ("System:: Show Month Details Module Ended but with some errors.\n");
	}
	else if (regID == 6)
	{	showMenu();
	}
	else if (regID == 7)
	{	showAbout();
	}
	else if (regID == 8)
	{	clearScreen();
		clearOPCC = 1;
		//printf ("System:: Clearing Sreen...");
	}
	else
	{	printf("System:: Application Not defined in registry. Please contact your system administrator.\n");
	}
	return 0;
}
#endif //REGISTRY_H_
