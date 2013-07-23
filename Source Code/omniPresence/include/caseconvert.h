#ifndef _CASECONVERT_H_
	#define _CASECONVERT_H_
static char commandLine[50] = " ";
void changeToUpper(char instr[])
{	char ch[3] = "";
	int len=0,i=0;
	len=strlen(instr);
	while(i<len)
	{ 	sprintf(ch, "%c", toupper(instr[i]));
		strcat(commandLine, ch);
		i++;
	}	
	return ;
}
#endif //_CASECONVERT_H_
