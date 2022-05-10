/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_are_detached_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:04:12 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/05 12:00:53 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*
	There is 2 functions in this file be careful
*/


/*
	another interesting thing about thread is that you can detach them 
	from the main thread 
	The function to do is is pthread_detach(&th) and it takes as input the
	actual thread you want to detach 

	a detached thread is no longer joinable we can't no longer joinable
	We cannot longer call pthread_join on it
	That means we cannot wait on it to finish its execution before exiting the program

	Another thing about detached thread is that they clear their own ressources
	Before we had to call pthread_join on every joinable thread that we created
	so that we clear the ressources that we are using

	In this case with a detached threads you no longer have to do that
	In fact if you call pthread_join you will get an error
	We are not even getting the routine to execute because the main thread
	That as created the threads failed to join them so it did not wait
	Then the 2 created threads waited for 1 second which gave
	the time to the master process to just finish its execution

	What you have to do is that instead of returning 0 in the main
	you will youse pthread_exit(0) and the pthread_exit will wait for 
	the detached processes
*/

// # define THREAD_NUM 2
// void	*routine(void * args)
// {
// 	sleep(1);
// 	printf("Finished execution\n");
// 	return (NULL);
// }

// int main(int argc, char **argv)
// {
// 	int i;

// 	i = -1;
// 	pthread_t th[THREAD_NUM];

// 	while (++i < THREAD_NUM)
// 	{
// 		if (pthread_create(&th[i], NULL, &routine, NULL)!= 0)
// 		{
// 			perror("Failed to create thread");
// 			return (1);
// 		}
// 		pthread_detach(th[i]);
// 	}
// 	i = -1;
// 	while (++i < THREAD_NUM)
// 	{
// 		if (pthread_join(th[i], NULL)!= 0)
// 		{
// 			perror("failed to join thread");
// 		}
// 	}
// 	pthread_exit(0);
// }


/*
	THIS IS NOT ALLOWED IN PHILO I AM PRETTY MUCH SURE
	In a second time we can create a thread and make it detached out of the box
	with the ptreahd_create second parameter which is the attribute
	to create this second varaible we have to create a pthread_attr_t variable

*/
# define THREAD_NUM 2
void	*routine(void * args)
{
	sleep(1);
	printf("Finished execution\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	int i;

	i = -1;
	pthread_t th[THREAD_NUM];
	pthread_attr_t detachedThread;
	pthread_attr_init(&detachedThread);
	pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);
	while (++i < THREAD_NUM)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL)!= 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		pthread_detach(th[i]);
	}
	i = -1;
	while (++i < THREAD_NUM)
	{
		if (pthread_join(th[i], NULL)!= 0)
		{
			perror("failed to join thread");
		}
	}
	pthread_attr_destroy(&detachedThread);
	pthread_exit(0);
}