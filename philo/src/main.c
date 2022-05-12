/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:07:34 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/12 15:12:57 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
/*
1	argv[0] = Program
2	argv[1] = number_of_philosophers (if only ony the philosopher has to die at some point)
3	argv[2] = time_to_die time_to_die (en millisecondes)
4	argv[3] = time_to_eat (en milisecondes)
5	argv[4] = time_to_sleep (en milisecondes )
6	argv[5] = number_of_times_each_philosopher_must_eat (optionnel si aucun fourni le tout arrête à la mort d'un philosopher)
			  Sinon la simulation arrête lors-ce que tout les philosophers ont mangé au moins number_of_times

	Notes :
			Chaque Philosopher se voit assigner un numéro entre 1 et number_of_philsophers
			Le philosopher NO 1 est assis à côté du philosophie numéro number_of_philosophers
			Les autres suivent cette logique : Philosophe numéro N est assis entre philosophe n - 1 
			et le phislosophe n + 1;
*/




void 	*rountine(void *ptr)
{
	//usleep est en MICRO SECONDE 
	t_philo *p = ptr;
	pthread_mutex_lock(p->fork_left);
	printf("This is from within the lock\n");
	pthread_mutex_unlock(p->fork_left);
// • Les philosophes sont soit en train de manger, de penser ou de dormir.
// Lorsqu’ils mangent, ils ne peuvent pas penser ou dormir.
// Lorsqu’ils dorment, ils ne peuvent pas manger ou penser.
// Enfin, lorsqu’ils pensent, ils ne peuvent pas manger ou dormir.
// 1- Le philosophe mange avec sa fourchette ( à sa droite ) et la fourchette de n - 1 à sa gauche 
// 2-	Quand un philosophe a fini de manger, il repose les fourchettes sur la table et se met à dormir.
// 3- Une fois réveillé, il se remet à penser et il doit manger avant time to die
// La simulation prend fin si un philosophe meurt de faim.
	//eat  and wait till time to eat is done
		//to eat a philosopher must have access to his mutex and the mutex before him
		//it will eat for time_to_eat
	//sleep and wait till time to sleep is done
		//the philosopher will sleep for time_to_sleep
	//think and wait to die
		//the philosopher will think for time_to_die
	return (NULL);
}

int ft_atoi(char *str)
{
	int i;
	int rtn;
	int neg;

	i = 0;
	neg = 1;
	rtn = 0;
	while(str[i])
	{
		if (str[i]  == '-')
		{
			neg = -1;
			i++;
		}
		while(str[i] >= '0' && str[i] <= '9')
		{
			rtn = rtn * 10 + str[i] - '0';
			i++;
		}
	}
	return (neg * rtn);
}

int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_input(int argc, char **argv)
{
	int i;
	
	i = 1;
	while(i < argc)
	{
		if (check_int(argv[i]) != 0)
		{
			printf("Every argument should be an int\n");
			return (1);
		}
		if (ft_atoi(argv[i]) < 0)
		{
			printf("Every argument should be positive\n");
			return (2);
		}
		i++;
	}
	return (0);
}

int	parse_and_initiate(int argc, char **argv, t_pgm *pg)
{
	if (validate_input(argc, argv) != 0)
		return (1);
	if (argc == 5)
		pg->nb_time_to_eat = 0;
	else
		pg->nb_time_to_eat = ft_atoi(argv[5]);
	pg->nb_philos = ft_atoi(argv[1]);
	pg->nb_fork = pg->nb_philos;
	pg->time_to_die = ft_atoi(argv[2]);
	pg->time_to_eat = ft_atoi(argv[3]);
	pg->time_to_sleep = ft_atoi(argv[4]);
	printf("Values provided by the user = \n--------------------------\n");
	printf("This is the number of philo %d\n", pg->nb_philos);
	printf("This is the number of fork %d\n", pg->nb_fork);
	printf("This is the time to die %zu\n", pg->time_to_die);
	printf("This is the time to eat %zu\n", pg->time_to_eat);
	printf("This is the time to sleep %zu\n", pg->time_to_sleep);
	printf("This is time NB time to eat %d\n",pg->nb_time_to_eat);
	printf("--------------------------\n");
	pg->th = malloc(sizeof(pthread_t) * (pg->nb_philos)); // the + 1 is for the extra process to monitor but actually now I use it because I start at 1 instead of 0
	pg->philos = malloc(sizeof(t_philo) * (pg->nb_philos));
	pg->forks = malloc(sizeof(pthread_mutex_t) * pg->nb_fork); //here I allocated an array of mutex
	return (0);
}

int	create_philos_n_mutex(t_pgm *pg)
{
	//I should probablt init the right fork each time
	pg->i = -1;
	while(++pg->i <= pg->nb_fork)
	{
		pg->philos[pg->i].nb_time_eaten = 0;
		pg->philos[pg->i].is_dead = false;
		pg->philos[pg->i].id = pg->i + 1;
		pg->philos[pg->i].pgm = pg;
		pg->philos[pg->i].fork_left = &pg->forks[pg->i];
		pg->philos[pg->i].fork_left = &pg->forks[pg->i + 1 % pg->nb_philos];
		pthread_mutex_init(&pg->forks[pg->i], NULL);
	}
	pg->i = -1;
	while (++pg->i <= pg->nb_philos)
	{
		if (pthread_create(&pg->th[pg->i], NULL, &rountine, &pg->philos[pg->i]) != 0)
		{
			printf("Failed to create thread\n");
			return (1);
		}
		printf("Philo %d is now existing\n", pg->i);
	}
	pg->i = 0;
	while (++pg->i <= pg->nb_philos)
	{
		if (pthread_join(pg->th[pg->i], NULL) != 0)
			return (2);
		printf("Philo %d is DONE existing\n", pg->i);
	}	
	return (0);
}

//après avoir tout initialiser je devrais caller get_time pour avoir le time stamp i
long	get_time()
{
	long rtn;
	
	rtn = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	rtn = rtn + (tv.tv_sec * 1000);
	rtn = rtn + (tv.tv_usec / 1000);

	return (rtn);
}
int main(int argc, char **argv)
{
	t_pgm pg;

	if (argc == 5 || argc == 6)
	{		
		if (parse_and_initiate(argc, argv, &pg) != 0)
			return (1);
		if (create_philos_n_mutex(&pg) != 0)
			return (2);
		//check le state le state de tout le monde	
		free(pg.th);
		free(pg.forks);
		free(pg.philos);
		pg.i = 0;
		while(pg.i < pg.nb_fork)
		{
			pthread_mutex_destroy(&pg.forks[pg.i]);
			pg.i++;
		}
	}
	else
		printf("Not enough args to run the program\n");
}

