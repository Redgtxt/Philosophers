#include "philo.h"


static int is_dead(t_worker *worker)
{
    (void)worker;

    return 0;
}

void* monitor_thread(void *rec)
{
    t_philo *philo;
	philo = (t_philo *)rec;

    int i;
    int nfull;

    while (true)
    {
        i = 0;
        nfull = 0;
        while (philo->num_of_philos > i)
        {
            if(is_dead(&philo->workers[i]))
                break;
            
            if(philo->workers[i].is_full)
            {
              printf("%d\n",philo->workers[i].is_full);
                usleep(100);
                nfull++;
            }
           i++;
        }
        if(nfull >= philo->num_of_philos)
            break ;
    }
    return NULL;
}