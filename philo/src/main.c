/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/20 14:19:27 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//***usleep est en MICRO SECONDE***
//***LE USER ME DONNE EN MILISECONDE LES TEMPS**
//***CHACUN DES CHIFFRES DOIT ETRE MULTIPLIER PAR 1000***
void	destroy_mutex(t_pgm *pg)
{
	pg->i = 0;
	while (pg->i < pg->nb_fork)
	{
		pthread_mutex_destroy(&pg->forks[pg->i]);
		pg->i++;
	}
	pthread_mutex_destroy(&pg->write_mutex);
}

int	join_thread(t_pgm *pg)
{
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
	}	
	return (0);
}

int		check_for_death(t_pgm *pg)
{
	int i = 0;
	while(1)
	{
		pg->actual_time = get_time() - pg->time.initial_time;
		if (pg->actual_time >= (pg->philos[i].last_eaten + pg->time_to_die))
		{
			print_status(&pg->philos[i], 'd');
			pg->game_over = true;
			pg->philos[i].is_dead = true;
			return (1);
		}
		if (i == pg->nb_philos - 1)
			i = -1;
		i++;
	}
	return (0);
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
int	main(int argc, char **argv)
{
	t_pgm	pg;
	int i;

	i = 0;
	if (argc == 5 || argc == 6)
	{	
		if (parse_input(argc, argv, &pg) != 0)
			return (1);
		init_pgm(&pg, argv);
		pg.time.initial_time = get_time();
		create_philos(&pg);
		if (pg.nb_philos == 1)
			pthread_create(&pg.th[0], NULL, &one_philo_routine, &pg.philos[0]);
		else
		{
			if (run_all_threads(&pg) != 0)
				return (2);
			if (check_for_death(&pg) == 1)
			{
				destroy_mutex(&pg);
				exit (2);
			}
		}
		join_thread(&pg);
	}
	else
		printf("Not enough args to run the program\n");
	return (0);
}
