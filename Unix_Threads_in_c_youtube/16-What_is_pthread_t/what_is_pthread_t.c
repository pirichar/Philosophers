#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
	So you can use the function pthread_self() to know what thread you are atm
	normally pthread are not really made to print out since they are of an opaque type
	Meaning that they could be a long or a long long so the way we printed it 
	is dangerous and it should only be used as demonstration purpuses

	The pthread_t is managed by the pthread_api
	The hierarchy would look at something like this
	1- Your program
	2- The api
	3- The OS
*/
void	*routine(void * args)
{
	pthread_t th = pthread_self();
	printf("%ul\n", th);
}

int main(int argc, char **argv)
{
	int nb_th;
	int i;

	i = -1;
	nb_th = 2;
	pthread_t th[nb_th];

	while (++i < nb_th)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL)!= 0)
			return (1);	
		printf("%ul\n", th[i]); // here we print the identification of the threads
	}
	i = -1;
	while (++i < nb_th)
	{
		if (pthread_join(th[i], NULL)!= 0)
			return (1);	
	}
}