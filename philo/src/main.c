/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/10 14:27:46 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
/*
1	argv[0] = Program
2	argv[1] = number_of_philosophers (if only ony the philosopher has to die at some point)
3	argv[2] = time_to_die time_to_die (en millisecondes)
4	argv[3] = time_to_eat (en milisecondes)
5	argv[4] = time_to_sleep (en milisecondes )
6	argv[5] = number_of_times_each_philosopher_must_eat (optionnel si aucun fourni le tout arrête à la mort d'un philosopher)
			  Sinon la simulation arrête lors-ce que tout les philosophers ont mangé au moins number_of_times

	Notes :
			Chaque Philosopher se voit assigner un numéro entre 1 et number_of_philsophers
			Le philosopher NO 1 est assis à côté du philosophie numéro number_of_philosophers
			Les autres suivent cette logique : Philosophe numéro N est assis entre philosophe n - 1 
			et le phislosophe n + 1;
*/
void 	*rountine()
{
	//eat  and wait till time to eat is done
	//sleep and wait till time to sleep is done
	//think and wait to die
	return (NULL);
}

int ft_atoi(char *str)
{
	int i;
	int rtn;
	int neg;

	i = 0;
	neg = 1;
	rtn = 0;
	while(str[i])
	{
		if (str[i]  == '-')
		{
			neg = -1;
			i++;
		}
		while(str[i] >= '0' && str[i] <= '9')
		{
			rtn = rtn * 10 + str[i] - '0';
			i++;
		}
	}
	return (neg * rtn);
}

// void	parse_input(int argc, char **argv)
// {

// }


//maybe I should separate the pthread_join side of this function to something else; lets see
// for now this function takes as input the arguments but could only take argv[1]
//then it mallocs an array to put my threads into with the atoi of argv[1]
// I could probably init the forks here as well ?
// Should I get the output of pthread_Create and assign that to a philo as I create them ?
int	init_philos(char **argv, t_pgm *pg)
{
	pg->nb_philos = ft_atoi(argv[1]);
	printf("This is the number of philo provided %d\n", pg->nb_philos);
	pg->th = malloc(sizeof(pthread_t) * pg->nb_philos + 1); // the + 1 is for the extra process
	while (pg->i <= pg->nb_philos)
	{
		if (pthread_create(&pg->th[pg->i], NULL, &rountine, NULL) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		printf("Philo %d is now existing\n", pg->i);
		pg->i++;
	}
	pg->i = 1;
	while (pg->i <= pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
		printf("Philo %d is DONE existing\n", pg->i);
		pg->i++;
	}	
	return (0);
}

int main(int argc, char **argv)
{
	t_pgm pg;

	pg.i = 1;
	if (argc > 5)
	{
		//here I should or COULD par the whole input and return different stuff
		//if the value of my return is not 0 I could exit or something like that
		//I could also print the errors into the parse function
		if (ft_atoi(argv[1]) < 1)
		{
			printf("Provide a positive amount of philosophers please\n");
			return (1);
		}
		//Here I want to init my philos so basically I could do that in a function
		// pg.nb_philos = ft_atoi(argv[1]);
		// printf("This is the number of philo provided %d\n", pg.nb_philos);
		// pg.th = malloc(sizeof(pthread_t) * pg.nb_philos + 1); // the + 1 is for the extra process
		// while (pg.i <= pg.nb_philos)
		// {
		// 	if (pthread_create(&pg.th[pg.i], NULL, &rountine, NULL) != 0)
		// 	{
		// 		printf("Failed to create thread\n");
		// 		return (1);
		// 	}
		// 	printf("Philo %d is now existing\n", pg.i);
		// 	pg.i++;
		// }
		// pg.i = 1;
		// while (pg.i <= pg.nb_philos)
		// {
		// 	if (pthread_join(pg.th[pg.i], NULL) != 0)
		// 		return (2);
		// 	printf("Philo %d is DONE existing\n", pg.i);
		// 	pg.i++;
		// }	
		//use argv[1] to create the right amount of process  + 1 ( the process that will look over everyone)
		//also you can use the number of philosophers to create the ammount of forks (mutex)
		if (init_philos(argv, &pg) != 0)
			return (1);
		//maybe I init the number of fork here ? 
		//there is one work in between each philosopher so if there is 2 there will be 2 fork;
		// that means that exept if there is one philosopher whtere will be the same amount of philo as the amount of fork
		free(pg.th);
	}
	else
		printf("Not enough args to run the program\n");
}

