/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/24 22:57:18 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//***usleep est en MICRO SECONDE***
//***LE USER ME DONNE EN MILISECONDE LES TEMPS**
//***CHACUN DES CHIFFRES DOIT ETRE MULTIPLIER PAR 1000***


int	check_for_death(t_pgm *pg, int i)
{
	pg->actual_time = get_time() - pg->time.initial_time;
	pthread_mutex_lock(&pg->death_mutex);
	if (pg->actual_time >= (pg->philos[i].last_eaten + pg->time_to_die))
	{
		pg->game_over = true;
		pthread_mutex_unlock(&pg->death_mutex);	
		print_status(&pg->philos[i], 'd');
		return (1);
	}
	else
		pthread_mutex_unlock(&pg->death_mutex);	
	return (0);
}

int check_for_full(t_pgm *pg)
{
	if (pg->nb_time_to_eat != 0)	
	{
		pthread_mutex_lock(&pg->full_mutex);
		if (pg->nb_full_philo >= pg->nb_philos)
		{
			pg->game_over = true;
			printf("Everyone is now full🍝\n");
			pthread_mutex_unlock(&pg->full_mutex);
			return (1);
		}
		else
			pthread_mutex_unlock(&pg->full_mutex);
	}
	return (0);
}

int	check_for_end(t_pgm *pg)
{
	int	i;

	i = 0;
	while (1)
	{
		if (check_for_death(pg, i) == 1)
			return (1);
		if (check_for_full(pg) == 1)
			return (1);
		if (i == pg->nb_philos - 1)
			i = -1;
		i++;
		usleep(100);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_pgm	pg;
	int		i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (parse_input(argc, argv, &pg) != 0)
			return (1);
		init_pgm(&pg, argv);
		if (pg.nb_philos == 1)
			pthread_create(&pg.th[0], NULL, &one_philo_routine, &pg.philos[0]);
		else
		{
			if (run_all_threads(&pg) != 0)
				return (2);
			if (check_for_end(&pg) == 1)
			{
				join_thread(&pg);
				destroy_mutex(&pg);
				return (3);
				// exit(3);
			}
		}
		join_thread(&pg);
	}
	return (0);
}
