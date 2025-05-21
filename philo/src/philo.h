/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:12:03 by hguerrei          #+#    #+#             */
/*   Updated: 2025/05/21 16:21:57 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define MILISECONDS 1000

# define EAT_MSG "is eating"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"
# define DEAD_MSG "is dead"
# define FORK_MSG "has taken a fork"
# define EAT_ENOUGH "Ending simulation all have eaten enough times\n"

typedef struct s_philo
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_eat;// opcional
	pthread_t		monitor;
	bool			is_simulation_running;
	pthread_t		*philo_storage;// array que contem as threads
	pthread_mutex_t	*mutex_arr;// array de mutexs
	struct s_worker	*workers;
	pthread_mutex_t	protect_print;
}					t_philo;

typedef struct s_worker
{
	int				num_of_philos;
	long int		time_to_die;
	bool			is_full;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		last_meal_time;
	pthread_mutex_t	protect_time;
	int				n_meals;// opcional
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo			*philo;
	int				id;
}					t_worker;

/*Parsing */
int					do_parsing(char *argv[]);
int					give_values(t_philo *philo, char *argv[], int argc);

/*Philo Init*/
void				fork_set(t_worker *worker, t_philo *philo);
int					storing_philos(t_philo *philo);

/*Worker Init*/
int					init_memory(t_philo *philo);

/*Init threads and Mutexs*/
int					init_threads(t_philo *philo);
int					init_mutexes(t_philo *philo);
pthread_mutex_t		*init_mutex_arr(int num);
void				cleanup_mutex_arr(pthread_mutex_t *arr, int size);

/*Inicialize Program*/
int					inicialize_program(int argc, char *argv[], t_philo *philo);

/*	Monitor	*/
void				*monitor_thread(void *rec);

/*	ADMIN	*/
void				kill_simulation(t_philo *philo);
bool				is_running_philo(t_philo *philo);
bool				is_running(t_worker *worker);
int					print_philo(t_worker *worker, char *msg);

/*	TIME	*/
long int			my_gettimeofday(void);
unsigned long int	get_time(void);
void				ft_usleep(unsigned long int time,t_worker *worker);

/*Eat*/
int					eat(t_worker *worker);

/*	ROUTINE	*/
void				*routine(void *rec);

#endif
