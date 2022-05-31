/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/31 12:04:47 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//***usleep est en MICRO SECONDE***
//***LE USER ME DONNE EN MILISECONDE LES TEMPS**
//***CHACUN DES CHIFFRES DOIT ETRE MULTIPLIER PAR 1000***

void	a_lonely_life(t_pgm *pg)
{
	pthread_create(&pg->th[0], NULL, &one_philo_routine, &pg->philos[0]);
	pthread_join(pg->th[0], NULL);
	destroy_mutex(pg);
}

int	main(int argc, char **argv)
{
	t_pgm	pg;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(argc, argv, &pg) != 0)
			return (1);
		init_pgm(&pg, argv);
		if (pg.nb_philos == 1)
			a_lonely_life(&pg);
		else
		{
			if (run_all_threads(&pg) != 0)
				return (2);
			if (check_for_end(&pg) == 1)
			{
				join_thread(&pg);
				destroy_mutex(&pg);
				return (3);
			}
		}
		join_thread(&pg);
	}
	return (0);
}
