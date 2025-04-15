/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:49:29 by hguerrei          #+#    #+#             */
/*   Updated: 2025/04/08 19:50:25 by hguerrei         ###   ########.fr       */
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
#define MILISECONDS 1000

#define EAT_MSG "is eating"
#define THINK_MSG "is thinking"
#define SLEEP_MSG "is sleeping"
#define DEAD_MSG "is dead"
#define FORK_MSG "has taken a fork"

typedef struct s_worker
{
	int num_of_philos;
	long int time_to_die;
	long int time_to_eat;
	long int time_to_sleep;
	int num_of_times_each_philo_eat;//opcional
	pthread_mutex_t *left_fork; 
	pthread_mutex_t *right_fork; 
	int id;
} t_worker;

typedef struct s_philo
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_times_each_philo_eat;//opcional
	pthread_t *philo_storage;//array que contem as threads
	pthread_mutex_t *mutex_arr;//array de mutexs
	t_worker *workers;//array que contem a estrutura das threads criada
} t_philo;



/*	TIME	*/
long int my_gettimeofday(void);
unsigned long int get_time(void);

/*	INIT THREADS*/
int do_parsing(char *argv[]);
int give_values(t_philo *philo, char *argv[], int argc);
t_worker *worker_init(t_philo *philo);
int storing_philos(t_philo *philo);
int inicialize_program(int argc,char *argv[],t_philo *philo);

/*	ROUTINE	*/
void* routine(void *rec);


pthread_mutex_t *create_mutex(int num);
void cleanup_mutex(pthread_mutex_t *arr,int size);

void debug_values_philo(	t_philo philo);
#endif
