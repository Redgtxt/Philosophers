#include "philo.h"

int init_mutexes(t_philo *philo)
{
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
    return 0;
}

int init_threads(t_philo *philo)
{
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
