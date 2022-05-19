/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:27:13 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/18 20:16:55 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
1	argv[0] = Program
2	argv[1] = number_of_philosophers 
	(if only ony the philosopher has to die at some point)
3	argv[2] = time_to_die time_to_die (en millisecondes)
4	argv[3] = time_to_eat (en milisecondes)
5	argv[4] = time_to_sleep (en milisecondes )
6	argv[5] = number_of_times_each_philosopher_must_eat (optionnel 
	si aucun fourni le tout arrête à la mort d'un philosopher)
			  Sinon la simulation arrête lors-ce que tout les philosophers
			   ont mangé au moins number_of_times

	Notes :
			Chaque Philosopher se voit assigner un numéro entre
			 1 et number_of_philsophers
			Le philosopher NO 1 est assis à côté du philosophie 
			numéro number_of_philosophers
			Les autres suivent cette logique : Philosophe numéro 
			N est assis entre philosophe n - 1 
			et le phislosophe n + 1;
*/

int	ft_atoi(char *str)
{
	int	i;
	int	rtn;
	int	neg;

	i = 0;
	neg = 1;
	rtn = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			neg = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			rtn = rtn * 10 + str[i] - '0';
			i++;
		}
	}
	return (neg * rtn);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_int(argv[i]) != 0)
		{
			printf("Every argument should be an int\n");
			return (1);
		}
		if (ft_atoi(argv[i]) < 0)
		{
			printf("Every argument should be positive\n");
			return (2);
		}
		i++;
	}
	return (0);
}

int	parse_and_initiate(int argc, char **argv, t_pgm *pg)
{
	if (validate_input(argc, argv) != 0)
		return (1);
	if (argc == 5)
	{
		pg->max_eat = false;
		pg->nb_time_to_eat = 0;
	}
	else
	{
		pg->max_eat = true;
		pg->nb_time_to_eat = ft_atoi(argv[5]);
	}
	init_pgm(pg, argv);
	return (0);
}
