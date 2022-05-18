	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:09:50 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/18 15:13:03 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_initiation(t_pgm *pg)
{
	printf("Values provided by the user = \n--------------------------\n");
	printf("This is the number of philo %d\n", pg->nb_philos);
	printf("This is the number of fork %d\n", pg->nb_fork);
	printf("This is the time to die %zu\n", pg->time_to_die);
	printf("This is the time to eat %zu\n", pg->time_to_eat);
	printf("This is the time to sleep %zu\n", pg->time_to_sleep);
	printf("This is time NB time to eat %d\n", pg->nb_time_to_eat);
	printf("--------------------------\n");
}

//il faudrait que je mette un mutex sur ma fonction au lieu de call printf 14 fois je pourrais juste le caller avec la string que je passe
// ca va juste me prendre un strcomp + passer ce que je veux imprimmer comme du monde
//je pourrais ausi faire une fonction qui retourne le time stamp actuel au lieu de faire get time ici
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
		printf(HBLU"%ld %d is eating and has eaten %d times\n"RESET,
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