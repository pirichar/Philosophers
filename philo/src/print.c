/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:09:50 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/31 07:49:06 by pirichar         ###   ########.fr       */
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

//il faudrait que je mette un mutex sur ma fonction au lieu de 
//call printf 14 fois je pourrais juste le caller avec la string que je passe
// ca va juste me prendre un strcomp + passer ce que je veux imprimmer 
//comme du monde je pourrais ausi faire une fonction qui retourne 
//le time stamp actuel au lieu de faire get time ici
// void	print_status(t_philo *p, char status)
// {
// 	pthread_mutex_lock(&p->pgm->death_mutex);
// 	// pthread_mutex_lock(&p->pgm->write_mutex);
// 	if (p->pgm->game_over == false || status == 'd')
// 	{
// 		p->pgm->time.atm = get_time() - p->pgm->time.initial_time;
// 		if (status == 'l')
// 			printf(HGRN"%ld %d has taken a fork????\n"RESET,
// 				(p->pgm->time.atm), p->id);
// 		if (status == 'r')
// 			printf(HGRN"%ld %d has taken a fork????\n"RESET,
// 				(p->pgm->time.atm), p->id);
// 		if (status == 'e')
// 			printf(HBLU"%ld %d is eating ???? and has eaten %d times ???\n"RESET,
// 				(p->pgm->time.atm), p->id, p->nb_time_eaten);
// 		if (status == 's')
// 			printf(HMAG"%ld %d is sleeping????\n"RESET, (p->pgm->time.atm), p->id);
// 		if (status == 't')
// 			printf(HCYN"%ld %d is thinking????\n"RESET, (p->pgm->time.atm), p->id);
// 		if (status == 'd')
// 			printf(HRED"%ld %d is dead ????\n"RESET, (p->pgm->time.atm), p->id);
// 	}
// 	pthread_mutex_unlock(&p->pgm->death_mutex);
// 	// pthread_mutex_unlock(&p->pgm->write_mutex);
// }
void	print_status(t_philo *p, char status)
{
	p->pgm->time.atm = get_time() - p->pgm->time.initial_time;
	pthread_mutex_lock(&p->pgm->death_mutex);
	pthread_mutex_lock(&p->pgm->full_mutex);
	if (p->pgm->game_over == false || status == 'd')
	{
		if (status == 'l')
			printf(HGRN"%ld %d has taken a fork????\n"RESET,
				(p->pgm->time.atm), p->id);
		if (status == 'r')
			printf(HGRN"%ld %d has taken a fork????\n"RESET,
				(p->pgm->time.atm), p->id);
		if (status == 'e')
			printf(HBLU"%ld %d is eating ????\n"RESET,
				(p->pgm->time.atm), p->id);
		if (status == 's')
			printf(HMAG"%ld %d is sleeping????\n"RESET, (p->pgm->time.atm), p->id);
		if (status == 't')
			printf(HCYN"%ld %d is thinking????\n"RESET, (p->pgm->time.atm), p->id);
		if (status == 'd')
			printf(HRED"%ld %d is dead ????\n"RESET, (p->pgm->time.atm), p->id);
	}
	pthread_mutex_unlock(&p->pgm->death_mutex);
	pthread_mutex_unlock(&p->pgm->full_mutex);
}

void	print_time(t_philo *p)
{
	printf("This is last time eaten %ld for %d\n", (p->last_eaten), p->id);
	printf("This is time to die %ld for %d\n", (p->pgm->time_to_die), p->id);
	printf("This is the actual time %ld for %d\n", (p->pgm->actual_time), p->id);
	printf("This is the start time + time_to_die for %d = %ld\nt", p->id,
		((p->last_eaten) + p->pgm->time_to_die));
	printf("this is actual time = %ld for %d\n",
		(p->pgm->actual_time), p->id);
}
