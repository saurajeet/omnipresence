int push(char [],char);
char pop(char []);
const int size = 512;
int top = -1;
static iter = 0;
char parsedfield1[25]={""},parsedfield2[25]={""},parsedfield3[25]={""},parsedfield4[25]={""},parsedfield5[25]={""},parsedfield6[25]={""},parsedfield7[25]={""},parsedfield8[25]={""},parsedfield9[25]={""},parsedfield10[25]={""},parsedfield11[25]={""},parsedfield12[25]={""},parsedfield13[25]={""},parsedfield14[25]={""},parsedfield15[25]={""},parsedfield16[25]={""},parsedfield17[25]={""},parsedfield18[25]={""},parsedfield19[25]={""},parsedfield20[25]={""},parsedfield21[25]={""},parsedfield22[25]={""},parsedfield23[25]={""},parsedfield24[25]={""},parsedfield25[25]={""},parsedfield26[25]={""},parsedfield27[25]={""},parsedfield28[25]={""},parsedfield29[25]={""},parsedfield30[25]={""},parsedfield31[25]={""},parsedfield32[25]={""};
void clear_Parser();
void parser(char array[], int n)
{
	int t=0,ret,i=0,j=0,u;
	int field = 0;
	char item,res,stack[512]="",ch;
	clear_Parser();
//	printf("Starting parser...\n");
//	printf("Array:: %s",array);
//	printf("%d\n",strlen(array));
	while(t<=strlen(array))
	{
		item = array[t];
//		printf("PARSER::item = %c\n",item);
		if(item == '<')
			{
				field++;
//				printf("PARSER::field =  %d ; SKIPPING '<'\n",field);
			}
		if(item != '<' && item != '>' && item != '\0')
		{
//			printf("PARSER:: pushing item\n");
			ret = push(stack, item);
			i++;
//			printf("PARSER:: top = %d , stack[%d] = %c, i = %d\n",top,top,stack[top],i);
		}
		if(item == '>')
		{	for(u = 0; u <= n; u++)
			{
			if(field == u)
			{
//				printf("PARSER:: poping item from stack with field 1\n");
				while(top != -1 )
				{
					res = pop(stack);
					i--;
					if(field == 1)
						parsedfield1[i] = res;
					if(field == 2)
						parsedfield2[i] = res;
					if(field == 3)
                                                parsedfield3[i] = res;
					if(field == 4)
                                                parsedfield4[i] = res;
					if(field == 5)
						parsedfield5[i] = res;
					if(field == 6)
						parsedfield6[i] = res;
					if(field == 7)
						parsedfield7[i] = res;
					if(field == 8)
                                                parsedfield8[i] = res;
					if(field == 9)
                                                parsedfield9[i] = res;
					if(field == 10)
						parsedfield10[i] = res;
					if(field == 11)
						parsedfield11[i] = res;
					if(field == 12)
						parsedfield12[i] = res;
					if(field == 13)
                                                parsedfield13[i] = res;
					if(field == 14)
                                                parsedfield14[i] = res;
					if(field == 15)
						parsedfield15[i] = res;
					if(field == 16)
						parsedfield16[i] = res;
					if(field == 17)
						parsedfield17[i] = res;
					if(field == 18)
                                                parsedfield18[i] = res;
					if(field == 19)
                                                parsedfield19[i] = res;
					if(field == 20)
						parsedfield20[i] = res;
					if(field == 21)
						parsedfield21[i] = res;
					if(field == 22)
						parsedfield22[i] = res;
					if(field == 23)
                                                parsedfield23[i] = res;
					if(field == 24)
                                                parsedfield24[i] = res;
					if(field == 25)
						parsedfield25[i] = res;
					if(field == 26)
						parsedfield26[i] = res;
					if(field == 27)
						parsedfield27[i] = res;
					if(field == 28)
                                                parsedfield28[i] = res;
					if(field == 29)
                                                parsedfield29[i] = res;
					if(field == 30)
						parsedfield30[i] = res;
					if(field == 31)
                                                parsedfield31[i] = res;
					if(field == 32)
						parsedfield32[i] = res;
					//printf("PARSER::field1 %c----%d----%d \n",parsedfield1[i],top,i);
				}
			}
			}
		}
		t++;
	}
//	iter++;
}

int push(char stack[], char ele)
{
        if(top == size-1)
                return -1;
        else
        {
                top++;
                stack[top] = ele;
        }
        return 0;
}

char pop(char stack[])
{
        char ret;
        if(top == -1)
        {
                printf("\nUnderflow!\n");
                return ;
        }
        else
        {
                ret = stack[top];
                top--;
        }
        return ret;
}

void clear_Parser()
{	int a=0,buf=0;
	//for(buf = 0;buf<=10;buf++)
	//{
	while(parsedfield1[a]!='\0')
        {       parsedfield1[a]=' ';
                a++;
        }
	a=0;
	while(parsedfield2[a]!='\0')
        {       parsedfield2[a]=' ';
                a++;
        }
	a=0;
	while(parsedfield3[a]!='\0')
        {       parsedfield3[a]=' ';
                a++;
        }
	a=0;
	while(parsedfield4[a]!='\0')
        {       parsedfield4[a]=' ';
                a++;
        }
}
