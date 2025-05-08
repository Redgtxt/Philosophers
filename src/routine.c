#include "philo.h"

int print_philo(t_worker *worker,char *msg)
{
	pthread_mutex_lock(&worker->philo->protect_print);

	if (!worker->philo->is_simulation_running && strcmp(msg, DEAD_MSG) != 0)
	{
		pthread_mutex_unlock(&worker->philo->protect_print);
		return 0;
	}
	printf("%lu Philosofer:%d %s\n",get_time(), worker->id,msg);
	pthread_mutex_unlock(&worker->philo->protect_print);

	return 0;
}

static void ft_usleep(unsigned long int time)
{
	unsigned long int start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
	{
		usleep(10);
	}

	//usleep(time * 1000);
}

static int eat(t_worker *worker)
{

	if(worker->num_of_philos == 1)
	{
			pthread_mutex_lock(worker->right_fork);
			print_philo(worker, FORK_MSG);

			while (is_running(worker))
			{
				usleep(100);
			}

			pthread_mutex_unlock(worker->right_fork);
			return 0;
	}

	if (!is_running(worker))
		return 0;
	//Pega o garfo
	pthread_mutex_lock(worker->right_fork);
	print_philo(worker,FORK_MSG);

	pthread_mutex_lock(worker->left_fork);
	print_philo(worker,FORK_MSG);

	pthread_mutex_lock(&worker->protect_time);
	worker->last_meal_time = get_time();
	pthread_mutex_unlock(&worker->protect_time);

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
	if(is_running(worker))
		print_philo(worker,SLEEP_MSG);
	ft_usleep(worker->time_to_sleep);
	return 0;
}

static int think(t_worker* worker)
{
	if(is_running(worker))
		print_philo(worker,THINK_MSG);
	return 0;
}

bool	is_running(t_worker *worker)
{
	bool aux;
	pthread_mutex_lock(&worker->philo->protect_print);
	aux = worker->philo->is_simulation_running;
	pthread_mutex_unlock(&worker->philo->protect_print);
	return(aux);
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

	while (is_running(worker))
	{
		if (worker->is_full || !is_running(worker))
			break;

		eat(worker);

		if (worker->is_full || !is_running(worker))
			break;

		my_sleep(worker);

		if (!is_running(worker) || !is_running(worker))
			break;
		think(worker);
	}

	return NULL;
}
