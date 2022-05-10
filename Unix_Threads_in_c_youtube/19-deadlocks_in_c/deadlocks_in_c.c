#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_TH 8

pthread_mutex_t mutexFuel; 
int fuel = 50;
pthread_mutex_t mutexWater; 
int water = 10;

/*
	A very simple example of a deadlock is when you lock a mutex twice
	For example if for some reason instead of locking it once like bellow
	you would do 
	pthread_mutex_lock(&mutexFuel);
	pthread_mutex_lock(&mutexFuel);
	If you try to lunch that the program is gonna get stock forever
	Because the lock is allready been taken and its trying to do it 
	at the same time with the same thread
*/
void	*routine(void *arg)
{
	if (rand () % 2 == 0)
	{
		pthread_mutex_lock(&mutexFuel);
		sleep(1);
		pthread_mutex_lock(&mutexWater);
	}
	else
	{
		pthread_mutex_lock(&mutexWater);
		sleep(1);
		pthread_mutex_lock(&mutexFuel);
	}
		fuel += 50;
		water = fuel;
		printf("Incemented fuel to : %d set water to %d\n", fuel, water);
		pthread_mutex_unlock(&mutexFuel);
		pthread_mutex_unlock(&mutexWater);
	
	return (NULL);
}

int main(int argc, char **argv)
{
	int i;
	pthread_t th[NB_TH];
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_mutex_init(&mutexWater, NULL);
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
	printf("Water at the end %d\n", water);
	pthread_mutex_destroy(&mutexFuel);
	pthread_mutex_destroy(&mutexWater);
	return (0);
}