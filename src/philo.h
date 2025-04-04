/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:49:29 by hguerrei          #+#    #+#             */
/*   Updated: 2025/04/04 17:58:39 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
#define PHILO_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>

typedef struct s_worker
{

	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_times_each_philo_eat;//opcional


} t_worker;

typedef struct s_philo
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_times_each_philo_eat;//opcional
	pthread_t *philo_storage;

	t_worker *workers;
} t_philo;




void debug_values_philo(	t_philo philo);
int inicialize_program(int argc,char *argv[],t_philo *philo);
int storing_philos(t_philo *philo);
#endif
