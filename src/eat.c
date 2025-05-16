/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:22 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:24 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_one(t_worker *worker)
{
	pthread_mutex_lock(worker->right_fork);
	print_philo(worker, FORK_MSG);
	while (is_running(worker))
	{
		usleep(100);
	}
	pthread_mutex_unlock(worker->right_fork);
	return (0);
}

static void	eaten_enough(t_worker *worker)
{
	if (worker->philo->num_of_times_each_philo_eat > 0
		&& worker->n_meals == worker->philo->num_of_times_each_philo_eat)
	{
		pthread_mutex_lock(&worker->protect_time);
		worker->is_full = true;
		pthread_mutex_unlock(&worker->protect_time);
	}
}

int	eat(t_worker *worker)
{
	if (worker->num_of_philos == 1)
		return (handle_one(worker));
	if (!is_running(worker))
		return (0);
	pthread_mutex_lock(worker->right_fork);
	print_philo(worker, FORK_MSG);
	pthread_mutex_lock(worker->left_fork);
	print_philo(worker, FORK_MSG);
	pthread_mutex_lock(&worker->protect_time);
	worker->last_meal_time = get_time();
	pthread_mutex_unlock(&worker->protect_time);
	print_philo(worker, EAT_MSG);
	ft_usleep(worker->time_to_eat);
	pthread_mutex_lock(&worker->protect_time);
	worker->n_meals++;
	pthread_mutex_unlock(&worker->protect_time);
	eaten_enough(worker);
	pthread_mutex_unlock(worker->left_fork);
	pthread_mutex_unlock(worker->right_fork);
	return (0);
}
