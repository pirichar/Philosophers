/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:44:32 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/25 06:29:44 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_full(t_philo *p)
{
	bool gameover;

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

// static void	take_forks_and_eat(t_philo *p)
// {
// 	pthread_mutex_lock(p->fork_left);
// 	print_status(p, 'l');
// 	pthread_mutex_lock(p->fork_right);
// 	print_status(p, 'r');
// 	rotate_queue(p->pgm->queue, p->pgm->nb_philos);
// 	p->nb_time_eaten++;
// 	pthread_mutex_lock(&p->pgm->death_mutex);
// 	pthread_mutex_lock(&p->pgm->time_mutex);
// 	p->last_eaten = get_time() - p->pgm->time.initial_time;
// 	pthread_mutex_unlock(&p->pgm->time_mutex);
// 	pthread_mutex_unlock(&p->pgm->death_mutex);
// 	print_status(p, 'e');
// 	ft_sleep(p->pgm->time_to_eat);
// 	pthread_mutex_unlock(p->fork_left);
// 	pthread_mutex_unlock(p->fork_right);
// }

static void	take_forks_and_eat(t_philo *p)
{
	pthread_mutex_lock(p->fork_left);
	print_status(p, 'l');
	pthread_mutex_lock(p->fork_right);
	print_status(p, 'r');
	p->nb_time_eaten++;
	pthread_mutex_lock(&p->pgm->death_mutex);
	pthread_mutex_lock(&p->pgm->time_mutex);
	p->last_eaten = get_time() - p->pgm->time.initial_time;
	pthread_mutex_unlock(&p->pgm->time_mutex);
	pthread_mutex_unlock(&p->pgm->death_mutex);
	print_status(p, 'e');
	ft_sleep(p->pgm->time_to_eat);
	pthread_mutex_unlock(p->fork_left);
	pthread_mutex_unlock(p->fork_right);
}

static void	sleep_routine(t_philo *p)
{
	print_status(p, 's');
	ft_sleep(p->pgm->time_to_sleep);
}


// void	*routine(void *ptr)
// {
// 	t_philo	*p;
// 	p = ptr;
// 	// pthread_mutex_lock(&p->pgm->time_mutex);
// 	p->last_eaten = (get_time() - p->pgm->time.initial_time);
// 	// pthread_mutex_unlock(&p->pgm->time_mutex);
// 	while (1)
// 	{
// 		if (p->pgm->queue[0] == p->id)
// 		{
// 			if (check_full(p))
// 				break;
// 			take_forks_and_eat(p);
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
			break;
		if (p->id % 2 == 0)
			usleep(50);
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

void	*one_philo_routine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	pthread_mutex_lock(p->fork_left);
	print_status(p, 'l');
	ft_sleep(p->pgm->time_to_die);
	print_status(p, 'd');
	pthread_mutex_unlock(p->fork_left);
	return (NULL);
}
