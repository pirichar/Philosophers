#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>


/*
	So here we can't return value because its locally allocated
	Then what we do is that we create result; we malloc 
	Then we set the VALUE OF (*) result to the value
*/
void *roll_dice()
{
	int value = (rand() % 6) + 1;
	int *result;
	result = malloc(sizeof(int));
	*result = value;
	printf("Thread result :%p\n", result); 
	return (void*)result;
}
/*
	to pass a value between a thread and main it has to do with the second parameter of pthread_join
	The pthread_join is gonna take a reference to a pointer (double pointer)
	and its gonna set the value from within it to what ever we have sent from here
	So here we create the int *res that we pass to the pthread_join by address so it becomes a double pointer
	We then allocate it in the roll_dice function
	and finally deallocate it in the main
	We are gonna fix it in thje next video with the threads argument
*/
int main(int argc, char **argv)
{
	int *res;
	//double check how srand works cuz I don't know
	srand(time(NULL));
	pthread_t th;

	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void**)&res) != 0)
		return 2;
	printf("Main res :%p\n", res); 
	printf("Result: %d\n", *res);
	free (res);
	return 0;
}