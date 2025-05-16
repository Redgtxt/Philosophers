/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:29 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:51:07 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_mutex_arr(int num)
{
	int				i;
	pthread_mutex_t	*mutex_arr;

	mutex_arr = malloc(sizeof(pthread_mutex_t) * num);
	if (!mutex_arr)
		return (NULL);
	i = 0;
	while (num > i)
	{
		pthread_mutex_init(&mutex_arr[i], NULL);
		i++;
	}
	return (mutex_arr);
}

int	init_mutexes(t_philo *philo)
{
	philo->mutex_arr = init_mutex_arr(philo->num_of_philos);
	if (!philo->mutex_arr)
	{
		printf("Error creating mutexes\n");
		return (-1);
	}
	if (pthread_mutex_init(&philo->protect_print, NULL))
	{
		printf("Error creating mutex\n");
		return (-1);
	}
	return (0);
}

void	cleanup_mutex_arr(pthread_mutex_t *arr, int size)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (size > i)
	{
		pthread_mutex_destroy(&arr[i]);
		i++;
	}
	free(arr);
}

int	init_threads(t_philo *philo)
{
	if (storing_philos(philo) == -1)
	{
		printf("Error creating philosopher threads\n");
		cleanup_mutex_arr(philo->mutex_arr, philo->num_of_philos);
		free(philo->philo_storage);
		free(philo->workers);
		return (-1);
	}
	if (pthread_create(&philo->monitor, NULL, monitor_thread, philo) != 0)
	{
		printf("Error creating monitor thread\n");
		cleanup_mutex_arr(philo->mutex_arr, philo->num_of_philos);
		free(philo->philo_storage);
		free(philo->workers);
		return (-1);
	}
	return (0);
}
