/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:02:18 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/19 10:46:05 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_pgm(t_pgm *pg, char **argv)
{
	pg->nb_philos = ft_atoi(argv[1]);
	pg->nb_fork = pg->nb_philos;
	pg->time_to_die = ft_atoi(argv[2]);
	pg->time_to_eat = ft_atoi(argv[3]);
	pg->time_to_sleep = ft_atoi(argv[4]);
	pg->th = malloc(sizeof(pthread_t) * (pg->nb_philos));
	pg->philos = malloc(sizeof(t_philo) * (pg->nb_philos));
	pg->forks = malloc(sizeof(pthread_mutex_t) * pg->nb_fork);
	pthread_mutex_init(&pg->write_mutex, NULL);
	print_initiation(pg);
}

void	create_philos(t_pgm *pg)
{
	pg->i = -1;
	while (++pg->i < pg->nb_fork)
	{
		pg->philos[pg->i].nb_time_eaten = 0;
		pg->philos[pg->i].is_dead = false;
		pg->philos[pg->i].is_full = false;
		pg->philos[pg->i].id = pg->i + 1;
		pg->philos[pg->i].pgm = pg;
		pg->philos[pg->i].fork_left = &pg->forks[pg->i];
		pg->philos[pg->i].fork_right = &pg->forks[(pg->i + 1) % pg->nb_fork];
		pthread_mutex_init(&pg->forks[pg->i], NULL);
	}	
}

int	create_philos_n_mutex(t_pgm *pg)
{
	create_philos(pg);
	pg->i = 0;
	while (pg->i < pg->nb_philos)
	{
		if (pthread_create(&pg->th[pg->i], NULL,
				&rountine, &pg->philos[pg->i]) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		pg->i++;
	}
	return (0);
}
