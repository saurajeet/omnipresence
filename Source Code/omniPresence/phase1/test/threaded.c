#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function (void *ptr);

main()
{
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int iret1, iret2;

	//Create independent each of the will execute function

	iret1 = pthread_create (&thread1, NULL, print_message_function, (void *) message1);
	iret2 = pthread_create (&thread2, NULL, print_message_function, (void *) message2);

	//Wait till all the threads are complete. Unless we
	// wait we run the risk of executing an exit which ill terminate
	// the process and all threads before the threads have completed.

	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);

	printf ("\nThread 1 returns : %d\n", iret1);
	printf ("\nThread 2 returns : %d\n", iret2);

	return 0;
}

void *print_message_function (void *ptr)
{	char *message;
	message = (char *)ptr;
	printf ("\n %s \n", message);
}
