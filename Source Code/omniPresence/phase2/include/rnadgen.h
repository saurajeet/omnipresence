unsigned long baseConvert(unsigned long num,int base)
{
	unsigned long m,n=0;
	int rem=0;
	m=num;
	while(m>0)
	{
		rem=m%base;
		n=n*10+rem;
		m=m/base;
	}
	m=0;
	while(n>0)
	{
		rem=n%10;
		m=m*10+rem;
		n=n/10;
	}
	num=num+m;
	return num;
}
char rnad[100]= " ";

void rnadGenerator(void )
{	//printf("Into RGEN");
	time_t t;
        const struct tm* st;
	const char str1[50]="%m%d%y";
	const char str2[50]="%H%M%S";
	char arr1[50] = "";
	char arr2[50] = "";
	char nad1[50] = "";
	char nad2[50] ="";
	int x=0;
	unsigned long num1 = 0,num2 = 0,r1=0,r2=0,r3=0,r4=0,sum=0,quo=0;
	r1=rand();
        r2=rand();
        r3=rand();
        r4=rand();
        r1=r1/10;
        r2=r2/10;
        r3=r3/10;
        r4=r4/10;
	sum=r1+r2+r3+r4;
	x=time(&t);
        if(x==-1)
        {
                printf("cannot retrieve system time...");
                exit(1);
        }
        st=gmtime(&t);
//	printf("Struct Init");
        strftime(&arr1[0], sizeof(arr1), &str1[0], st);
	strftime(&arr2[0], sizeof(arr2), &str2[0], st);
//        printf("\n date %s\t",arr1);
//	printf("time %s",arr2);
	num1=atol(arr1);
	num2=atol(arr2);
	num2=num2+sum;
	quo=num2/1000000;
	num2=num2%1000000;
	num1=num1+quo;
//	printf("\nnum1: %ld\tnum2: %ld",num1,num2);
	num1=baseConvert(num1,7);
	num2=baseConvert(num2,9);
	sprintf(nad1,"%ld",num1);
	sprintf(nad2,"%ld",num2);
	if(strlen(nad1)==5)
		strcpy(rnad,"0");
	if(strlen(nad2)==5)
		strcat(nad1,"0");
	strcat(rnad,nad1);
	strcat(rnad,nad2);	
}

