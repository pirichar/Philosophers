#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//To use Thread you need to inlcude pthread and also to link
//in order you should compile with gcc -g -pthread shor_introduction_to_threads.c 
#include <pthread.h>

int mails = 0;
void	*routine()
{
	for (int i = 0;i < 100000; i++)
	{
		mails++;
	}
	//step of incrementing
	// read mails
	// increment
	// write mails
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t t1, t2;

	if (pthread_create(&t1, NULL,&routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL,&routine, NULL) != 0)
		return (2);	
	if (pthread_join(t1,NULL) != 0)
		return (3);
	if (pthread_join(t2,NULL) != 0)
		return (4);
	printf("Number of mails : %d\n", mails);
	return (0);
}


