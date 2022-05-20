/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:44:32 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/20 11:06:57 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks_and_eat(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->fork_right);
		print_status(p, 'r');
		pthread_mutex_lock(p->fork_left);
		print_status(p, 'l');
		//Eating
		p->nb_time_eaten++;
		p->last_eaten = get_time() - p->pgm->time.initial_time;
		print_status(p, 'e');
		ft_sleep(p->pgm->time_to_eat);
		pthread_mutex_unlock(p->fork_right);
		pthread_mutex_unlock(p->fork_left);
	}
	else
	{
		pthread_mutex_lock(p->fork_left);
		print_status(p, 'l');
		pthread_mutex_lock(p->fork_right);
		print_status(p, 'r');
		//Eating
		p->nb_time_eaten++;
		print_status(p, 'e');
		p->last_eaten = get_time() - p->pgm->time.initial_time;
		ft_sleep(p->pgm->time_to_eat);
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
	}
}

void	sleep_routine(t_philo *p)
{
	print_status(p, 's');
	ft_sleep(p->pgm->time_to_sleep);
}


void	*rountine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	p->last_eaten = (get_time() - p->pgm->time.initial_time);
	while (1)
	{
		if (p->pgm->max_eat == true)
			if (p->nb_time_eaten >= p->pgm->nb_time_to_eat) 
			{
				p->is_full = 1;//probablement que ici je devrais me faire un array avec mes is_full
								//pour tout mes philos
				break;
			}
		take_forks_and_eat(p);
		sleep_routine(p);
		print_status(p, 't');
	}
	return (NULL);
}