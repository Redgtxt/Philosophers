/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:10 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/21 16:22:49 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	my_gettimeofday(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * MILISECONDS + tv.tv_usec / MILISECONDS);
}

unsigned long int	get_time(void)
{
	static unsigned long int	start_time;

	if (!start_time)
	{
		start_time = my_gettimeofday();
		return (0);
	}
	else
	{
		return (my_gettimeofday() - start_time);
	}
}

void	ft_usleep(unsigned long int time, t_worker *worker)
{
	unsigned long int	start_time;

	start_time = get_time();
	while (get_time() - start_time < time && is_running(worker))
	{
		usleep(10);
	}
}
