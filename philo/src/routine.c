/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:44:32 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/23 18:35:03 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks_and_eat(t_philo *p)
{
	if (p->id % 2 != 0)
	{
		pthread_mutex_lock(p->fork_left);
		print_status(p, 'l');
		pthread_mutex_lock(p->fork_right);
		print_status(p, 'r');
		//rotate queue
		p->nb_time_eaten++;
		pthread_mutex_lock(&p->pgm->time_mutex);
		p->last_eaten = get_time() - p->pgm->time.initial_time;
		pthread_mutex_unlock(&p->pgm->time_mutex);
		print_status(p, 'e');
		ft_sleep(p->pgm->time_to_eat);
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
	}
	else
	{
		usleep(50);
		pthread_mutex_lock(p->fork_left);
		print_status(p, 'r');
		pthread_mutex_lock(p->fork_right);
		print_status(p, 'l');
		p->nb_time_eaten++;
		pthread_mutex_lock(&p->pgm->time_mutex);
		p->last_eaten = get_time() - p->pgm->time.initial_time;
		pthread_mutex_unlock(&p->pgm->time_mutex);
		print_status(p, 'e');
		ft_sleep(p->pgm->time_to_eat);
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
	}
}

static void	sleep_routine(t_philo *p)
{
	print_status(p, 's');
	ft_sleep(p->pgm->time_to_sleep);
}

static bool	check_full(t_philo *p)
{
	bool gameover;

	pthread_mutex_lock(&p->pgm->full_mutex);
	if (p->pgm->max_eat == true)
		if (p->nb_time_eaten >= p->pgm->nb_time_to_eat) 
		{
			p->is_full = 1;
			p->pgm->nb_full_philo++;
		}
	pthread_mutex_unlock(&p->pgm->full_mutex);
	pthread_mutex_lock(&p->pgm->death_mutex);
	gameover = p->pgm->game_over;
	pthread_mutex_unlock(&p->pgm->death_mutex);
	return (gameover);
}

void	*routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	p->last_eaten = (get_time() - p->pgm->time.initial_time);
	while (1)
	{
		//faire un if ici avec si mon élément est le premier de ma queue
		if (check_full(p))
			break;
		take_forks_and_eat(p);
		if (check_full(p))
			break;
		sleep_routine(p);
		if (check_full(p))
			break;
		print_status(p, 't');
	}
	return (NULL);
}