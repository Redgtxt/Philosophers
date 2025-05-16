/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:04 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:06 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_sleep(t_worker *worker)
{
	if (is_running(worker))
		print_philo(worker, SLEEP_MSG);
	ft_usleep(worker->time_to_sleep);
	return (0);
}

static int	think(t_worker *worker)
{
	if (is_running(worker))
		print_philo(worker, THINK_MSG);
	if (worker->num_of_philos % 2 > 0)
	{
		if ((worker->time_to_eat * 2) - worker->time_to_sleep > 0)
			ft_usleep((worker->time_to_eat * 2) - worker->time_to_sleep);
	}
	else if (worker->time_to_eat - worker->time_to_sleep > 0)
		ft_usleep(worker->time_to_eat - worker->time_to_sleep);
	return (0);
}

static void	select_wait(t_worker *worker)
{
	if (worker->num_of_philos % 2 > 0)
	{
		if (worker->id == worker->num_of_philos)
			ft_usleep((worker->time_to_eat * 2));
		else if (worker->id % 2 > 0)
			ft_usleep(worker->time_to_eat);
	}
	else if (worker->id % 2 > 0)
		ft_usleep(worker->time_to_eat);
}

void	*routine(void *rec)
{
	t_worker	*worker;

	worker = (t_worker *)rec;
	if (worker->num_of_philos == 1)
		return (eat(worker), NULL);
	select_wait(worker);
	while (is_running(worker))
	{
		if (!is_running(worker))
			break ;
		eat(worker);
		if (!is_running(worker))
			break ;
		my_sleep(worker);
		if (!is_running(worker))
			break ;
		think(worker);
	}
	return (NULL);
}
