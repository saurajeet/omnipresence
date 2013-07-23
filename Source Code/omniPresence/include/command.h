
#ifndef COMMAND_H_
	#define COMMAND_H_

static char commandLineASCII[50] = "";

int compareString(char[], char[], int);

void changeToUpper(char instr[])
{       char ch[3] = "";
        int len=0,i=0;
        len=strlen(instr);
        while(i<len)
        {       sprintf(ch, "%c", toupper(instr[i]));
                strcat(commandLineASCII, ch);
                i++;
        }
        return ;
}

int commandLineProcessor(char ipcommandLine[])
{	//printf("CMP: %s %s %d.\n",ipcommandLine, commandLineASCII, noOfCommands);
	if ((compareString(commandLineASCII, "QUIT", 4)) == 0 || (compareString(commandLineASCII, "EXIT", 4)) == 0)
	{	strcpy(commandLineASCII, "");
		return 0;
	}
	if ((compareString(commandLineASCII, "Q", 1)) == 0)
	{	strcpy(commandLineASCII, "");
		return 0;
	}
	if ((compareString(commandLineASCII, "PHASE3", 6)) == 0)
	{	strcpy(commandLineASCII, "");
		return 10;
	}
	if ((compareString(commandLineASCII, "CREATE_TABLE", 12)) == 0)
	{	strcpy (commandLineASCII, "");
		return 11;
	}
	if ((compareString (commandLineASCII, "PHASE1", 6)) == 0)
	{	strcpy (commandLineASCII, "");
		return 20;
	}
	if ((compareString (commandLineASCII, "POPULATE", 8)) == 0)
	{	strcpy (commandLineASCII, "");
		return 21;
	}
	if ((compareString (commandLineASCII, "WORKERS", 7)) == 0)
	{	strcpy (commandLineASCII, "");
		return 22;
	}
	if ((compareString (commandLineASCII, "PREPARE", 7)) == 0)
	{	strcpy (commandLineASCII, "");
		return 23;
	}
	if ((compareString (commandLineASCII, "FEODB", 5)) == 0)
	{	strcpy (commandLineASCII, "");
		return 24;
	}
	if ((compareString (commandLineASCII, "SANCTION_LEAVE", 14)) == 0)
	{	strcpy (commandLineASCII, "");
		return 25;
	}
	if ((compareString (commandLineASCII, "VALIDATE", 8)) == 0)
	{	strcpy (commandLineASCII, "");
		return 26;
	}
	if ((compareString (commandLineASCII, "SHOW_INFO", 9) == 0))
	{	strcpy (commandLineASCII, "");
		return 27;
	}
	if ((compareString (commandLineASCII, "SHOW_STATUS", 11)) == 0)
	{	strcpy (commandLineASCII, "");
		return 28;
	}
	if ((compareString (commandLineASCII, "USERADD", 7)) == 0)
	{	strcpy (commandLineASCII, "");
		return 29;
	}
	if ((compareString (commandLineASCII, "NOTIFY", 6)) == 0)
	{	strcpy (commandLineASCII, "");
		return 30;
	}
	if ((compareString (commandLineASCII, "AUTHENTICATE", 12)) == 0)
	{	strcpy (commandLineASCII, "");
		return 31;
	}
	if ((compareString (commandLineASCII, "BACKUP", 6)) == 0)
	{	strcpy (commandLineASCII, "");
		return 32;
	}
	if ((compareString (commandLineASCII, "SHOW_MD", 7)) == 0)
	{	strcpy (commandLineASCII, "");
		return 33;
	}
	if ((compareString(commandLineASCII, "\n", 1) == 0) || (compareString(commandLineASCII, "NULL", 4) == 0))
	{	strcpy (commandLineASCII, "");
		return 5;
	}
	if ((compareString (commandLineASCII, "MENU", 4)) == 0 || (compareString(commandLineASCII, "HELP", 4) == 0))
	{	strcpy (commandLineASCII, "");
		return 6;
	}
	if ((compareString (commandLineASCII, "ABOUT", 5)) == 0)
	{	strcpy (commandLineASCII, "");
		return 7;
	}
	if ((compareString (commandLineASCII, "START", 5)) == 0)
	{	strcpy (commandLineASCII, "");
		return 5;
	}
	if ((compareString (commandLineASCII, "CLEAR", 5)) == 0)
	{	strcpy (commandLineASCII, "");
		printf ("Clearing OPCC");
		return 8;
	}
	else
	{	strcpy(commandLineASCII, "");
		if (noOfCommands == 1)
			return 5;
		else
			return 1;
	}
	return 5;
}

int compareString(char inpStr[], char cmpStr[], int no)
{	//printf ("CS: %s-%s-%d\n", inpStr, cmpStr, no);
	int localCtr = 0;
	//char inp[50] = "HELLO";
	//strcpy(inp, inpStr);
	//printf ("CS: %c - %c - %c - %c, %s", inp[0], inp[1], inp[2], inp[3], inp);
	for (localCtr = 0; localCtr < no; localCtr++)
	{	//printf("%c - %c, %d - %d\n", inpStr[localCtr], cmpStr[localCtr]);
		if (inpStr[localCtr] != cmpStr[localCtr])
			return 1;
	}
	return 0;
}
#endif //COMMAND_H_
