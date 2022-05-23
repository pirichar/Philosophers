/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:44:32 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/23 14:24:02 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks_and_eat(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->fork_left);
		print_status(p, 'l');
		pthread_mutex_lock(p->fork_right);
		print_status(p, 'r');
		p->nb_time_eaten++;
		pthread_mutex_lock(&p->pgm->time_mutex);
		p->last_eaten = get_time() - p->pgm->time.initial_time;
		print_status(p, 'e');
		pthread_mutex_unlock(&p->pgm->time_mutex);
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
		print_status(p, 'e');
		pthread_mutex_unlock(&p->pgm->time_mutex);
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

static void	check_full(t_philo *p)
{
	pthread_mutex_lock(&p->pgm->full_mutex);
	if (p->pgm->max_eat == true)
		if (p->nb_time_eaten >= p->pgm->nb_time_to_eat) 
		{
			p->is_full = 1;
			p->pgm->nb_full_philo++;
		}
	pthread_mutex_unlock(&p->pgm->full_mutex);
}

void	*rountine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	p->last_eaten = (get_time() - p->pgm->time.initial_time);
	while (1)
	{
		check_full(p);
		take_forks_and_eat(p);
		check_full(p);
		sleep_routine(p);
		print_status(p, 't');
	}
	return (NULL);
}