/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:14 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:39 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->protect_print);
	philo->is_simulation_running = false;
	pthread_mutex_unlock(&philo->protect_print);
}

bool	is_running_philo(t_philo *philo)
{
	bool	aux;

	pthread_mutex_lock(&philo->protect_print);
	aux = philo->is_simulation_running;
	pthread_mutex_unlock(&philo->protect_print);
	return (aux);
}

bool	is_running(t_worker *worker)
{
	bool	aux;

	pthread_mutex_lock(&worker->philo->protect_print);
	aux = worker->philo->is_simulation_running;
	pthread_mutex_unlock(&worker->philo->protect_print);
	return (aux);
}

int	print_philo(t_worker *worker, char *msg)
{
	pthread_mutex_lock(&worker->philo->protect_print);
	if (!worker->philo->is_simulation_running && strcmp(msg, DEAD_MSG) != 0)
	{
		pthread_mutex_unlock(&worker->philo->protect_print);
		return (0);
	}
	printf("%lu Philosofer:%d %s\n", get_time(), worker->id, msg);
	pthread_mutex_unlock(&worker->philo->protect_print);
	return (0);
}
