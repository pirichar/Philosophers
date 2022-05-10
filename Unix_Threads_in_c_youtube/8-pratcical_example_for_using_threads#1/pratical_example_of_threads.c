/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pratical_example_of_threads.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:22:44 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/05 10:15:00 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*
	The problem to solve here :

	Create 10 threads , each taking a unique prime from the primes array 
	and print it on the screen

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
	to the routine function and then free into the 
	routine function what has been allocated
	this is the case because the process might
	 not be executed at the same speed as
	the while loop goes up

	Here in this example we want to create 2 threads
	The first thread is gonna start from 0 to 4 
	the second thread is gonna start from 5 to 9
	We pass i * 5 so that the first thread get 0 
	and the second get i (1) * 5 (5)

	Once its done we use the allready allocated memory in the main 
	to return the output of the function once we gave it the value of the sum
	Then we are gonna gather that value with the pthread_join 
	add it to our global sum and free it at the end

*/
void	*routine(void *arg)
{
	int	start;
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	start = *(int *)arg;
	while (i < 5)
	{
		sum += primes[start + i];
		i++;
	}
	printf("This is the local sum %d\n", sum);
	*(int *)arg = sum;
	return (arg);
}

int main(int argc, char **argv)
{
	int	i;
	int	n;
	int	*a;
	int globalSum;

	i = -1;
	n = 2;
	globalSum = 0;
	pthread_t th[n];
	while(++i < n)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			return (1);
	}
	i = -1;
	while(++i < n)
	{
		int *r;
		if (pthread_join(th[i], (void**)&r) != 0)
			return (2);
		globalSum += *r;
		free (r);
	}
	printf("Global sum is = %d\n", globalSum);
	return (0);
}