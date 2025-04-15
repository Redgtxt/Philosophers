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

static void fork_set(t_worker *worker,t_philo *philo,int i)
{
    worker->left_fork = philo.mutex_arr[i - 1];
    if(worker->id)
        worker->right_fork = philo->mutex_arr[i];
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
        worker[i].num_of_times_each_philo_eat = philo->num_of_times_each_philo_eat;
        worker[i].num_of_philos = philo->num_of_philos;
        worker[i].id = i + 1;
        fork_set(&worker[i],philo);
        i++;
    }

    return worker;
}


int inicialize_program(int argc,char *argv[],t_philo *philo)
{
    if(argc < 5 || argc >= 7)
    {
        printf("Error: Wrong number of arguments\n");
        return -1;
    }
    memset(philo,0,sizeof(t_philo));
    if(do_parsing(argv) == -1)
    {
        return -1;
    }
    if(give_values(philo,argv,argc) == -1)
    {
        printf("Error: Value Invalid\n");
        return -1;
    }
    philo->mutex_arr = create_mutex(philo->num_of_philos);

    philo->philo_storage = malloc(sizeof(pthread_t) * philo->num_of_philos);
    if(!philo->philo_storage)
    {
        printf("Error allocating memory for array");
        return -1;
    }
    philo->workers = worker_init(philo);
    storing_philos(philo);


    return 0;
}
