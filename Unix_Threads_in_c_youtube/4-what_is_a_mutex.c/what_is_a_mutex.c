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
		// so checking if the lock have been taking by someone
		// and wating for the lock to be unlocked
		//and setting the lock to one once we are taking the play
		//is completed by one function which is called 
		// pthread_mutex_lock(&mutex)
		pthread_mutex_lock(&mutex);
		mails++;
		//then instead of setting the lock to 0
		// we use pthread_mutex_unlock passing the mutex
		pthread_mutex_unlock(&mutex);

	}
	return (NULL);
}


/*
	in order to use the mutex uptop and to lock the processes
	we have to initialize it with pthread_mutex_init()
	It takes two argument firt; the adress of the mutex
	Second is some attribute we dont get to right now
	NULL sets everything to default

	NOTE THAT : at the end you have to use the function
	pthread_mutex_destroy which takes the address to mutex
	in order to destroy the created mutex 
*/
int main(int argc, char **argv)
{
	pthread_t t1, t2, t3 , t4;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL,&routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL,&routine, NULL) != 0)
		return (2);	
	if (pthread_create(&t3, NULL,&routine, NULL) != 0)
		return (3);
	if (pthread_create(&t4, NULL,&routine, NULL) != 0)
		return (4);	
	if (pthread_join(t1,NULL) != 0)
		return (5);
	if (pthread_join(t2,NULL) != 0)
		return (6);
	if (pthread_join(t3,NULL) != 0)
		return (7);
	if (pthread_join(t4,NULL) != 0)
		return (8);
	printf("Number of mails : %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}


