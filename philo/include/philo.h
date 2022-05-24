/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:09:13 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/24 10:41:21 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include "./colors.h"

typedef struct s_philo	t_philo;
// typedef struct s_time t_time;

typedef struct s_time
{
	long	initial_time;
	long	time_atm;
	long	start_thinking;
}				t_time;

typedef struct s_pgm
{
	int				nb_philos;
	int				nb_fork;
	int				nb_full_philo;
	pthread_t		*th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	full_mutex;
	int				i;
	t_philo			*philos;
	long			time_to_eat;
	bool			max_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			actual_time;
	int				nb_time_to_eat;
	int				*queue;
	bool			game_over;
	t_time			time;
}				t_pgm;

//a date cette struct est USELESS
typedef struct s_philo
{
	int				nb_time_eaten;
	bool			is_full;
	bool			is_dead;
	long			last_eaten;
	int				id;
	t_pgm			*pgm;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}				t_philo;


//main.c


//print.c
void	print_time(t_philo *p);
void	print_status(t_philo *p, char status);
void	print_initiation(t_pgm *pg);

//parse.c
int		ft_atoi(char *str);
int		check_int(char *str);
int		validate_input(int argc, char **argv);
int		parse_input(int argc, char **argv, t_pgm *pg);


//time.c
long	get_time(void);
void	ft_sleep(long time_to_sleep);

//create.c
void	create_philos(t_pgm *pg);
int		run_all_threads(t_pgm *pg);
void	init_pgm(t_pgm *pg, char **argv);

//routine.c
void	*routine(void *ptr);

//queue.c
int	*create_queue(int philo_count);
void	rotate_queue(int *queue, int size);

#endif