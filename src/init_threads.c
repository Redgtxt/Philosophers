#include "philo.h"

int storing_philos(t_philo *philo)
{

    int p_num;

    p_num = 0;
    while(philo->num_of_philos > p_num)
    {
    	if(pthread_create(&philo->philo_storage[p_num],NULL,&routine, &(philo->workers[p_num])) != 0)
		{
			//TENHO DE DAR FREE E MATAR OS PHILOS
			return -1;
		}
		p_num++;
	}

    return 0;
}

static void fork_set_impar(t_worker *worker, t_philo *philo)
{
    worker->left_fork = &philo->mutex_arr[worker->id - 1];
    if(worker->id == philo->num_of_philos)
        worker->right_fork = &philo->mutex_arr[0];
    else
        worker->right_fork = &philo->mutex_arr[worker->id];
}

static void fork_set_par(t_worker *worker, t_philo *philo)
{
    worker->right_fork = &philo->mutex_arr[worker->id - 1];
    if(worker->id == philo->num_of_philos)
        worker->left_fork = &philo->mutex_arr[0];
    else
        worker->left_fork = &philo->mutex_arr[worker->id];
}

static void fork_set(t_worker *worker, t_philo *philo)
{
    if (philo->num_of_philos == 1)
    {

        worker->right_fork = &philo->mutex_arr[0];
        worker->left_fork = NULL;
        return;
    }

    if(worker->id % 2 == 0)
    {
        fork_set_par(worker,philo);
    }else
        fork_set_impar(worker,philo);
}

t_worker *worker_init(t_philo *philo)
{
    t_worker *worker;
    int i;

    i = 0;
    worker = malloc(sizeof(t_worker) * philo->num_of_philos);
    while (philo->num_of_philos > i)
    {
        worker[i].time_to_die = philo->time_to_die;
        worker[i].time_to_eat = philo->time_to_eat;
        worker[i].time_to_sleep = philo->time_to_sleep;
        worker[i].num_of_philos = philo->num_of_philos;
        worker[i].id = i + 1;
        worker[i].n_meals = 0;
        worker[i].philo = philo;
        worker[i].is_full = false;
        worker[i].last_meal_time = get_time();
        pthread_mutex_init(&worker[i].protect_time,NULL);
        fork_set(&worker[i], philo);
        i++;
    }

    return worker;
}


int inicialize_program(int argc, char *argv[], t_philo *philo)
{
    if(argc < 5 || argc >= 7)
    {
        printf("Error: Wrong number of arguments\n");
        return -1;
    }
    memset(philo, 0, sizeof(t_philo));
    if(do_parsing(argv) == -1)
    {
        return -1;
    }
    if(give_values(philo, argv, argc) == -1)
    {
        printf("Error: Value Invalid\n");
        return -1;
    }
    if (philo->num_of_philos == 1)
    {
        printf("Only one philosopher. He will die after %d ms.\n", philo->time_to_die);
    }
    philo->is_simulation_running = true;
    philo->mutex_arr = create_mutex(philo->num_of_philos);
    if (!philo->mutex_arr)
    {
        printf("Error creating mutexes\n");
        return -1;
    }
    if (pthread_mutex_init(&philo->protect_print, NULL))
    {
        printf("Error creating mutex\n");
        return -1;
    }

    philo->philo_storage = malloc(sizeof(pthread_t) * philo->num_of_philos);
    if(!philo->philo_storage)
    {
        printf("Error allocating memory for array");
        cleanup_mutex(philo->mutex_arr, philo->num_of_philos);
        return -1;
    }

    philo->workers = worker_init(philo);
    if (!philo->workers)
    {
        printf("Error initializing workers\n");
        cleanup_mutex(philo->mutex_arr, philo->num_of_philos);
        free(philo->philo_storage);
        return -1;
    }


    if (storing_philos(philo) == -1)
    {
        printf("Error creating philosopher threads\n");
        cleanup_mutex(philo->mutex_arr, philo->num_of_philos);
        free(philo->philo_storage);
        free(philo->workers);
        return -1;
    }


    if (pthread_create(&philo->monitor, NULL, monitor_thread, philo) != 0)
    {
        printf("Error creating monitor thread\n");

        cleanup_mutex(philo->mutex_arr, philo->num_of_philos);
        free(philo->philo_storage);
        free(philo->workers);
        return -1;
    }

    return 0;
}
