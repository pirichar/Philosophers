/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:40:39 by pirichar          #+#    #+#             */
/*   Updated: 2022/05/17 15:29:59 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//après avoir tout initialiser je devrais 
//caller get_time pour avoir le time stamp i
long	get_time(void)
{
	long			rtn;
	struct timeval	tv;

	rtn = 0;
	gettimeofday(&tv, NULL);
	rtn = rtn + (tv.tv_sec * 1000);
	rtn = rtn + (tv.tv_usec / 1000);
	return (rtn);
}


void	ft_sleep(long time_to_sleep)
{
	long start_time;
	long actual_time;

	start_time = get_time();
	while(1)
	{
		actual_time = get_time();
		if(start_time + time_to_sleep == actual_time)
			break;
	}
}
