/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/19 13:11:36 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//***usleep est en MICRO SECONDE***
//***LE USER ME DONNE EN MILISECONDE LES TEMPS**
//***CHACUN DES CHIFFRES DOIT ETRE MULTIPLIER PAR 1000***
void	destroy_mutex(t_pgm *pg)
{
	pg->i = 0;
	while (pg->i < pg->nb_fork)
	{
		pthread_mutex_destroy(&pg->forks[pg->i]);
		pg->i++;
	}
	pthread_mutex_destroy(&pg->write_mutex);
}

int	join_thread(t_pgm *pg)
{
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
		printf("Philo %d is DONE existing\n", (pg->i) + 1);
	}	
	return (0);
}

int		check_for_death(t_pgm *pg)
{
	int i = 0;
	while(i < pg->nb_philos)
	{
		if (pg->philos[i].is_dead == true)
		{
			print_status(&pg->philos[i], 'd');
			return (1);
		}
		if (i == pg->nb_philos - 1)
			i = -1;
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_pgm	pg;
	int i;

	i = 0;
	if (argc == 5 || argc == 6)
	{	
		if (parse_and_initiate(argc, argv, &pg) != 0)
			return (1);
		pg.time.initial_time = get_time();
		if (create_philos_n_mutex(&pg) != 0)
			return (2);
		if (check_for_death(&pg) == 1)
		{
			destroy_mutex(&pg);
			return (2);
		}
		join_thread(&pg);
	}
	else
		printf("Not enough args to run the program\n");
	return (0);
}
