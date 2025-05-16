/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:37 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:39 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	philo;
	int		i;

	if (inicialize_program(argc, argv, &philo) == -1)
		return (-1);
	i = 0;
	pthread_join(philo.monitor, NULL);
	while (philo.num_of_philos > i)
	{
		pthread_join(philo.philo_storage[i], NULL);
		i++;
	}
	cleanup_mutex_arr(philo.mutex_arr, philo.num_of_philos);
	i = 0;
	while (philo.num_of_philos > i)
	{
		pthread_mutex_destroy(&philo.workers[i].protect_time);
		i++;
	}
	pthread_mutex_destroy(&philo.protect_print);
	free(philo.philo_storage);
	free(philo.workers);
	return (0);
}
