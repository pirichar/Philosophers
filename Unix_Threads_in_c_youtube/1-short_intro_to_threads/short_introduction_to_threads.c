//link : https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2&t=39s

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//To use Thread you need to inlcude pthread and also to link
//in order you should compile with gcc -g -pthread shor_introduction_to_threads.c 
#include <pthread.h>


//Important notes to understand thread under this
/*
	the basis of creating a thread is that
	when you create a thread
	you execute a function whatever function you create

	here we are gonna start by creating a routine that is pretty generic
	and try to execute it with the threads

	----to start creating the thread we have to define a place----
	where the api can store some information about the thread
	we do this by using the variable pthread_t here we name it t1;

	-----To initialize a thread we call pthread_create()-------
	1-	the first argument is the pointer to the t1 variable we have created here
	So we just pass its address
	2-	Second are the atributes ; if you don't know what to pass
	you can just pass NULL since its asquing for a pointer
	3- Third is gonna be the function you want to execute
	in order to pass the function we just pass its adress
	4- lastly are the arguments you are gonna pass to routine if needed
	since in our case we don't have anything to pass with we are just gonna past null

	----Lastly, like processes, we need to wait for our pthreads to finish its execution----
	In order to do so ;you call pthread_join() which is pretty much the wait for pthread
	1- we pass the actual struct with no pointer 
	2- you can also pass a pointer that would get the result of the thread
	but we don't need to do so here
*/

//Main with only on thread in this
/*void	*routine()
{
	printf("Test from threads\n");
	return(NULL);
}
int main(int argc, char **argv)
{
	pthread_t t1;
	pthread_create(&t1, NULL,&routine, NULL);
	pthread_join(t1,NULL);
	return (0);
}*/


/*
	if I want to do the same but with 2 variables I just create a second variable
	call pthread create with this variable and wait for it as well

	In order to be sure that we can do two print and compare if they are printing at the same time
	Another good thing is to protect the creation of a thread
	pthread_create will return 0 if ok or an error message if not

	You can do the same for the pthread_join


*/

void	*routine()
{
	printf("Test from threads\n");
	sleep(2);
	printf("Ending thread\n");
	return(NULL);
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
	return (0);
}