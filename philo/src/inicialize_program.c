/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicialize_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:47:54 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:47:56 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc >= 7)
	{
		printf("Error: Wrong number of arguments\n");
		return (-1);
	}
	if (do_parsing(argv) == -1)
	{
		return (-1);
	}
	return (0);
}

static int	setup_philo(t_philo *philo, char *argv[], int argc)
{
	memset(philo, 0, sizeof(t_philo));
	if (give_values(philo, argv, argc) == -1)
	{
		printf("Error: Value Invalid\n");
		return (-1);
	}
	if (philo->num_of_philos == 1)
	{
		printf("Only one philosopher. He will die after %d ms.\n",
			philo->time_to_die);
	}
	philo->is_simulation_running = true;
	return (0);
}

int	inicialize_program(int argc, char *argv[], t_philo *philo)
{
	if (check_args(argc, argv) == -1)
		return (-1);
	if (setup_philo(philo, argv, argc) == -1)
		return (-1);
	if (init_mutexes(philo) == -1)
		return (-1);
	if (init_memory(philo) == -1)
		return (-1);
	if (init_threads(philo) == -1)
		return (-1);
	return (0);
}
