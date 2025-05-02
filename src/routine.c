#include "philo.h"

int print_philo(t_worker *worker,char *msg)
{
	if (!worker->philo->is_simulation_running && strcmp(msg, DEAD_MSG) != 0)
		return 0;

	printf("%lu Philosofer:%d %s\n",get_time(), worker->id,msg);
	return 0;
}

static void ft_usleep(long int time)
{
	usleep(time * 1000);
}

static int eat(t_worker *worker)
{

	if(worker->num_of_philos == 1)
	{
			pthread_mutex_lock(worker->right_fork);
			print_philo(worker, FORK_MSG);
			
			while (worker->philo->is_simulation_running && !worker->is_dead)
			{
				usleep(1000); 
			}
			
			pthread_mutex_unlock(worker->right_fork);
			return 0;
	}

	if (!worker->philo->is_simulation_running || worker->is_dead)
		return 0;
	//Pega o garfo
	pthread_mutex_lock(worker->right_fork);
	print_philo(worker,FORK_MSG);

	pthread_mutex_lock(worker->left_fork);
	print_philo(worker,FORK_MSG);
	
	worker->last_meal_time = get_time();
	print_philo(worker,EAT_MSG);
	ft_usleep(worker->time_to_eat);
	worker->n_meals++;

	if(worker->philo->num_of_times_each_philo_eat > 0  && worker->n_meals == worker->philo->num_of_times_each_philo_eat)
	{
		worker->is_full = true;
	} 
	pthread_mutex_unlock(worker->right_fork);
	pthread_mutex_unlock(worker->left_fork);
	return 0; 
}

static int my_sleep(t_worker *worker)
{
	if(worker->philo->is_simulation_running)
		print_philo(worker,SLEEP_MSG);
	ft_usleep(worker->time_to_sleep);
	return 0;
}

static int think(t_worker* worker)
{
	if(worker->philo->is_simulation_running)
		print_philo(worker,THINK_MSG);
	return 0;
}

void* routine(void *rec)
{
	t_worker *worker;
	worker = (t_worker *)rec;

	if (worker->num_of_philos == 1)
    {
        eat(worker);
        return NULL;
    }

	while (worker->philo->is_simulation_running)
	{
		if (worker->is_full || worker->is_dead)
			break;

		eat(worker);

		if (worker->is_full || !worker->philo->is_simulation_running || worker->is_dead)
			break;

		my_sleep(worker);

		if (!worker->philo->is_simulation_running || worker->is_dead)
			break;
		think(worker);
	}

	return NULL;
}