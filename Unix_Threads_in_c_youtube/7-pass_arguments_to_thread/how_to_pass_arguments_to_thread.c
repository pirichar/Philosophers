/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_to_pass_arguments_to_thread.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:22:44 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/05 09:37:29 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*
	The problem to solve here :

	Create 10 threads , each taking a unique prime from the primes array and print it on the screen

*/
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
/*
	in the last example we had nothing in our routine function input
	Now instead of not having any we are gonna pass in a void *
	This is what you are gonna be able to pass in to the routine
	This argument is the same as the forth argument in pthread_Create
	So you can pass an argument from pthread_Create to your routine function
	You can actually use it in your routine function

	Lets say we pass a pointer to the index we want to print
	Now we have to dynamically allocate memory on the heap and pass that 
	to the routine function and then free into the routine function what has been allocated
	this is the case because the process might not be executed at the same speed as
	the while loop goes up

*/
void	*routine(void *arg)
{
	int index;
	index = *(int *)arg;
	printf("%d ",primes[index]);
	free (arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	int i;
	int n;
	int *a;
	pthread_t th[10];

	i = -1;
	n = 10;
	while(++i < 10)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			return (1);
	}
	i = -1;
	while(++i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
	}
	return (0);
}