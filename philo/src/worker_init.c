/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:17 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:19 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_worker	*worker_init(t_philo *philo)
{
	t_worker	*worker;
	int			i;

	i = 0;
	worker = malloc(sizeof(t_worker) * philo->num_of_philos);
	if (!worker)
		return (NULL);
	while (philo->num_of_philos > i)
	{
		worker[i].time_to_die = philo->time_to_die;
		worker[i].time_to_eat = philo->time_to_eat;
		worker[i].time_to_sleep = philo->time_to_sleep;
		worker[i].num_of_philos = philo->num_of_philos;
		worker[i].id = i + 1;
		worker[i].n_meals = 0;
		worker[i].philo = philo;
		worker[i].is_full = false;
		worker[i].last_meal_time = get_time();
		pthread_mutex_init(&worker[i].protect_time, NULL);
		fork_set(&worker[i], philo);
		i++;
	}
	return (worker);
}

int	init_memory(t_philo *philo)
{
	philo->philo_storage = malloc(sizeof(pthread_t) * philo->num_of_philos);
	if (!philo->philo_storage)
	{
		printf("Error allocating memory for array");
		cleanup_mutex_arr(philo->mutex_arr, philo->num_of_philos);
		return (-1);
	}
	philo->workers = worker_init(philo);
	if (!philo->workers)
	{
		printf("Error initializing workers\n");
		cleanup_mutex_arr(philo->mutex_arr, philo->num_of_philos);
		free(philo->philo_storage);
		return (-1);
	}
	return (0);
}
