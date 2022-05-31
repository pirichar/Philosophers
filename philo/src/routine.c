/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:44:32 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/31 15:25:02 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	wait_for_fork(t_philo *p, pthread_mutex_t *fork, char side)
{
	while (1)
	{
		if (check_full(p))
			return (1);
		if (pthread_mutex_lock(fork) == 0)
		{
			print_status(p, side);
			return (0);
		}
	}
}

// static void	take_forks_and_eat(t_philo *p)
// {
// 	if (wait_for_fork(p,p->fork_left, 'l') != 0)
// 		return (1);
// 	if (wait_for_fork(p, p->fork_right, 'r') != 0)
// 		return (1);
// 	rotate_queue(p->pgm->queue, p->pgm->nb_philos);
// 	p->nb_time_eaten++;
// 	pthread_mutex_lock(&p->pgm->death_mutex);
// 	p->last_eaten = get_time() - p->pgm->time.initial_time;
// 	pthread_mutex_unlock(&p->pgm->death_mutex);
// 	print_status(p, 'e');
// 	ft_sleep(p->pgm->time_to_eat);
// 	pthread_mutex_unlock(p->fork_left);
// 	pthread_mutex_unlock(p->fork_right);
// }

static int	take_forks_and_eat(t_philo *p)
{
	if (wait_for_fork(p, p->fork_left, 'l') != 0)
		return (1);
	if (wait_for_fork(p, p->fork_right, 'r') != 0)
		return (1);
	p->nb_time_eaten++;
	pthread_mutex_lock(&p->pgm->death_mutex);
	p->last_eaten = get_time() - p->pgm->time.initial_time;
	pthread_mutex_unlock(&p->pgm->death_mutex);
	if (check_full(p))
	{
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		return (1);
	}
	print_status(p, 'e');
	ft_sleep(p->pgm->time_to_eat, p);
	if (check_full(p))
	{
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		return (1);
	}
	pthread_mutex_unlock(p->fork_left);
	pthread_mutex_unlock(p->fork_right);
	return (0);
}

static void	sleep_routine(t_philo *p)
{
	print_status(p, 's');
	ft_sleep(p->pgm->time_to_sleep, p);
}

// void	*routine(void *ptr)
// {
// 	t_philo	*p;
	
// 	p = ptr;
// 	p->last_eaten = (get_time() - p->pgm->time.initial_time);
// 	while (1)
// 	{
// 		if (check_full(p))
// 			break;
// 		if (p->pgm->queue[0] == p->id)
// 		{
// 			if (check_full(p))
// 				break;
// 			if (take_forks_and_eat(p) != 0)
// 				break ;
// 			if (check_full(p))
// 				break;
// 			sleep_routine(p);
// 			if (check_full(p))
// 				break;
// 			print_status(p, 't');
// 		}
// 	}
// 	return (NULL);
// }

void	*routine(void *ptr)
{
	t_philo	*p;
	p = ptr;
	p->last_eaten = (get_time() - p->pgm->time.initial_time);
	while (1)
	{
		if (check_full(p))
			break ;
		if (p->id % 2 == 0)
			usleep(p->pgm->time_to_die / 10);
		if (take_forks_and_eat(p) != 0)
			break ;
		if (check_full(p))
			break ;
		sleep_routine(p);
		if (check_full(p))
			break ;
		print_status(p, 't');
	}
	return (NULL);
}

void	*one_philo_routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	pthread_mutex_lock(p->fork_left);
	print_status(p, 'l');
	ft_sleep(p->pgm->time_to_die, p);
	print_status(p, 'd');
	pthread_mutex_unlock(p->fork_left);
	return (NULL);
}
