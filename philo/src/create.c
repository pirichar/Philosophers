/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:02:18 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/18 15:29:04 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		pg->philos[pg->i].fork_right = &pg->forks[pg->i + 1 % pg->nb_philos];
		pthread_mutex_init(&pg->forks[pg->i], NULL);
	}	
}

int	create_philos_n_mutex(t_pgm *pg)
{
	create_philos(pg);
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_create(&pg->th[pg->i], NULL,
				&rountine, &pg->philos[pg->i]) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
	}
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
		printf("Philo %d is DONE existing\n", (pg->i) + 1);
	}	
	return (0);
}