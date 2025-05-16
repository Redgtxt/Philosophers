/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:43 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:45 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_worker *worker)
{
	long int	current_time;
	long int	time_elapsed;

	if (!is_running(worker))
		return (1);
	current_time = get_time();
	pthread_mutex_lock(&worker->protect_time);
	time_elapsed = current_time - worker->last_meal_time;
	pthread_mutex_unlock(&worker->protect_time);
	if (time_elapsed > worker->time_to_die)
	{
		print_philo(worker, DEAD_MSG);
		return (1);
	}
	return (0);
}

static void	*monitor_one(t_philo *philo)
{
	usleep(philo->time_to_die * 1000);
	if (is_running_philo(philo))
	{
		print_philo(&philo->workers[0], DEAD_MSG);
		kill_simulation(philo);
	}
	return (NULL);
}

static int	have_we_all_eaten_enough(t_philo *philo, int nfull)
{
	if (philo->num_of_times_each_philo_eat > 0)
	{
		if (nfull >= philo->num_of_philos)
		{
			pthread_mutex_lock(&philo->protect_print);
			printf(EAT_ENOUGH);
			pthread_mutex_unlock(&philo->protect_print);
			kill_simulation(philo);
			return (1);
		}
	}
	return (0);
}

static int	check_death(t_philo *philo, int i)
{
	if (is_dead(&philo->workers[i]))
	{
		kill_simulation(philo);
		return (1);
	}
	return (0);
}

void	*monitor_thread(void *rec)
{
	t_philo	*philo;
	int		i;
	int		nfull;

	philo = (t_philo *)rec;
	if (philo->num_of_philos == 1)
		return (monitor_one(philo));
	while (is_running_philo(philo))
	{
		i = -1;
		nfull = 0;
		while (philo->num_of_philos > ++i)
		{
			if (check_death(philo, i))
				break ;
			pthread_mutex_lock(&philo->workers[i].protect_time);
			if (philo->workers[i].is_full)
				nfull++;
			pthread_mutex_unlock(&philo->workers[i].protect_time);
		}
		if (have_we_all_eaten_enough(philo, nfull))
			break ;
		usleep(100);
	}
	return (NULL);
}
