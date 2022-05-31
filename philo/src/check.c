/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:59:30 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/31 12:27:33 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// 3 fonctions appelées par le main pour vérifier l'état de la partie
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

int	check_for_full(t_pgm *pg)
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
		if (pg->nb_time_to_eat != 0)
		{	
			if (check_for_full(pg) == 1)
				return (1);
		}
		if (i == pg->nb_philos - 1)
			i = -1;
		i++;
		usleep(100);
	}
	return (0);
}

// fonction appellée par la fonction de routine pour vérifier son état
bool	check_full(t_philo *p)
{
	bool	gameover;

	if (p->pgm->max_eat == true)
	{
		pthread_mutex_lock(&p->pgm->full_mutex);
		if (p->nb_time_eaten >= p->pgm->nb_time_to_eat)
		{
			p->is_full = 1;
			p->pgm->nb_full_philo++;
		}
		pthread_mutex_unlock(&p->pgm->full_mutex);
	}
	pthread_mutex_lock(&p->pgm->death_mutex);
	gameover = p->pgm->game_over;
	pthread_mutex_unlock(&p->pgm->death_mutex);
	return (gameover);
}
