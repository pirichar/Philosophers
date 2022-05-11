/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:09:13 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/11 15:35:32 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	int		nb_time_eaten;
	bool	is_dead;

}				t_philo;

typedef struct s_pgm
{
	int 		nb_philos;
	int			nb_fork;
	pthread_t *th;
	int 		i;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time_to_die;
	int 	nb_time_to_eat;
}				t_pgm;










#endif