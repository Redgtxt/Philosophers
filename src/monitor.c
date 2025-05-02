#include "philo.h"


static int is_dead(t_worker *worker)
{
    long int current_time;
    long int time_elapsed;
    
    // Se o filósofo já foi marcado como morto, retorna isso
    if (worker->is_dead)
        return 1;
    
    current_time = get_time();
    time_elapsed = current_time - worker->last_meal_time;
    
    // Se o tempo desde a última refeição exceder o tempo para morrer
    if (time_elapsed > worker->time_to_die)
    {
        worker->is_dead = true;
        print_philo(worker, DEAD_MSG);
        return 1;
    }
    
    return 0;
}

void* monitor_thread(void *rec)
{
    t_philo *philo;
    philo = (t_philo *)rec;

    int i;
    int nfull;
    bool someone_died;
    
    someone_died = false;

    if (philo->num_of_philos == 1)
    {

        usleep(philo->time_to_die * 1000);
        

        if (philo->is_simulation_running)
        {      
            print_philo(&philo->workers[0], DEAD_MSG);
            philo->is_simulation_running = false;
        }
        
        return NULL;
    }

    while (philo->is_simulation_running)
    {
        i = 0;
        nfull = 0;
        while (philo->num_of_philos > i && !someone_died)
        {
            if(is_dead(&philo->workers[i]))
            {
                philo->is_simulation_running = false;
                someone_died = true;
                break;
            }
            
            if(philo->workers[i].is_full)
            {
                nfull++;
            }
            i++;
        }
        
        if(someone_died)
            break;
        
        if(philo->num_of_times_each_philo_eat > 0)
        {

            if(nfull >= philo->num_of_philos)
            {
                printf("All philosophers have eaten %d times. Stopping simulation.\n", 
                    philo->num_of_times_each_philo_eat);
                philo->is_simulation_running = false;
                break;

            }
        }
        
      usleep(1000);
    }
    return NULL;
}
