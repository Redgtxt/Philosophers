/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:55 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:57 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	storing_philos(t_philo *philo)
{
	int	p_num;

	p_num = 0;
	while (philo->num_of_philos > p_num)
	{
		if (pthread_create(&philo->philo_storage[p_num], NULL, &routine,
				&(philo->workers[p_num])) != 0)
		{
			return (-1);
		}
		p_num++;
	}
	return (0);
}

static void	fork_set_impar(t_worker *worker, t_philo *philo)
{
	worker->left_fork = &philo->mutex_arr[worker->id - 1];
	if (worker->id == philo->num_of_philos)
		worker->right_fork = &philo->mutex_arr[0];
	else
		worker->right_fork = &philo->mutex_arr[worker->id];
}

static void	fork_set_par(t_worker *worker, t_philo *philo)
{
	worker->right_fork = &philo->mutex_arr[worker->id - 1];
	if (worker->id == philo->num_of_philos)
		worker->left_fork = &philo->mutex_arr[0];
	else
		worker->left_fork = &philo->mutex_arr[worker->id];
}

void	fork_set(t_worker *worker, t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		worker->right_fork = &philo->mutex_arr[0];
		worker->left_fork = NULL;
		return ;
	}
	if (worker->id % 2 == 0)
		fork_set_par(worker, philo);
	else
		fork_set_impar(worker, philo);
}
