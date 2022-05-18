/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/18 14:31:55 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// • Les philosophes sont soit en train de manger, de penser ou de dormir.
// Lorsqu’ils mangent, ils ne peuvent pas penser ou dormir.
// Lorsqu’ils dorment, ils ne peuvent pas manger ou penser.
// Enfin, lorsqu’ils pensent, ils ne peuvent pas manger ou dormir.
// 1- Le philosophe mange avec sa fourchette ( à sa droite )
//	 et la fourchette de n - 1 à sa gauche 
// 2-	Quand un philosophe a fini de manger, il repose 
//	les fourchettes sur la table et se met à dormir.
// 3- Une fois réveillé, il se remet à penser et il doit manger avant ttd
// La simulation prend fin si un philosophe meurt de faim.
	//eat  and wait till time to eat is done
		//to eat a philosopher must have access to 
		//his mutex and the mutex before him
		//it will eat for time_to_eat
	//sleep and wait till time to sleep is done
		//the philosopher will sleep for time_to_sleep
	//think and wait to die
		//the philosopher will think for time_to_die

//***usleep est en MICRO SECONDE***
//***LE USER ME DONNE EN MILISECONDE LES TEMPS**
//***CHACUN DES CHIFFRES DOIT ETRE MULTIPLIER PAR 1000***

void	take_forks_and_eat(t_philo *p)
{
	pthread_mutex_lock(p->fork_left);
	print_status(p, 'l');
	pthread_mutex_lock(p->fork_right);
	print_status(p, 'r');
	//Eating
	print_status(p, 'e');
	p->pgm->start_time = get_time();
	ft_sleep(p->pgm->time_to_eat);
	pthread_mutex_unlock(p->fork_left);
	pthread_mutex_unlock(p->fork_right);

}
void	*rountine(void *ptr)
{
	t_philo	*p;

	p = ptr;
	p->pgm->start_time = get_time();
	while (1)
	{
		p->pgm->actual_time = get_time();	
		if (p->pgm->max_eat == true)
			if (p->nb_time_eaten >= p->pgm->nb_time_to_eat) 
				break;
		//forks
		take_forks_and_eat(p);
		//sleep
		print_status(p, 's');
		ft_sleep(p->pgm->time_to_sleep);
		//Think
		print_status(p, 't');
		print_time(p);
		p->pgm->actual_time = get_time();		
		if ( p->pgm->actual_time >= p->pgm->start_time + p->pgm->time_to_die )
		{
			print_status(p, 'd');
			p->is_dead = true;
			break;
		}	
	}
	return (NULL);
}

void	create_philos(t_pgm *pg)
{
	pg->i = -1;
	while (++pg->i < pg->nb_fork)
	{
		pg->philos[pg->i].nb_time_eaten = 0;
		pg->philos[pg->i].is_dead = false;
		pg->philos[pg->i].is_full = false;
		pg->philos[pg->i].id = pg->i + 1;
		pg->philos[pg->i].pgm = pg;
		pg->philos[pg->i].fork_left = &pg->forks[pg->i];
		pg->philos[pg->i].fork_right = &pg->forks[pg->i + 1 % pg->nb_philos];
		pthread_mutex_init(&pg->forks[pg->i], NULL);
	}	
}

int	create_philos_n_mutex(t_pgm *pg)
{
	create_philos(pg);
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_create(&pg->th[pg->i], NULL,
				&rountine, &pg->philos[pg->i]) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		printf("Philo %d is now existing\n", (pg->i) + 1);
	}
	pg->i = -1;
	while (++pg->i < pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
		printf("Philo %d is DONE existing\n", (pg->i) + 1);
	}	
	return (0);
}

int	main(int argc, char **argv)
{
	t_pgm	pg;

	if (argc == 5 || argc == 6)
	{	
		if (parse_and_initiate(argc, argv, &pg) != 0)
			return (1);
		pg.time.initial_time = get_time();
		if (create_philos_n_mutex(&pg) != 0)
			return (2);
		//check le state le state de tout le monde	
		//while(1) check le state pi sors si kk1 meurt ?
		free(pg.th);
		free(pg.forks);
		free(pg.philos);
		pg.i = 0;
		while (pg.i < pg.nb_fork)
		{
			pthread_mutex_destroy(&pg.forks[pg.i]);
			pg.i++;
		}
	}
	else
		printf("Not enough args to run the program\n");
}
