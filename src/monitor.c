#include "philo.h"


static int is_dead(t_worker *worker)
{
    long int current_time;
    long int time_elapsed;

    // Se o filósofo já foi marcado como morto, retorna isso
    if (!is_running(worker))
        return 1;

    current_time = get_time();

	pthread_mutex_lock(&worker->protect_time);
    time_elapsed = current_time - worker->last_meal_time;
	pthread_mutex_unlock(&worker->protect_time);

    // Se o tempo desde a última refeição exceder o tempo para morrer
    if (time_elapsed > worker->time_to_die)
    {
        print_philo(worker, DEAD_MSG);
        return 1;
    }

    return 0;
}

void kill_simulation(t_philo *philo)
{
    pthread_mutex_lock(&philo->protect_print);
    philo->is_simulation_running = false;
    pthread_mutex_unlock(&philo->protect_print);
}

bool    is_running_philo(t_philo *philo)
{
    bool aux;
	pthread_mutex_lock(&philo->protect_print);
	aux = philo->is_simulation_running;
	pthread_mutex_unlock(&philo->protect_print);
	return(aux);
}

void* monitor_thread(void *rec)
{
    t_philo *philo;
    philo = (t_philo *)rec;

    int i;
    int nfull;


    if (philo->num_of_philos == 1)
    {

        usleep(philo->time_to_die * 1000);

        if (is_running_philo(philo))
        {
            print_philo(&philo->workers[0], DEAD_MSG);
            kill_simulation(philo);
        }

        return NULL;
    }

    while (is_running_philo(philo))
    {
        i = 0;
        nfull = 0;
        while (philo->num_of_philos > i)
        {
            if(is_dead(&philo->workers[i]))
            {
               kill_simulation(philo);
                break;
            }

            if(philo->workers[i].is_full)
            {
                nfull++;
            }
            i++;
        }

        // if(!is_running_philo(philo))
        //     break;

        if(philo->num_of_times_each_philo_eat > 0)
        {

            if(nfull >= philo->num_of_philos)
            {
                printf("All philosophers have eaten %d times. Stopping simulation.\n",
                    philo->num_of_times_each_philo_eat);
                kill_simulation(philo);
                break;

            }
        }

      usleep(100);
    }
    return NULL;
}
