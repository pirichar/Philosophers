/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:02:18 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/24 22:53:19 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_pgm(t_pgm *pg, char **argv)
{
	pg->nb_philos = ft_atoi(argv[1]);
	pg->nb_fork = pg->nb_philos;
	pg->game_over = false;
	pg->nb_full_philo = 0;
	pg->time_to_die = ft_atoi(argv[2]);
	pg->time_to_eat = ft_atoi(argv[3]);
	pg->time_to_sleep = ft_atoi(argv[4]);
	pg->queue = create_queue(pg->nb_philos);
	pg->th = malloc(sizeof(pthread_t) * (pg->nb_philos));
	pg->philos = malloc(sizeof(t_philo) * (pg->nb_philos));
	pg->forks = malloc(sizeof(pthread_mutex_t) * pg->nb_fork);
	pthread_mutex_init(&pg->write_mutex, NULL);
	pthread_mutex_init(&pg->death_mutex, NULL);
	pthread_mutex_init(&pg->time_mutex, NULL);
	pthread_mutex_init(&pg->full_mutex, NULL);
	pg->time.initial_time = get_time();
	print_initiation(pg);
	create_philos(pg);
}

void	create_philos(t_pgm *p)
{
	p->i = -1;
	while (++p->i < p->nb_fork)
	{
		p->philos[p->i].nb_time_eaten = 0;
		p->philos[p->i].is_dead = false;
		p->philos[p->i].is_full = false;
		p->philos[p->i].id = p->i + 1;
		p->philos[p->i].pgm = p;
		p->philos[p->i].fork_left = &p->forks[p->i];
		if (p->nb_philos > 1)
			p->philos[p->i].fork_right = &p->forks[(p->i + 1) % p->nb_fork];
		pthread_mutex_init(&p->forks[p->i], NULL);
	}	
}

int	run_all_threads(t_pgm *pg)
{
	pg->i = 0;
	while (pg->i < pg->nb_philos)
	{
		if (pthread_create(&pg->th[pg->i], NULL,
				&routine, &pg->philos[pg->i]) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		pg->i++;
	}
	return (0);
}

void	destroy_mutex(t_pgm *pg)
{
	pg->i = 0;
	while (pg->i < pg->nb_fork)
	{
		pthread_mutex_destroy(&pg->forks[pg->i]);
		pg->i++;
	}
	pthread_mutex_destroy(&pg->write_mutex);
	pthread_mutex_destroy(&pg->time_mutex);
	pthread_mutex_destroy(&pg->death_mutex);
	pthread_mutex_destroy(&pg->full_mutex);
	free(pg->th);
	free(pg->philos);
	free(pg->forks);
}

int	join_thread(t_pgm *pg)
{
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
	}	
	return (0);
}