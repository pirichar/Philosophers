/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:53:05 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/24 10:54:23 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	*create_queue(int nb_philo)
{
	int	*queue;
	int	i;
	int	j;

	queue = malloc(nb_philo * sizeof(int));
	i = 1;
	j = 0;
	while (i <= nb_philo)
	{
		queue[j] = i;
		i += 2;
		++j;
	}
	i = 2;
	while (i <= nb_philo)
	{
		queue[j] = i;
		i += 2;
		++j;
	}
	return (queue);
}

void	rotate_queue(int *queue, int size)
{
	int	i;
	int	tmp;

	tmp = queue[0];
	i = 0;
	while (i < size - 1)
	{
		queue[i] = queue[i + 1];
		++i;
	}
	queue[i] = tmp;
}