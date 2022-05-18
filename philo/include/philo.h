/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:09:13 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/18 14:23:46 by pirichar         ###   ########.fr       */
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
	pthread_t		*th;
	pthread_mutex_t	*forks;
	int				i;
	t_philo			*philos;
	long			time_to_eat;
	bool			max_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			start_time;
	long			actual_time;
	int				nb_time_to_eat;
	bool			game_over;
	t_time			time;
}				t_pgm;

//a date cette struct est USELESS
typedef struct s_philo
{
	int				nb_time_eaten;
	bool			is_full;
	bool			is_dead;
	int				id;
	t_pgm			*pgm;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}				t_philo;

//parse.c
int		ft_atoi(char *str);
int		check_int(char *str);
int		validate_input(int argc, char **argv);
int		parse_and_initiate(int argc, char **argv, t_pgm *pg);

//time.c
long	get_time(void);
void	ft_sleep(long time_to_sleep);
void	print_time(t_philo *p);
void	print_status(t_philo *p, char status);

#endif