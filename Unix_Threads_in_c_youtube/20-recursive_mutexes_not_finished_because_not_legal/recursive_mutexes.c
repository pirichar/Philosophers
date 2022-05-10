#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_TH 8

pthread_mutex_t mutexFuel; 
int fuel = 50;
/*
	You Can actually lock a mutex in the same thread mutliple times in a same thread
	In order to do so we have to set some atributes to the mutex itself

	To do so we have to use the command pthread_mutexattr_t to create a recusrive mutex WHICH IS NOT ALLOWED IN OUR PROJECT

*/
void	*routine(void *arg)
{
		pthread_mutex_lock(&mutexFuel);
		fuel += 50;
		printf("Incremented fuel ot %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
	
	return (NULL);
}

int main(int argc, char **argv)
{
	int i;
	pthread_t th[NB_TH];
	pthread_mutexattr_t recursiveMutexAttribute;
	pthread_mutexattr_settype(&recursiveMutexAttribute, );
	pthread_mutex_init(&mutexFuel, NULL);

	i = -1;
	while (++i < NB_TH)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			perror("Could not create thread");
	}
	i = -1;
	while (++i < NB_TH)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Could not join thread");
	}
	printf("Fuel at the end %d\n", fuel);
	pthread_mutex_destroy(&mutexFuel);
	return (0);
}