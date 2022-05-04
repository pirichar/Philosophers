#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//To use Thread you need to inlcude pthread and also to link
//in order you should compile with gcc -g -pthread shor_introduction_to_threads.c 
#include <pthread.h>

/*
	To solve the issue of the race condition
	We can use a mutex

	A mutex is a sort of a lock around a section of code
	Here I initialize a mutez with the command 
	pthread_mutex_t


	Think as mutex as some bracket that
	protects a part of a code that you want to protect
	agaisnt other threads executing it at the same time
	If at any point any thread is executing this line of code
	Theres not gonna be any other thread aht is gonna execute this line of code
	because there is a mutex around it (in our case mail++)
*/
int mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0;i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);

	}
	return (NULL);
}


/*
	In the last videos we created thread one by one
	repeating useless code multiple times

	What we could do to eveitate that is
	creating an array of threads
	Like showned bellow
	NOTE THAT THIS METHOD WILL NOT PERMIT PARRALLELISM
	It would create a first thread ; run it and then start over with the second
	Look further in the page to see the 
*/
int main(int argc, char **argv)
{
	pthread_t th[4];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
		if (pthread_join(th[i],NULL) != 0)
			return (2);
		printf("Thread %d has finished its execution\n", i);
	}
	printf("Number of mails : %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}


