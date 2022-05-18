/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:40:39 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/18 14:30:01 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//après avoir tout initialiser je devrais 
//caller get_time pour avoir le time stamp i
long	get_time(void)
{
	long			rtn;
	struct timeval	tv;

	rtn = 0;
	gettimeofday(&tv, NULL);
	rtn = rtn + (tv.tv_sec * 1000);
	rtn = rtn + (tv.tv_usec / 1000);
	return (rtn);
}


void	ft_sleep(long time_to_sleep)
{
	long start_time;
	long actual_time;

	start_time = get_time();
	while(1)
	{
		actual_time = get_time();
		if(start_time + time_to_sleep == actual_time)
			break;
	}
}

void	print_status(t_philo *p, char status)
{
	if (status == 't')
				p->pgm->time.start_thinking = get_time();
	else
		p->pgm->time.time_atm = get_time();
	if (status == 'l')
		printf(HGRN"%ld %d has taken a fork \n"RESET,
			(p->pgm->time.time_atm - p->pgm->time.initial_time), p->id);
	if (status == 'r')
		printf(HGRN"%ld %d has taken a fork\n"RESET,
			(p->pgm->time.time_atm - p->pgm->time.initial_time), p->id);
	if (status == 'e')
	{
		p->nb_time_eaten++;
		printf(HBLU"%ld %d is eating and has eat %d times\n"RESET,
			(p->pgm->time.time_atm - p->pgm->time.initial_time), p->id, p->nb_time_eaten);
	}
	if (status == 's')
		printf(HMAG"%ld %d is sleeping\n"RESET,
			(p->pgm->time.time_atm - p->pgm->time.initial_time), p->id);
	if (status == 't')
		printf(HCYN"%ld %d is thiking\n"RESET,
			(p->pgm->time.start_thinking - p->pgm->time.initial_time), p->id);
	if (status == 'd')
		printf(HRED"%ld %d is dead\n"RESET,
			(p->pgm->time.time_atm - p->pgm->time.initial_time), p->id);
}


void	print_time(t_philo *p)
{
	printf("This is the start time %ld for %d\n",(p->pgm->start_time - p->pgm->time.initial_time), p->id);
	printf("This is time to die %ld for %d\n",(p->pgm->time_to_die), p->id);
	printf("This is the actual time %ld for %d\n",(p->pgm->actual_time - p->pgm->time.initial_time), p->id);
	printf("This is the start time + time_to_die for %d = %ld\nthis is actual time = %ld for %d\n", p->id,
	((p->pgm->start_time - p->pgm->time.initial_time) + p->pgm->time_to_die),
		(p->pgm->actual_time - p->pgm->time.initial_time), p->id);
}