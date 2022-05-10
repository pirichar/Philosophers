#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
	So the way showned bellow is the way I used to delcare mutex
	I (for now) declare a global variable as a mutex
	I then init it with pthread_mutex_init and I destroy it at the end

	Tho if I don't have anyuse for the second parameter of pthread_mutex_init
	I can create it in another way (see the second snipet of code uncommented bellow)
*/
// #define THREAD_NB 2

// pthread_mutex_t mutex;

// void	*routine(void *arg)
// {
// 	printf("ROUTINE CALL\n");
// 	return (NULL);
// }

// int main (int arc, char **argv)
// {
// 	int i;
// 	pthread_t threads[THREAD_NB];
// 	pthread_mutex_init(&mutex, NULL);

// 	i = -1;
// 	while (++i < THREAD_NB)
// 	{
// 		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
// 			return (1);
// 	}
// 	i = -1;
// 	while (++i < THREAD_NB)
// 	{
// 		if (pthread_join(threads[i], NULL) != 0)
// 			return (2);
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }


/*
	As said top we can just use PTHREAD_MUTEX_INITIALIZER after the mutex
	Then we don't have to do the pthread_mutex_init
	The mutex destroy is a good practice to call everysingle time
	But its not mandatory on most systems the ressources will be automatically cleaned up
	
*/
#define THREAD_NB 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*routine(void *arg)
{
	printf("ROUTINE CALL\n");
	return (NULL);
}

int main (int arc, char **argv)
{
	int i;
	pthread_t threads[THREAD_NB];

	i = -1;
	while (++i < THREAD_NB)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < THREAD_NB)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (2);
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
